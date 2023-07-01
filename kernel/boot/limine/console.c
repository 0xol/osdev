#include <stdint.h>
#include <font.h>
#include "limine.h"
#include "start.h"
#include <stdio.h>

static volatile struct limine_framebuffer_request limine_fb = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};
const char font_mask[8]={128,64,32,16,8,4,2,1};
#define MAX_CURSOR_X (limine_fb.response->framebuffers[0]->width / FONT_WIDTH)
#define MAX_CURSOR_Y (limine_fb.response->framebuffers[0]->height / FONT_HEIGHT)
#define SCREEN_WIDTH (limine_fb.response->framebuffers[0]->width)
#define SCREEN_HEIGHT (limine_fb.response->framebuffers[0]->height)
#define SCREEN_NEXT_CHAR_POSITION ((current_cursor_x * FONT_WIDTH) + (current_cursor_Y * FONT_HEIGHT * SCREEN_WIDTH))

int current_cursor_x = 0;
int current_cursor_Y = 0;
uint32_t background_colour = 0x00000000;
uint32_t foreground_colour = 0xFFFFFFFF;
int* limine_fb_addr;

int limine_fb_draw_char(char c) {
    for (int y = 0; y < FONT_HEIGHT; y++) {for (int x = 0; x < FONT_WIDTH; x++) {
        limine_fb_addr[SCREEN_NEXT_CHAR_POSITION + x + (y * SCREEN_WIDTH)] = background_colour;
        if (font_bitmap[c * FONT_HEIGHT + y]&font_mask[x]) {
            limine_fb_addr[SCREEN_NEXT_CHAR_POSITION + x + (y * SCREEN_WIDTH)] = foreground_colour;
        }
    }}
    return 0;
}

int limine_fb_putchar(char c) {
    if (c < ' ') {
        switch (c) {
        case '\0':
            return 0;
        break;

        case '\b':
            if (current_cursor_x != 0) {current_cursor_x--; return 0;}
            if (current_cursor_Y != 0) {current_cursor_Y--; current_cursor_x = MAX_CURSOR_X-1; return 0;}
            return 0;//we are at the start of the screen, backspace shouldnt do anything
        break;
        
        case '\t':
            for (int x = 0; x < 4; x++) {putchar(' ');}
            return 0;
        break;

        case '\n':
            current_cursor_x = 0;
            current_cursor_Y++;
            return 0;
        break;

        case '\r':
            current_cursor_x = 0;
            return 0;
        break;

        default:
            return 1;    
        break;
        }
    }
    
    if (c >= ' ' && c <= '~') {
        limine_fb_draw_char(c);

        current_cursor_x++;
        if ((uint64_t)current_cursor_x == MAX_CURSOR_X) {current_cursor_x = 0; current_cursor_Y++;}
        return 0;
    }
    return 1;
}

int limine_fb_init(void) {
    limine_fb_addr = limine_fb.response->framebuffers[0]->address;
    putchar = limine_fb_putchar;
    return 0;
}