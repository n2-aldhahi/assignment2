#include "frame_buffer.h"
#include "../source/io.h"

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FB_WIDTH  80
#define FB_HEIGHT 25

char *fb = (char *) 0x000B8000;
unsigned short cursor_x = 0;
unsigned short cursor_y = 0;
unsigned char current_fg = FB_LIGHT_GREY;
unsigned char current_bg = FB_BLACK;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void fb_move_cursor(unsigned short pos_x, unsigned short pos_y) {
    cursor_x = pos_x;
    cursor_y = pos_y;
    unsigned short pos = pos_y * FB_WIDTH + pos_x;
    
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_set_color(unsigned char fg, unsigned char bg) {
    current_fg = fg;
    current_bg = bg;
}

void fb_write_char(char c) {
    if (c == '\n') {
        fb_newline();
        return;
    }
    
    if (c == '\b') {
        fb_backspace();
        return;
    }
    
    unsigned int position = cursor_y * FB_WIDTH + cursor_x;
    fb_write_cell(position, c, current_fg, current_bg);
    
    cursor_x++;
    if (cursor_x >= FB_WIDTH) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= FB_HEIGHT) {
            cursor_y = FB_HEIGHT - 1;
        }
    }
    
    fb_move_cursor(cursor_x, cursor_y);
}

void fb_write_string(char *str) {
    int i = 0;
    while (str[i]) {
        fb_write_char(str[i]);
        i++;
    }
}

void fb_clear() {
    for (int i = 0; i < FB_WIDTH * FB_HEIGHT; i++) {
        fb_write_cell(i, ' ', current_fg, current_bg);
    }
    fb_move_cursor(0, 0);
}

void fb_newline() {
    cursor_x = 0;
    cursor_y++;
    if (cursor_y >= FB_HEIGHT) {
        cursor_y = FB_HEIGHT - 1;
    }
    fb_move_cursor(cursor_x, cursor_y);
}

void fb_backspace() {
    if (cursor_x > 0) {
        cursor_x--;
    } else if (cursor_y > 0) {
        cursor_y--;
        cursor_x = FB_WIDTH - 1;
    }
    
    unsigned int position = cursor_y * FB_WIDTH + cursor_x;
    fb_write_cell(position, ' ', current_fg, current_bg);
    fb_move_cursor(cursor_x, cursor_y);
}
