#include <stdio.h>
#include "gdt.h"

void arch_init(void) {
    printf("Starting x86_64 backend\n");
    gdt_init();
}