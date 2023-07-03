#include <stdio.h>
#include <kernel.h>

void kernel_start(void) {
    printf("VIZ kernel v%s (C) 2023 0xol\n", VIZ_VERSION);
    printf("Built %s at %s\n", __DATE__, __TIME__);

    arch_init();
}