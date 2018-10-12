#include "rayterm.h"
#include <iostream>
#include <ncurses.h>

std::string getHello() {
    return "Hello World!";
}

int main (int argc, char *argv[]) {

    // initalize ncurses
    initscr();
    // this doesn't work for some reason
    cbreak();
    noecho();
    keypad(stdscr, true);

    // do fancy hello stuff
    wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);
    move(1,1);
    attron(A_STANDOUT);
    addstr(getHello().c_str());
    attroff(A_STANDOUT);

    // show changes
    refresh();

    std::cout << getch() << "\n";

    // do cleanup/exit
    endwin();
}
