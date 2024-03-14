#include <stdio.h>
#include <stdlib.h>

/*
    1)
     a) Créer un float 'f1' sur la pile
     b) Affecter sa valeur à 5
     c) Affecter sa valeur à 10 en passant par un pointeur
     d) Créer un float 'f2' sur la pile
     c) Affecter sa valeur à 20 en passant par le même pointeur
*/
void exo1() {
    float f1 = 5;
    float* pi = &f1;
    *pi = 10;
    printf("%f\n", f1);
    float f2;
    pi = &f2;
    *pi = 20;
    printf("%f\n", f2);
}
/*
    2)
     a) Créer un float 'pf1' sur le tas
     b) Affecter la valeur 5 à l'espace mémoire alloué
     c) créer un float 'pf2' sur le tas
     d) Échanger les valeurs des deux pointeurs 'pf2' devra pointer sur le premier espace
     mémoire alloué et 'pf1' sur le deuxième
     c) Libérer l'espace mémoire dans l'ordre de l'allocation
*/
void exo2() {
    float* pf1 = (float*) malloc(sizeof(float));
    if (pf1 == NULL) {
        exit(1);
    }
    *pf1 = 5;
    float* pf2 = (float*) malloc(sizeof(float));
    if (pf2 == NULL) {
        exit(1);
    }
    float* pf3 = &pf1;
    pf1 = &pf2;
    pf2 = &pf3;
    printf("pf1 : %f, pf2 : %f\n", pf1, pf2);
    free(pf1);
    free(pf2);
}
int main()
{
    exo1();
    exo2();
    return 0;
}
