#include <iostream>
#include "terminal.hpp"

int main (int argc, char *argv[]) {

    printf("Starting RayTerm...\n");

    // initalize ncurses
    setup();


    // do fancy hello stuff
    wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);
    move(1,1);
    attron(A_BOLD);
    addstr("Hello World");
    attroff(A_BOLD);

    // show changes
    refresh();
    getch();

    // do cleanup/exit
    cleanup();
}
