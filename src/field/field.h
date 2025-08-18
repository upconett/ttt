#ifndef FIELD_H
#define FIELD_H


#include <stdlib.h>


struct field {
    char** cells;
};

struct pos {
    short x;
    short y;
};


struct field* create_field();
void destroy_field(struct field* this);
void fill_with_char(struct field* f, const char c);
char cell_at(struct field* f, short x, short y);


#endif
