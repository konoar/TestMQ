/****************************************
  ksClient.c
    copyright 2020.07.11 konoar 
 ****************************************/

#include "ksDefine.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/msg.h>

int main(int argc, const char *argv[])
{

    int         mqid    = -1;
    int         abort   =  0;
    char        *end;
    ksMessage   msg;

    if (2 != argc) {
        return KS_NG;
    }

    if (0 == (mqid = strtol(argv[1], &end, 10)) || end != argv[1] + strlen(argv[1])) {
        return KS_NG;
    }

    do {

        if (0 > msgrcv(mqid, &msg, KS_MSG_MAX, 0, IPC_NOWAIT)) {

            if (ENOMSG == errno)    KS_SLEEP(500);
            else                    return KS_NG;

        } else {

            switch (msg.type) {

                case KS_MSG_PRINT:
                    printf("%s\n", msg.message);
                    break;

                case KS_MSG_KILL:
                    abort = 1;
                    break;

            }

        }

    } while(!abort);

    return KS_OK;

}

