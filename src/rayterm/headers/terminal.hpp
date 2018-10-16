#ifndef _RAY_TERMINAL_H_
#define _RAY_TERMINAL_H_

#include <string>
#include <ncurses.h>

extern struct Windows {
    WINDOW* info;
    WINDOW* main;
} WINDOWS;

void setup(void);
void allrefresh(void);
void inforefresh(void);
void mainrefresh(void);
void handle_resize(void);
void cleanup(void);

void mainloop(void);

void waddstr_attr(WINDOW* window, char* str, chtype attr);

#endif
