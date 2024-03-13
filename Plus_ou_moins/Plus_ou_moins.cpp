#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int ask_input(const char* message, const char* authorizedinput, int size) {
	char input;
	while (1) {
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

int ask_number(int min, int max) {
	int i;
	while (1) {
		printf("Choississez un nombre entre %d et %d : ", min, max);
		scanf_s("%d", &i);
		if (min <= i && 1<= max) {
			return i;
		}
	}
}

int game()
{
	srand(time(NULL));
	int guess = 0;
	int min;
	int max = 0;
	printf("Choississez la borne minimum :\n");
	scanf_s("%d", &min);
	while (max <= min) {
		printf("Choississez la borne maximum :\n");
		scanf_s("%d", &max);
	}
	int nb_try = 6;
	int random_num = rand() %((max-min) + 1 - 1);
	random_num += 1 + min;
	printf("%d\n", random_num);
	while (guess != random_num) {
		guess = ask_number(min, max);
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
	return 0;
}

bool restart() {
	char replay[256];
	replay[0] = ask_input("Veux tu rejouer ? y/n : ", "yYnN",25);
	if (replay[0] == 'y'|| replay[0] == 'Y') {
		return true;
	}
	else
	{
		return false;
	}
}

int main() {
	game();
	while (1) {
		if (restart()) {
			game();
		}
		else
		{
			return 0;
		}
	}
}
