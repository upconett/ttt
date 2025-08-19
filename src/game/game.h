// code by upco


#ifndef GAME_H
#define GAME_H


#include "field/field.h"


struct game_data {
    struct field* field;
    char current_player;
    short turn_num;
};

struct win_row {
    struct pos p1;
    struct pos p2;
    struct pos p3;
};

short in_win_row(struct win_row* wr, short x, short y);

struct game_data* create_game_data();
void destroy_game_data(struct game_data*);

char determine_winner(struct field* f);
struct win_row get_win_row(struct field* f);


#endif
