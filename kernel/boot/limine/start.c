#include "start.h"
#include <stdio.h>

void _start(void) {
    limine_fb_init();
    char string[] = "Booting VIZ kernel from limine\n";
    for (int x = 0;string[x] != '\0';x++) {
        putchar(string[x]);
    }
    puts("Testing puts from klibc with limine putchar backend");

    printf("OMG %i printf support", 3);
    for (;;);
}