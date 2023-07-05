#include "start.h"
#include <stdio.h>
#include "limine.h"
#include <kernel.h>

static volatile struct limine_bootloader_info_request limine_bootloader_info = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0
};

void _start(void) {
    limine_fb_init();
    printf("Kernel started by %s, revision: %s\n", limine_bootloader_info.response->name, limine_bootloader_info.response->version);
    kernel_start();
    for (;;);
}
