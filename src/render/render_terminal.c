#include "stdio.h"

#include "render/render.h"


void render_field(struct field* f) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", cell_at(f, i,j));
        }
        printf("\n");
    }
    printf("\n");
}
