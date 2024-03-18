#include <stdio.h>
#include <stdlib.h>

typedef struct Grid {
    int size;
} Grid;

typedef struct Tile {
    int x;
    int y;
}Tile;

void create_grid() {
    Grid g;
    g.size = 5;
    int* l = (int*) malloc(g.size * sizeof(int));
    for (int i = 0; i < g.size; i++) {
        l[i] = (int*) malloc(g.size * sizeof(int));
    }
}


int main()
{
    create_grid();
    return 0;
}
