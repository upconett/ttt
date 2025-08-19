// code by upco


#include "game/game.h"


#pragma region game_data

struct game_data* create_game_data() {
    struct game_data* this = malloc(sizeof(struct game_data));
    this->field = create_field();
    fill_with_char(this->field, '\0');
    this->current_player = 'x';
    this->turn_num = 0;
    return this;
}

void destroy_game_data(struct game_data* this) {
    destroy_field(this->field);
    free(this);
}

#pragma endregion


#pragma region winner

short have_winner(char* winner, char c1, char c2, char c3) {
    if (c1 == c2 && c2 == c3) *winner = c1;
    else                      *winner = '\0';
    return (*winner != '\0');
}

short horizontal_win_line(char* winner, struct field* f, short y) {
    char c1 = cell_at(f, 0,y);
    char c2 = cell_at(f, 1,y);
    char c3 = cell_at(f, 2,y);
    return have_winner(winner, c1, c2, c3);
}

short vertical_win_line(char* winner, struct field* f, short x) {
    char c1 = cell_at(f, x,0);
    char c2 = cell_at(f, x,1);
    char c3 = cell_at(f, x,2);
    return have_winner(winner, c1, c2, c3);
}

short diagonal_win_left(char* winner, struct field* f) {
    char c1 = cell_at(f, 0,0);
    char c2 = cell_at(f, 1,1);
    char c3 = cell_at(f, 2,2);
    return have_winner(winner, c1, c2, c3);
}

short diagonal_win_right(char* winner, struct field* f) {
    char c1 = cell_at(f, 2,0);
    char c2 = cell_at(f, 1,1);
    char c3 = cell_at(f, 0,2);
    return have_winner(winner, c1, c2, c3);
}

char determine_winner(struct field* f) {
    char wnr;
    for (int i = 0; i < 3; i++) {
        if (horizontal_win_line(&wnr, f, i)) return wnr;
        if (vertical_win_line(&wnr, f, i)) return wnr;
    }
    if (diagonal_win_left(&wnr, f)) return wnr;
    diagonal_win_right(&wnr, f); // return anyway
    return wnr;
}

#pragma endregion
