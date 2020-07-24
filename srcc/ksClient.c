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

    if (2 != argc || !argv[1] || 0 == strlen(argv[1])) {
        exit(EXIT_FAILURE);
    }

    mqid = strtol(argv[1], &end, 10);

    if (end != argv[1] + strlen(argv[1])) {
        exit(EXIT_FAILURE);
    }

    do {

        if (0 > msgrcv(mqid, &msg, KS_MSG_MAX, 0, IPC_NOWAIT)) {

            if (ENOMSG == errno)    KS_SLEEP(500);
            else                    exit(EXIT_FAILURE);

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

    exit(EXIT_SUCCESS);

}

