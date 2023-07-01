#include <stdio.h>
#include <stdint.h>

char putchar_set = 0;
int (*putchar)(char c);

int puts(const char *s) {
    for (uint16_t x = 0; x < 4096; x++) {
        if (s[x] == '\0') {putchar('\n'); return 0;} //finished printing string, print newline and return
        if (putchar(s[x]) < 0) {return EOF;} //errors if putchar encounters an error and returns a negative value
    }
    return EOF; //triggers if (sizeof(s) > 4096), likely caused by a buffer overflow
}