#ifndef FE_KERNEL_H
#define FE_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif
extern volatile int fe_status;
int fe_main();
void fe_panic();

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#ifdef __cplusplus
}
#endif

#endif // FE_KERNEL_H