#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tile {
    int isFlag;
    int isBomb;
    int isDiscover;
    char value;
    int near_bomb;
    int x;
    int y;
}Tile;

typedef struct Grid {
    int size;
    Tile** tiles;
} Grid;

//Vérification de la valdité de l'input de l'utilisateur
int ask_number(const char* message, Grid* grid) {
    int i;
    while (1) {
        printf("%s", message);
        int IError = scanf_s("%d", &i);
        while (getchar() != '\n');
        if (IError) {
            if (i < grid->size && i >= 0) {
                return i;
            }
        }
    }
}

//Place les bombes dans le Démineur à une position différente de la première tuile découverte et ses tuiles adjacentes
int place_bomb(Grid* grid, int row, int col) {
    srand(time(NULL));

    int limit_bomb = grid->size/2;
    int i = 0;
    char** list_pos = (char**)malloc(grid->size * sizeof(char*));
    for (int x = 0; x < grid->size; x++) {
        list_pos[x] = (int*)malloc(grid->size * sizeof(char));
        for (int y = 0; y < grid->size; y++) {
            list_pos[x][y] = grid->tiles[x][y].value ;
        }
    }
    //tuiles adjacentes à la tuile découverte
    list_pos[row-1][col-1] = '0';
    list_pos[row-1][col] = '0';
    list_pos[row-1][col+1] = '0';
    list_pos[row][col-1] = '0';
    list_pos[row][col+1] = '0';
    list_pos[row+1][col-1] = '0';
    list_pos[row+1][col] = '0';
    list_pos[row+1][col+1] = '0';
    while(i < limit_bomb) {
        int random_x = rand() % (grid->size);
        int random_y = rand() % (grid->size);
        if (!grid->tiles[random_x][random_y].isBomb && list_pos[random_x][random_y] != '0') {
            grid->tiles[random_x][random_y].isBomb = 1;
            i++;
        }
    }
    return grid;
}

//Vérifie si la case est une bombe ou non
int test_bomb(int row, int col, Grid* grid) {
    if (grid->tiles[row][col].isBomb) {
        return 1;
    }
    return 0;
}

//Set la valeur de nearbomb qui sert à savoir le nombre de bombes autour de la tuile
void setvalue(Grid* grid) {
    for (int row = 0; row < grid->size; row++) {
        for (int col = 0; col < grid->size; col++) {
            if (!test_bomb(row, col, grid)){
                int val = 0;
                //Limite des tuiles pour le test des bombes
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

//Création du démineur de taille "size"
void create_grid(Grid* grid) {
    //Création d'un tableau de dimension 2 contenant des Tile
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

//Permet de découvrir les alentours de la tuile séléctionné tant que la valeur de nearbomb = 0
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
            if (!grid->tiles[i][j].isDiscover && !grid->tiles[i][j].isFlag) //Test si la tuile est caché et qu'il n'y a pas de drapeau
            {
                if (!test_bomb(i, j, grid)) {
                    grid->tiles[i][j].isDiscover = 1;
                    if (grid->tiles[i][j].near_bomb > 0) //Test si au moins 1 bombe est dans une tuile adjacente
                    {
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

//Demande à l'utilisateur la tuile qu'il veut découvrir
int ask_tile(Grid* grid, int first_tile) {
    while (1)
    {        
        int row = ask_number("Choississez la ligne : ", grid);
        int col = ask_number("Choississez la colonne : ", grid);
        if (!grid->tiles[row][col].isDiscover && !grid->tiles[row][col].isFlag) {
            grid->tiles[row][col].isDiscover = 1;
            if (test_bomb(row, col, grid)) {
                grid->tiles[row][col].value = 'B';
                return 1;
            }
            else
            {
                if (grid->tiles[row][col].near_bomb > 0) //Test si au moins 1 bombe est dans une tuile adjacente
                {
                    grid->tiles[row][col].value = grid->tiles[row][col].near_bomb + '0';
                }
                else
                {
                    grid->tiles[row][col].value = '0';
                    if (first_tile) //Test si la tuile découverte est la première du démineur
                    {
                        place_bomb(grid, row, col);
                        setvalue(grid);
                    }
                    propag(row, col, grid);
                }
            }
            return 0;
            
        }
    }
}

//Demande à l'utilisateur où est ce qu'il veut poser/retirer un drapeau
int place_flag(Grid* grid) {
    int row = ask_number("Choississez la ligne : ", grid);
    int col = ask_number("Choississez la colonne : ", grid);
    if (!grid->tiles[row][col].isDiscover && !grid->tiles[row][col].isFlag) //Test si la tuile est caché et qu'il n'y a pas de drapeau
    {
        grid->tiles[row][col].isDiscover = 1;
        grid->tiles[row][col].isFlag = 1;
        grid->tiles[row][col].value = 'F';
    }
    else if (grid->tiles[row][col].isDiscover && grid->tiles[row][col].isFlag) // Test si la tuile est découverte et qu'il y a un drapeau
    {
        grid->tiles[row][col].isDiscover = 0;
        grid->tiles[row][col].isFlag = 0;
        grid->tiles[row][col].value = '?';
    }
    return 0;
}

//Demande à l'utilisateur s'il veut découvrir une tuile ou intéragir avec n drapeau
int ask_action(const char* message, Grid* grid) {
    int i;
    while (1) {
        printf("%s", message);
        int IError = scanf_s("%d", &i);
        while (getchar() != '\n');
        if (IError) {
            if (i == 1) {
                return ask_tile(grid, 0);
            }
            else if (i == 0) {
                return place_flag(grid);
            }
        }
    }
}

//Permet l'affichage du démineur
void show_grid(Grid* grid) {
    for (int i = -1; i < grid->size; i++) {
        if (i == -1) {
            printf("   |");
        }
        else
        {
            printf(" 0%d|", i);
        }
    }

    printf("\n");
    for (int i = 0; i < grid->size; i++) {
        printf(" 0%d|", i);
        for (int j = 0; j < grid->size; j++) {
            printf(" %c |", grid->tiles[i][j].value);
        }
        printf("\n");
    }
}

//Permet de lancer le jeu
int game() {
    Grid g;
    g.size = 10;
    create_grid(&g);
    show_grid(&g);
    ask_tile(&g, 1);
    while (1) {
        show_grid(&g);
        if (ask_action("Appuyez sur 1 pour decouvrir une case et sur 0 pour mettre un drapeau :", &g)) {
            show_grid(&g);
            printf("Vous avez perdu !");
            return 0;
        }
    }
    return 0; 
}
int main()
{
    game();
    return 0;
}