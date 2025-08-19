// code by upco


#include <stdio.h>

#include "ui.h"

void scan_minus_one(struct pos* p) {
    scanf("%hu%hu", &p->x, &p->y);
    p->x--; p->y--;
}

void input_and_render(struct game_data* d, struct pos* p) {
    printf("Turn of '%c': ", d->current_player);
    scan_minus_one(p);

    while (1) {
        if ((p->x < 0 || p->x > 2) ||
            (p->y < 0 || p->y > 2)) {
            printf("Enter only numbers 1-3: ");
            scan_minus_one(p);
        }
        else if (cell_at(d->field, p->x, p->y) != '\0') {
            printf("Cell [%hu,%hu] already occupied: ", p->x+1, p->y+1);
            scan_minus_one(p);
        }
        else {
            break;
        }
    }
}

void render_field(struct field* f) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char c = cell_at(f, i,j);
            if (c == '\0') c = '-';
            printf("%c ", c);
        }
        printf("\n");
    }
    printf("\n");
}


void pass_turn(struct game_data* d) {
    if (d->current_player == 'x') d->current_player = 'o';
    else                          d->current_player = 'x';
}


void init_ui() {
    printf("\nTTT (Tic Tac Toe)\nusing terminal render\n");
}

void run_game() {
    struct game_data* d = create_game_data();
    struct pos current_pos = {0, 0};
    char winner = '\0';

    render_field(d->field);

    int c = 0;
    for (; c < 9; c++) {
        input_and_render(d, &current_pos);
        set_cell(d->field, current_pos, d->current_player);
        pass_turn(d);
        render_field(d->field);
        winner = determine_winner(d->field);
        if (winner != '\0') {
            printf("The winner is: '%c'\n", winner);
            break;
        }
    }
    if (c == 9) printf("Draw\n");
    
    destroy_game_data(d);
}

void quit_ui() {
    printf("\nSee you!\n\n");
}
