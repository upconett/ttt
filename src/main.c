#include "stdio.h"

#include "field/field.h"
#include "render/render.h"


int horizontal_win_line(struct field* f, short y) {
    char c1 = cell_at(f, 0,y);
    char c2 = cell_at(f, 1,y);
    char c3 = cell_at(f, 2,y);
    if (c1 == c2 && c2 == c3) {
        switch (c1) {
            case 'o': return 0;
            case 'x': return 1;
            default: return -1;
        }
    } return -1;
}

int vertical_win_line(struct field* f, short x) {
    char c1 = cell_at(f, x,0);
    char c2 = cell_at(f, x,1);
    char c3 = cell_at(f, x,2);
    if (c1 == c2 && c2 == c3) {
        switch (c1) {
            case 'o': return 0;
            case 'x': return 1;
            default: return -1;
        }
    } return -1;
}

int diagonal_win_left(struct field* f) {
    char c1 = cell_at(f, 0,0);
    char c2 = cell_at(f, 1,1);
    char c3 = cell_at(f, 2,2);
    if (c1 == c2 && c2 == c3) {
        switch (c1) {
            case 'o': return 0;
            case 'x': return 1;
            default: return -1;
        }
    } return -1;
}

int diagonal_win_right(struct field* f) {
    char c1 = cell_at(f, 2,0);
    char c2 = cell_at(f, 1,1);
    char c3 = cell_at(f, 0,2);
    if (c1 == c2 && c2 == c3) {
        switch (c1) {
            case 'o': return 0;
            case 'x': return 1;
            default: return -1;
        }
    } return -1;
}

int determine_winner(struct field* f) {
    short winner;
    for (int i = 0; i < 3; i++) {
        winner = horizontal_win_line(f, i);
        if (winner != -1) return winner;
        winner = vertical_win_line(f, i);
        if (winner != -1) return winner;
    }
    winner = diagonal_win_left(f);
    if (winner != -1) return winner;
    winner = diagonal_win_right(f);
    return winner;
}

int main() {
    struct field* f = create_field();
    fill_with_char(f, '-');

    render_field(f);

    int x, y;
    int turn = 1;  // 0 is 'o', 1 is 'x'
    short winner = -1;

    int c = 0;
    while (c < 9) {
        printf("Turn of '%c': ", (turn == 0 ? 'o' : 'x'));
        scanf("%d", &x);
        scanf("%d", &y);
        if ((x < 0 || x > 3) || (y < 0 || y > 3)) {
            printf("What? Only type 0, 1 or 2\n");
        } else if (f->cells[x][y] != '-') {
            printf("Already occupied\n");
        } else {
            if (turn) f->cells[x][y] = 'x'; 
            else      f->cells[x][y] = 'o';
            turn = !turn;

            render_field(f);

            winner = determine_winner(f);
            if (winner != -1) {
                char win_char = (winner == 0 ? 'o' : 'x');
                printf("The winner is: '%c'\n", win_char);
                break;
            }
            c++; // new turn there
        }
    }

    if (c == 9) printf("Draw\n");

    destroy_field(f);
    return 0;
}
