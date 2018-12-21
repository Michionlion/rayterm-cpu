#include "terminal.hpp"
#include <iostream>

// initialize global variable
Windows WINDOWS;

// Setup Terminal
void setup() {
    initscr();
    start_color();
    cbreak();
    noecho();

    curs_set(0);


    init_pair(1,COLOR_WHITE, COLOR_BLUE);
    init_pair(2,COLOR_WHITE, COLOR_GREEN);

    WINDOWS.main = subwin(stdscr, LINES-1, 0, 0, 0);
    WINDOWS.info = subwin(stdscr, 1, 0, LINES-1, 0);
    wbkgd(WINDOWS.main, COLOR_PAIR(2));
    wbkgd(WINDOWS.info, COLOR_PAIR(1));

    keypad(WINDOWS.main, true);
    keypad(WINDOWS.info, true);

    allrefresh();
}

void allrefresh() {
    inforefresh();
    mainrefresh();
}

void inforefresh() {
    wrefresh(WINDOWS.info);
}

void mainrefresh() {
    wrefresh(WINDOWS.main);
}

// Probably should just ignore resize
void handle_resize() {
    wresize(stdscr, LINES, COLS);
    wclear(stdscr);
    wresize(WINDOWS.info, 1, COLS);
    wresize(WINDOWS.main, LINES - 1, COLS);
    mvwin(WINDOWS.info, LINES - 1, 0);
    mvwin(WINDOWS.main, 0, 0);

    // wbkgd(WINDOWS.main, COLOR_PAIR(2));
    // wbkgd(WINDOWS.info, COLOR_PAIR(1));
    wclear(WINDOWS.main);
    wclear(WINDOWS.info);
    allrefresh();
    allrefresh();
}

Vec2 get_main_size() {
    Vec2 sizes = Vec2();
    getmaxyx(WINDOWS.main, sizes.y, sizes.x);

    return sizes;
}

void waddstr_attr(WINDOW* window, const char* str, chtype attr) {
    for(int i = 0; str[i] != '\0'; i++) {
        waddch(window, str[i] | attr);
    }
}

// auto-refreshes info window
void set_info_string(const char* str) {
    wclear(WINDOWS.info);
    mvwprintw(WINDOWS.info, 0, 0, str);
    inforefresh();
}

// must call mainrefresh after
void set_character_pixel(const int x, const int y, const void* pixelData) {
    wmove(WINDOWS.main, x, y);
    waddch(WINDOWS.main, *((char*)pixelData));
}

// Close down Terminal
void cleanup() {
    std::cout << "\n";
    delwin(WINDOWS.main);
    delwin(WINDOWS.info);
    endwin();
}
