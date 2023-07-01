#include "start.h"

void _start(void) {
    limine_fb_init();
    char string[] = "Booting VIZ kernel from limine\n";
    for (int x = 0;string[x] != '\0';x++) {
        putchar(string[x]);
    }
    for (;;);
}