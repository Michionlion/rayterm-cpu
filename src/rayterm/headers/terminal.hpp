#ifndef _RAY_TERMINAL_H_
#define _RAY_TERMINAL_H_

#include <string>
#include <ncurses.h>

extern struct Windows {
    WINDOW* info;
    WINDOW* main;
} WINDOWS;

void setup(void);
void cleanup(void);

#endif
