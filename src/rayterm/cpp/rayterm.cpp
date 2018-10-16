#include <iostream>
#include "terminal.hpp"

int main (int argc, char *argv[]) {

    printf("Starting RayTerm...\n");

    // initalize ncurses
    setup();


    // do fancy hello stuff
    wborder(WINDOWS.main, 0, 0, 0, 0, 0, 0, 0, 0);
    wmove(WINDOWS.main, 1,1);
    waddstr_attr(WINDOWS.main, "Hello World from the main screen", A_BOLD);
    waddstr(WINDOWS.info, "Info Screen");
    wmove(WINDOWS.info, 1, 0);
    waddstr(WINDOWS.info, "And again!");

    // show changes
    allrefresh();

    int key;
    while(key = getch()) {
        wclear(WINDOWS.info);
        mvwprintw(WINDOWS.info, 0, 0, "KEY: %d; LINES: %d; COLS: %d", key, LINES, COLS);
        inforefresh();
        mainloop();

        if(key == '\n') {
            cleanup();
            printf("Got EXIT, exiting\n");
            break;
        } else if (key == KEY_RESIZE) {
            wresize(WINDOWS.main, LINES - 2, 0);
        }
    }

    // do cleanup/exit
    cleanup();
}
