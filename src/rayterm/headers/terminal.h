#ifndef _RAY_TERMINAL_H_
#define _RAY_TERMINAL_H_

#include <ncurses.h>

extern struct Windows {
    WINDOW* info;
    WINDOW* main;
} WINDOWS;

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

void setup(void);
void allrefresh(void);
void inforefresh(void);
void mainrefresh(void);
void handle_resize(void);
void cleanup(void);

// Query
Vec2 get_main_size(void);

// Utility
void waddstr_attr(WINDOW* window, const char* str, chtype attr);


// Main interactive functions
void set_info_string(const char* str);
void set_character_pixel(const int x, const int y, const void* pixelData);
#endif
