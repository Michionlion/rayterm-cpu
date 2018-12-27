#include "stdio.h"
#include "terminal.h"
#include "translator.h"

int main (int argc, char *argv[]) {

    // initalize ncurses
    setup();


    // do fancy hello stuff
    wborder(WINDOWS.main, 0, 0, 0, 0, 0, 0, 0, 0);
    wmove(WINDOWS.main, 1,1);
    waddstr_attr(WINDOWS.main, "Hello World from the main screen", A_BOLD);
    set_info_string("INFO WINDOW");

    // show changes
    allrefresh();


    render();

    int key = 0;
    int frames = 0;
    while((key = getch()) != 0) {
        if(key == '\n') {
            printf("Got ENTER, exiting\n");
            break;
        } else if (key == KEY_RESIZE) {
            handle_resize();
        }
    }

    // do cleanup/exit
    cleanup();
}
