#include <iostream>
#include <sstream>
#include "terminal.hpp"

int main (int argc, char *argv[]) {

    printf("Starting RayTerm...\n");

    // initalize ncurses
    setup();


    // do fancy hello stuff
    wborder(WINDOWS.main, 0, 0, 0, 0, 0, 0, 0, 0);
    wmove(WINDOWS.main, 1,1);
    waddstr_attr(WINDOWS.main, "Hello World from the main screen", A_BOLD);
    set_info_string("INFO WINDOW");

    // show changes
    allrefresh();

    int key = 0;
    int frames = 0;
    while((key = getch()) != 0) {
        std::stringstream s;
        s << "KEY: " << key << "; LINES: " << LINES << "; COLS: " << COLS << "; FRAME: " << frames++;
        set_info_string(s.str().c_str());

        if(key == '\n') {
            cleanup();
            printf("Got EXIT, exiting\n");
            break;
        } else if (key == KEY_RESIZE) {
            handle_resize();
        }
    }

    // do cleanup/exit
    cleanup();
}
