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

    WINDOWS.main = subwin(stdscr, LINES-2, 0, 0, 0);
    WINDOWS.info = subwin(stdscr, 2, 0, LINES-2, 0);
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

void handle_resize() {
    wclear(WINDOWS.main);
    wclear(WINDOWS.info);

    wmove(stdscr, 0, 0);
    wresize(stdscr, LINES, COLS);
    wmove(WINDOWS.main, 0, 0);
    wresize(WINDOWS.main, LINES - 2, COLS);
    wmove(WINDOWS.info, LINES - 2, 0);
    wresize(WINDOWS.info, 2, COLS);
    allrefresh();
}

void waddstr_attr(WINDOW* window, char* str, chtype attr) {
    for(int i = 0; str[i] != '\0'; i++) {
        waddch(window, str[i] | attr);
    }
}

void mainloop() {

}

// Close down Terminal
void cleanup() {
    std::cout << "\n";
    delwin(WINDOWS.main);
    delwin(WINDOWS.info);
    endwin();
}
