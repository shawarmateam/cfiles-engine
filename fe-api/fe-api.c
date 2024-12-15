#include <stdio.h>

void __attribute__((constructor)) init() {
    printf("hello world\n");
}
