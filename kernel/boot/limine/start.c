#include "start.h"
#include <stdio.h>
#include "limine.h"

static volatile struct limine_bootloader_info_request limine_bootloader_info = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0
};

static volatile struct limine_memmap_request limine_memmap = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

uint64_t free_mem = 0;
uint64_t hardware_mem = 0;
uint64_t dead_mem = 0;

void printMemMap(void) {
    for (uint64_t x = 0; x < limine_memmap.response->entry_count; x++) {
        switch (limine_memmap.response->entries[x]->type)
        {
        case LIMINE_MEMMAP_USABLE:
            free_mem += limine_memmap.response->entries[x]->length;
        break;
        case LIMINE_MEMMAP_RESERVED:
            hardware_mem += limine_memmap.response->entries[x]->length;
        break;
        case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
            free_mem += limine_memmap.response->entries[x]->length;
        break;
        case LIMINE_MEMMAP_ACPI_NVS:
            continue;
        break;
        case LIMINE_MEMMAP_BAD_MEMORY:
            dead_mem += limine_memmap.response->entries[x]->length;
        break;
        case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
            hardware_mem += limine_memmap.response->entries[x]->length;
        break;
        case LIMINE_MEMMAP_KERNEL_AND_MODULES:
            free_mem += limine_memmap.response->entries[x]->length;//taken by the kernel but free memory non the less
        break;
        case LIMINE_MEMMAP_FRAMEBUFFER:
            hardware_mem += limine_memmap.response->entries[x]->length;
        break;
        default:
            printf("[LIMINE BOOT] [ERROR] Bootloader parsed %u as mem type\n", limine_memmap.response->entries[x]->type);
        break;
        }
    }
    printf("Hardware reserved memory: %uMiB (%u pages)\n", hardware_mem / 1024 / 1024, hardware_mem / 4096);
    printf("Free memory: %uMiB (%u pages)\n", free_mem / 1024 / 1024, free_mem / 4096);
    if (dead_mem > 0) {printf("!!!\nDead memory detected\nDead memory: %uB (%u pages)\n!!!\n", dead_mem, dead_mem / 4096);}
}

void _start(void) {
    limine_fb_init();
    printf("[LIMINE BOOT] Kernel started by %s, revision: %s\n", limine_bootloader_info.response->name, limine_bootloader_info.response->version);
    printMemMap();
    for (;;);
}