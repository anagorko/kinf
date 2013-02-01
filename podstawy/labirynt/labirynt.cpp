#include<stdio.h>

int main()
{
	int s = 0;

	printf("LABIRYNT\n");
	printf("--------\n\n");

	do {
		switch (s) {
		case 0: printf("Dwa dni temu wdepłeś do tego labiryntu. Zraniłeś się w głowe wchodząc do niego, i znalazłeś jakieś ruskie zioła. Musisz szybko coś zrobić bo zginiesz! Z komnaty, w której się znajdujesz są dwa wyjścia: na lewo (l) i na prawo (p). Po prawej stronie czujesz zapach ziół takich jak twoje...\n");
			break;
		case 1: printf("Idziesz długim korytarzem, na którego końcu jest rozwidlenie. Idziesz w lewo (l) czy w prawo (p)?\n");
			break;
		case 2: printf(". Z każdym krokiem owiewa Cię coraz silniejszy, zapach miejskiego jedzenia. Możesz zawrócić (z) lub iść dalej (d).\n");
			break;
		case 3: printf("Znalazłeś się w ogromnej jaskini. Możesz udać się na jej północny koniec (p),  gdzie widzisz schody z milionami trzonów. Możesz też wrócić tam, skąd przyszedłeś (w).\n");
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
				printf("To był TRZONOWIEC, który nażarł się zioł. Niestety zjadł cię...\n");
				s = 1001; 
			}
			break;
		case 1:
			if (c == 'l') { s = 2; }
			if (c == 'p') { s = 3; }
			break;
		case 2: if (c == 'z') { s = 1; }
			if (c == 'd') { 
				printf("Tam trafiłeś na napis WYJŚCIE, jednak przechodząc, będąc pewnym szczęścia, nie zauważyłeś zapadki prowadzącej do jadalni głodnych TRZONOWCÓW...\n");
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

