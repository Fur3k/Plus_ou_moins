#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char ask_input(const char* message, const char* authorizedinput, int size) {
	while (1) {
		char input;
		int i = 0;
		printf("%s", message);
		scanf_s("%c", &input, 1);
		while (getchar() != '\n');
		while (i != size) {
			if (authorizedinput[i] == input) {
				return input;
			}
			i++;
		}
	}
}

int ask_number(const char* message) {
	int i;
	while (1) {
		printf("%s", message);
		int IError = scanf_s("%d", &i);
		if (IError) {
			while (getchar() != '\n');
			return i;
		}
		while (getchar() != '\n');
	}
}

int game()
{
	srand(time(NULL));
	int guess = 0;
	int min = 0;
	int max = 0;
	while (min <= 0)
	{
		min = ask_number("Choississez la borne minimum : ");
	}
	while (max <= min) {
		max = ask_number("Choississez la borne maximum : ");
	}
	int nb_try = 6;
	int random_num = rand() %((max-min) + 1 - 1);
	random_num += 1 + min;
	while (guess != random_num) {
		while(guess < min || guess > max)
		{
			guess = ask_number("Choississez un nombre : ");
		}
		nb_try--;
		if (nb_try == 0) {
			printf("Perdu le nombre a deviner etait %d !\n", random_num);
			return 0;
		}
		else if (guess > random_num) {
			printf("C'est plus petit ! Il te reste %d essais !\n", nb_try);
			max = guess - 1;
		}
		else if(guess < random_num) {
			printf("C'est plus grand ! Il te reste %d essais !\n", nb_try);
			min = guess + 1;
		}
	}
	printf("You Win !\n");
	return random_num;
}

int restart() {
	char replay;
	replay = ask_input("Veux tu rejouer ? y/n : ", "yYnN",25);
	if (replay == 'y'|| replay == 'Y') {
		return 1;
	}
	else
	{
		return 0;
	}
}

int main() {
	int resultat[254] = { 0 };
	int taille_resultat = 254;
	int i = 0;
	int j = 0;
	resultat[i] = game(); 
	while (1) {
		if (restart()) {
			i++;
			if (i < taille_resultat) {
				resultat[i] = game();
			}
			else
			{
				printf("Vous avez fait le nombre de parties maximum !\n");
			}
		}
		printf("Voici les différents nombres a trouves durant votre session :\n");
		for (j = 0; j < taille_resultat; j++) {
			if (resultat[j] != 0) {
				printf("- Partie %d : %d\n", i + 1, resultat[j]);
			}
		}
		return 0;
	}
}