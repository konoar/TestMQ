/****************************************
  ksServer.c
    copyright 2020.07.11 konoar 
 ****************************************/

#include "ksDefine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

static int ksMqCreate(int *mqid)
{

    if (!mqid) {
        return KS_NG;
    }

    if (0 > (*mqid = msgget(IPC_PRIVATE, 0600))) {
        return KS_NG;
    }

    return KS_OK;

}

static int ksMqRelease(int mqid)
{

    struct msqid_ds msq;

    if (0 != msgctl(mqid, IPC_RMID, &msq)) {
        return KS_NG;
    }

    return KS_OK;

}

static int ksMsgSend(int mqid, int type, const char *message)
{

    ksMessage msg;
    memset(&msg, 0x00, sizeof(ksMessage));

    msg.type = type;

    if (message)    strcpy(msg.message, message);
    else            msg.message[0] = 0x00;

    if (0 != msgsnd(mqid, &msg, KS_MSG_MAX, 0)) {
        return KS_NG;
    }

    return KS_OK;

}

static int ksFork(pid_t *pid, int mqid)
{

    char mqidstr[32];

    char* const param[] = {
        KS_EXE_CLIENT, mqidstr, NULL
    };

    char* const env[] = {
        NULL
    };

    sprintf(mqidstr, "%d", mqid);

    if (0 == (*pid = vfork())) {
        (void) execve(KS_EXE_CLIENT, param, env);
        return KS_NG;
    }

    return KS_OK;

}

int main(int argc, const char *argv[])
{

    pid_t pid;
    int status, mqid, ecode = EXIT_SUCCESS;

    if (KS_OK != ksMqCreate(&mqid)) {
        exit(EXIT_FAILURE);
    }

    if (KS_OK != ksFork(&pid, mqid)) {
        exit(EXIT_FAILURE);
    }

    do {

        printf("Server Start\n");

        if (KS_OK != ksMsgSend(mqid, KS_MSG_PRINT, "Msg1")) {
            break;
        }

        KS_SLEEP(2 * 1000);

        if (KS_OK != ksMsgSend(mqid, KS_MSG_PRINT, "Msg2")) {
            ecode = EXIT_FAILURE;
            break;
        }

        if (KS_OK != ksMsgSend(mqid, KS_MSG_PRINT, NULL)) {
            ecode = EXIT_FAILURE;
            break;
        }

        if (KS_OK != ksMsgSend(mqid, KS_MSG_KILL, NULL)) {
            ecode = EXIT_FAILURE;
            break;
        }

        while (1) {
            if (-1 == waitpid(pid, &status, 0)) {
                ecode = EXIT_FAILURE;
                break;
            } else if (WIFEXITED(status)) {
                printf("Exited\n");
                break;
            }
        }

    } while(0);

    printf("Server End\n");

    if (KS_OK != ksMqRelease(mqid)) {
        ecode = EXIT_FAILURE;
    }

    exit(ecode);

}

