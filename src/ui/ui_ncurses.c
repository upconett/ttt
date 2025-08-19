// code by upco


#include <signal.h>
#include <ncurses.h>
#include <unistd.h>

#include "ui/ui.h"


#define COLOR_GRAY 


void init_ui() {
    initscr();
    raw();
    noecho();
    halfdelay(0);
    keypad(stdscr, TRUE);

    curs_set(0);

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);   
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, 8, COLOR_BLACK);
}

void quit_ui() {
    endwin();
}

void print_title();
void print_movement();
void print_interract();
void print_exit();
void print_turn(char);
void print_winner(char);
void print_draw();
void print_press_any_key();

void print_field(struct field* f, struct pos* cur, int col, int row) {
    for (int i = 0; i < 3; i++) {
        move(col+i, row);
        for (int j = 0; j < 4; j++) {
            char c = cell_at(f, i,j);
            if (c == '\0') c = '.';
            if (i == cur->x && j == cur->y+1 && j == 3) { 
                attron(COLOR_PAIR(3)); addch('>'); attroff(COLOR_PAIR(3));
            } else if (j == 3) {
                addch(' ');
            } else if (i == cur->x && j == cur->y) {
                attron(COLOR_PAIR(3)); addch('<'); attroff(COLOR_PAIR(3));
                printw("%c", c);
            } else if (i == cur->x && j == cur->y+1) { 
                attron(COLOR_PAIR(3)); addch('>'); attroff(COLOR_PAIR(3));
                printw("%c", c);
            } else {
                printw(" %c", c);
            }
        }
    }
}

void render_ui(struct game_data* d, struct pos* cur) {
    move(1, 1); print_title();
    print_field(d->field, cur, 3, 1);
    move(3, 10); print_movement();
    move(4, 10); print_interract();
    move(5, 10); print_exit();
    move(7, 1); print_turn(d->current_player);
    refresh();
}

void render_ui_and_winner(struct game_data* d, char winner) {
    struct pos cur = {-2, -2};
    render_ui(d, &cur);
    move(7, 1); print_winner(winner);
    move(9, 1); print_press_any_key();
    refresh();
}

void render_ui_and_draw(struct game_data* d, char winner) {
    struct pos cur = {-2, -2};
    render_ui(d, &cur);
    move(7, 1); print_draw();
    move(9, 1); print_press_any_key();
    refresh();
}

void print_title() {
    printw("Welcome to TTT ");
    attron(COLOR_PAIR(4)); printw("(Tic Tac Toe, btw)"); attroff(COLOR_PAIR(4));
}

void print_movement() {
    printw("move with ");
    attron(COLOR_PAIR(2)); printw("arrows"); attroff(COLOR_PAIR(1));
    printw(", ");
    attron(COLOR_PAIR(2)); printw("wasd "); attroff(COLOR_PAIR(1));
    printw("or ");
    attron(COLOR_PAIR(2)); printw("hjkl"); attroff(COLOR_PAIR(1));
}

void print_interract() {
    printw("interract with ");
    attron(COLOR_PAIR(1)); printw("enter "); attroff(COLOR_PAIR(1));
    printw("or ");
    attron(COLOR_PAIR(1)); printw("spacebar"); attroff(COLOR_PAIR(1));
}

void print_exit() {
    printw("quit the game with ");
    attron(COLOR_PAIR(1)); printw("ctrl-c "); attroff(COLOR_PAIR(1));
    printw("or ");
    attron(COLOR_PAIR(1)); printw("esc"); attroff(COLOR_PAIR(1));
}

void print_turn(char turn) {
    printw("It's turn of '");
    attron(COLOR_PAIR(3)); printw("%c", turn); attroff(COLOR_PAIR(3));
    printw("'");
}

void print_winner(char winner) {
    printw("Congrats, '");
    attron(COLOR_PAIR(3)); printw("%c", winner); attroff(COLOR_PAIR(3));
    printw("' has won!");
}

void print_press_any_key() {
    attron(COLOR_PAIR(4)); 
    printw("press any key...");
    attroff(COLOR_PAIR(4)); 
}

void print_draw() {
    printw("Oh, ");
    attron(COLOR_PAIR(4)); printw("nobody"); attroff(COLOR_PAIR(4));
    printw(" won, it seems...");
}


short is_up_key(int ch) {
    return (ch == KEY_UP || ch == 'k' || ch == 'w');
}

short is_down_key(int ch) {
    return (ch == KEY_DOWN || ch == 'j' || ch == 's');
}

short is_left_key(int ch) {
    return (ch == KEY_LEFT || ch == 'h' || ch == 'a');
}

short is_right_key(int ch) {
    return (ch == KEY_RIGHT || ch == 'l' || ch == 'd');
}

short is_enter_key(int ch) {
    return (ch == '\n' || ch == ' ');
}

short is_quit_key(int ch) {
    return (ch == 3 || ch == 27);
}

short is_direction_key(int ch) {
    return (
        is_up_key(ch) ||
        is_left_key(ch) ||
        is_right_key(ch) ||
        is_down_key(ch)
    );
}

short eq_pos(struct pos* p1, struct pos* p2) {
    return (p1->x == p2->x && p1->y == p2->y);
}


void input_and_render(struct game_data* d, struct pos* p) {
    short chosen = 0;
    struct pos cursor_p = *p;
    while (!chosen) {
        render_ui(d, &cursor_p);
        int ch = getch();
        if (is_enter_key(ch)) {
            if (cell_at(d->field, cursor_p.x, cursor_p.y) != '\0') {
                // TODO : add error animation
                continue;
            } else {
                p->x = cursor_p.x;
                p->y = cursor_p.y;
                chosen = TRUE;
            }
        } 
        else if (is_up_key(ch) && cursor_p.x > 0) {
            cursor_p.x--;
        }
        else if (is_left_key(ch) && cursor_p.y > 0) {
            cursor_p.y--;
        }
        else if (is_down_key(ch) && cursor_p.x < 2) {
            cursor_p.x++;
        }
        else if (is_right_key(ch) && cursor_p.y < 2) {
            cursor_p.y++;
        }
        else if (is_quit_key(ch)) {
            raise(SIGINT);
        }
    }
}


void pass_turn(struct game_data* d) {
    if (d->current_player == 'x') d->current_player = 'o';
    else                          d->current_player = 'x';
}


void run_game() {
    struct game_data* d = create_game_data();
    struct pos current_pos = {0, 0};
    char winner = '\0';

    int c = 0;
    for (; c < 9; c++) {
        input_and_render(d, &current_pos);
        set_cell(d->field, current_pos, d->current_player);
        pass_turn(d);
        winner = determine_winner(d->field);
        if (winner != '\0') {
            render_ui_and_winner(d, winner);
            cbreak(); getch();
            break;
        }
    }
    if (c == 9) {
        render_ui_and_draw(d, winner);
        cbreak(); getch();
    }
    
    destroy_game_data(d);
}
