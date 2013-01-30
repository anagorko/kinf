#include<cstdio>

int main()
{
	int x, y;

	printf("----------------------------------\n");

	for (y = 0; y < 30; y++) {
		for (x = 0; x < 30; x++) {
			if ((x-14)*(x-14) + (y-14)*(y-14) < 100) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("----------------------------------\n");

	return 0;
}
