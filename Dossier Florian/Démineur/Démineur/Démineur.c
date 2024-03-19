#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tile {
    int isFlag;
    int isBomb;
    int isDiscover;
    int near_bomb;
    char value;
    int x;
    int y;
}Tile;

typedef struct Grid {
    int size;
    Tile** tiles;
} Grid;

int ask_number(const char* message, Grid* grid) {
    int i;
    while (1) {
        printf("%s", message);
        int IError = scanf_s("%d", &i);
        if (IError) {
            if (i < grid->size && i >= 0) {
                while (getchar() != '\n');
                return i;
            }
        }
        while (getchar() != '\n');
    }
}

int place_bomb(Grid* grid) {
    srand(time(NULL));
    int limit_bomb = 10;
    int i = 0;
    while(i < limit_bomb) {
        int random_x = rand() % (grid->size);
        int random_y = rand() % (grid->size);
        if (!grid->tiles[random_x][random_y].isBomb) {
            grid->tiles[random_x][random_y].isBomb = 1;
            i++;
        }
    }
    return grid;
}

int test_bomb(int row, int col, Grid* grid) {
    if (grid->tiles[row][col].isBomb) {
        return 1;
    }
    return 0;
}

void setvalue(Grid* grid) {
    for (int row = 0; row < grid->size; row++) {
        for (int col = 0; col < grid->size; col++) {
            if (!test_bomb(row, col, grid)){
                int val = 0;
                int row_start = row - 1;
                int col_start = col - 1;
                int row_end = row + 1;
                int col_end = col + 1;
                if (row_start < 0) {
                    row_start++;
                }
                if (row_end >= grid->size) {
                    row_end--;
                }
                if (col_start < 0) {
                    col_start++;
                }
                if (col_end >= grid->size) {
                    col_end--;
                }
                for (int i = row_start; i <= row_end; i++) {
                    for (int j = col_start; j <= col_end; j++)
                    {
                        if (test_bomb(i, j, grid)) {
                            val++;
                        }
                    }
                }
                grid->tiles[row][col].near_bomb = val;
            }
        }
    }
}
void create_grid(Grid* grid) {
    grid->tiles = (Tile**) malloc(grid->size * sizeof(Tile*));
    for (int i = 0; i < grid->size; i++) {
        grid->tiles[i] = (Tile*)malloc(grid->size * sizeof(Tile));
        for (int j = 0; j < grid->size; j++) {
            grid->tiles[i][j].isDiscover = 0;
            grid->tiles[i][j].isFlag = 0;
            grid->tiles[i][j].isBomb = 0;
            grid->tiles[i][j].near_bomb = 0;
            grid->tiles[i][j].value = '?';
        }
    }
}



void propag(int row, int col, Grid* grid) {
    int row_start = row - 1;
    int col_start = col - 1;
    int row_end = row + 1;
    int col_end = col + 1;
    if (row_start < 0) {
        row_start++;
    }
    if (row_end >= grid->size) {
        row_end--;
    }
    if (col_start < 0) {
        col_start++;
    }
    if (col_end >= grid->size) {
        col_end--;
    }
    for (int i = row_start; i <= row_end; i++) {
        for (int j = col_start; j <= col_end; j++)
        {
            if (!grid->tiles[i][j].isDiscover && !grid->tiles[i][j].isFlag) {
                if (!test_bomb(i, j, grid)) {
                    grid->tiles[i][j].isDiscover = 1;
                    if (grid->tiles[i][j].near_bomb > 0) {
                        grid->tiles[i][j].value = grid->tiles[i][j].near_bomb + '0';
                    }
                    else
                    {
                        grid->tiles[i][j].value = '0';
                        propag(i, j, grid);
                    }
                }
            }
        }
    }
}

void ask_tile(Grid* grid) {
    while (1)
    {
        int row = ask_number("Choississez la ligne : ", grid);
        int col = ask_number("Choississez la colonne : ", grid);
        if (!grid->tiles[row][col].isDiscover && !grid->tiles[row][col].isFlag) {
            grid->tiles[row][col].isDiscover = 1;
            if (test_bomb(row, col, grid)) {
                grid->tiles[row][col].value = 'B';
            }
            else
            {
                if (grid->tiles[row][col].near_bomb > 0) {
                    grid->tiles[row][col].value = grid->tiles[row][col].near_bomb + '0';
                }
                else
                {
                    grid->tiles[row][col].value = '0';
                    propag(row, col, grid);
                }
            }
            return 0;
        }
    }
}

void show_grid(Grid* grid) {
    for (int i = 0; i < grid->size; i++) {
        for (int j = 0; j < grid->size; j++) {
            printf(" %c |", grid->tiles[i][j].value);
        }
        printf("\n");
    }
}

int game() {
    Grid g;
    g.size = 10;
    create_grid(&g);
    place_bomb(&g);
    setvalue(&g);
    while (1) {
        show_grid(&g);
        ask_tile(&g);
    }
    return 0;
}
int main()
{
    game();
    return 0;
}