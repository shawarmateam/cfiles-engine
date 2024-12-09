#ifndef FE_KERNEL
#define FE_KERNEL
#include "fe-settings.h"

#ifdef __cplusplus
extern "C" {
    void run();
    int loop();
}

#ifdef LOGGING_FE
    #define LOG(msg) printf("FE_LOG: %s\n", msg)
#else
    #define LOG(msg) // просто скип
#endif



#endif // __cplusplus

#ifndef __cplusplus
void run();
int loop();
#endif


#endif // FE_KERNEL
