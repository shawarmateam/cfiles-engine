#ifndef FE_KERNEL
#define FE_KERNEL

#ifdef __cplusplus
extern "C" {
    void run();
    int loop();
}
#endif

#ifndef __cplusplus
void run();
int loop();
#endif

#endif // FE_KERNEL
