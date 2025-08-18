#include "field/field.h"


struct field* create_field() {
    struct field* this = malloc(sizeof(struct field));
    this->cells = calloc(3, sizeof(char*));
    for (int i = 0; i < 3; i++) {
        this->cells[i] = calloc(3, sizeof(char));
    }
    return this;
};

void destroy_field(struct field* this) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->cells[i][j] = '\0';
        }
        free(this->cells[i]);
    }
    free(this->cells);
    free(this);
};

void fill_with_char(struct field* f, const char c) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            f->cells[i][j] = c;
        }
    }
}

char cell_at(struct field* f, short x, short y) {
    return f->cells[x][y];
}
