#include<stdio.h>

int main()
{
	int s = 0;

	printf("LABIRYNT\n");
	printf("--------\n\n");

	do {
		switch (s) {
		case 0: printf("Dwa dni temu zabłąkałeś się do tego labiryntu. Umierasz z pragnienia i wyczerpania. Musisz szybko znaleźć wodę albo zginiesz! Z komnaty, w której się znajdujesz są dwa wyjścia: na lewo (l) i na prawo (p). Wydaje Ci się, że po prawej słychać szum wody...\n");
			break;
		case 1: printf("Idziesz długim korytarzem, na którego końcu jest rozwidlenie. Idziesz w lewo (l) czy w prawo (p)?\n");
			break;
		case 2: printf("To nie jest dobry kierunek. Z każdym krokiem owiewa Cię coraz silniejszy, trupi zapach, od którego zbiera Ci się na wymioty. Możesz zawrócić (z) lub iść dalej (d).\n");
			break;
		case 3: printf("Znalazłeś się w ogromnej jaskini. Możesz udać się na jej północny koniec (p), w którym widzisz światło. Możesz też wrócić tam, skąd przyszedłeś (w).\n");
			break;
		}

		printf("\nCo wybierasz? ");
		char c;
		do {
			c = getchar();
		} while (c == '\n');
		printf("\n");
	
		switch (s) {
		case 0:
			if (c == 'l') { s = 1; }
			if (c == 'p') { 
				printf("Szum wody dochodził z dna głębokiej przepaści. Nie jesteś pierwszym, który na jej dnie stracił życie...\n");
				s = 1001; 
			}
			break;
		case 1:
			if (c == 'l') { s = 2; }
			if (c == 'p') { s = 3; }
			break;
		case 2: if (c == 'z') { s = 1; }
			if (c == 'd') { 
				printf("Tam nie mogło czekać Cię nic dobrego...\n");
				s = 1001; 
			}
			break;
		case 3: if (c == 'w') { s = 1; }
			if (c == 'p') { 
				printf("Światło okazało się wyjściem z jaskini.\n");
				s = 1000;
			} 
			break;
		case 4: break;
		default:
			printf("Nie rozumiem!\n");
		}
	} while (s < 1000);

	switch (s) {
	case 1000:
		printf("\n\n***Wygrałeś***!\n");
		break;
	case 1001:
		printf("\n\nPRZEGRAŁEŚ! Spróbuj jeszcze raz.\n");
		break;
	}

	return 0;
}

