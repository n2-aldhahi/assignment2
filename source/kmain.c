#include "../drivers/frame_buffer.h"

void kmain() {
    fb_clear();
    fb_write_string("Welcome to Tiny OS!\n");
    fb_write_string("Framebuffer driver initialized successfully.\n\n");
    
    fb_write_string("Testing colors:\n");
    fb_set_color(FB_GREEN, FB_BLACK);
    fb_write_string("Green text\n");
    
    fb_set_color(FB_RED, FB_BLACK);
    fb_write_string("Red text\n");
    
    fb_set_color(FB_BLUE, FB_BLACK);
    fb_write_string("Blue text\n");
    
    fb_set_color(FB_LIGHT_GREY, FB_BLACK);
    fb_write_string("\nCursor positioning test:\n");
    fb_move_cursor(10, 10);
    fb_write_string("This is at position (10,10)");
    
    fb_move_cursor(0, 12);
    fb_write_string("Tiny OS v1.0 - Frame Buffer Test Complete");
}
