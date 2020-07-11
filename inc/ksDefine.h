/****************************************
  ksDefine.h
    copyright 2020.07.11 konoar 
 ****************************************/

#ifndef __KS_DEFINE_H__
#define __KS_DEFINE_H__

#include <time.h>

#define KS_OK               0x00000000
#define KS_NG               0x80000000

#define KS_EXE_SERVER       "s"
#define KS_EXE_CLIENT       "c"

#define KS_MSG_PRINT        1
#define KS_MSG_KILL         2

#define KS_SLEEP(_a_)                               \
    do {                                            \
                                                    \
        struct timespec t = {                       \
            _a_ / 1000, (_a_ % 1000) * 1000 * 1000  \
        };                                          \
        nanosleep(&t, NULL);                        \
                                                    \
    } while(0)

#define KS_MSG_MAX          128

typedef struct _ksMessage
{

   long type;
   char message[KS_MSG_MAX];

} ksMessage, *ksMessagePtr;

#endif // __KS_DEFINE_H__

