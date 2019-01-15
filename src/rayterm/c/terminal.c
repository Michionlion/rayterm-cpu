#include "terminal.h"
#include "stdio.h"

TERMINAL* setup() {
    initscr();
    start_color();
    cbreak();
    noecho();

    curs_set(0);


    init_pair(1,COLOR_WHITE, COLOR_BLUE);
    init_pair(2,COLOR_WHITE, COLOR_GREEN);

    TERMINAL* term = (TERMINAL*) malloc(sizeof(TERMINAL));
    term->main = subwin(stdscr, LINES-1, 0, 0, 0);
    term->info = subwin(stdscr, 1, 0, LINES-1, 0);
    wbkgd(term->main, COLOR_PAIR(2));
    wbkgd(term->info, COLOR_PAIR(1));

    keypad(term->main, true);
    keypad(term->info, true);
}

void allrefresh() {
    
}

/* don't handle resizing for now
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
*/

VECTOR* get_size(WINDOW* win) {
    VECTOR* sizes = (VECTOR*) malloc(sizeof(VECTOR));
    getmaxyx(win, sizes->y, sizes->x);

    return sizes;
}

void add_str(WINDOW* window, const char* str, chtype attr) {
    for(int i = 0; str[i] != '\0'; i++) {
        waddch(window, str[i] | attr);
    }
}

// auto-refreshes info window
void set_info_string(TERMINAL* term, const char* str) {
    wclear(term->info);
    mvwprintw(term->info, 0, 0, str);
    wrefresh(term->info);
}

// must call refresh after
void set_character_pixel(TERMINAL* term, const POINT* position, const char, const Color background, const Color foreground) {
    wmove(term->main, x, y);
    chtype pixel = char | 
    waddch(term->main, *((char*)pixelData));
}

// Close down Terminal
void cleanup() {
    delwin(WINDOWS.main);
    delwin(WINDOWS.info);
    endwin();
    printf("\n");
}
