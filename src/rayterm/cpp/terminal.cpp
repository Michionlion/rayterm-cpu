#include "terminal.hpp"
#include <iostream>

// initialize global variable
Windows WINDOWS;

// Setup Terminal
void setup() {
    initscr();
    cbreak();
    noecho();
    delwin(stdscr);

    WINDOWS.main = newwin(LINES-2, 0, 0, 0);
    WINDOWS.info = newwin(2, 0, LINES-2, 0);

    keypad(stdscr, true);

}

// Close down Terminal
void cleanup() {
    std::cout << "\n";
    endwin();
}
