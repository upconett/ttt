// code by upco


#ifndef GAME_H
#define GAME_H


#include "field/field.h"


struct game_data {
    struct field* field;
    char current_player;
    short turn_num;
};

struct game_data* create_game_data();
void destroy_game_data(struct game_data*);

char determine_winner(struct field* f);


#endif
