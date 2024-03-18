#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tile {
    int isFlag;
    int isBomb;
    int isDiscover;
    int x;
    int y;
}Tile;

typedef struct Grid {
    int size;
    Tile** tiles;
} Grid;



int place_bomb(Grid* grid) {
    srand(time(NULL));
    int limit_bomb = 20;
    for (int i = 0; i < limit_bomb; i++) {
        int random_x = rand() % (grid->size + 1 - 1);
        int random_y = rand() % (grid->size + 1 - 1);
        grid->tiles[random_x][random_y].isBomb = 1;
    }
    return grid;
}

int create_grid(Grid* grid) {
    grid->tiles = (Tile**) malloc(grid->size * sizeof(Tile*));
    for (int i = 0; i < grid->size; i++) {
        grid->tiles[i] = (int*)malloc(grid->size * sizeof(int));
        for (int j = 0; j < grid->size; j++) {
            grid->tiles[i][j].isDiscover = 0;
        }
    }
    return grid->tiles;
}


void show_grid(Grid* grid) {
    for (int i = 0; i < grid->size; i++) {
        for (int j = 0; j < grid->size; i++) {
            printf("%d", grid->tiles[i][j]);
        }
        printf("\n");
    }
}

int game() {
    Grid g;
    g.size = 10;
    create_grid(&g);
    place_bomb(&g);
    show_grid(&g);
}
int main()
{
    game();
    return 0;
}