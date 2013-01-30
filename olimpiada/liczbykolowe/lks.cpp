#include<stdio.h>

//
// Oblicza największy wspólny dzielnik a i b (algorytm Euklidesa)
//

int gcd(int a, int b)
{
	if (a == 0) return b;
	if (b == 0) return a;
	
	if (a > b) return gcd(a % b, b);
	if (a < b) return gcd(a, b % a);
	
	return a;
}

//
// Oblicza symbol Jacobiego (m/n)
//

int jacobi(int m, int n)	
{
	if (n == 1) return 1;
	if (m == 1) return 1;
	
	if ( (m & 1) == 0) { // licznik parzysty
		if (m == 0) return 0;
		
		if (m == 2) {
			switch (n % 8) {
				case 1: case 7:
					return 1;
				case 3: case 5:
					return -1;
			}
		}
		
		return jacobi(m / 2, n) * jacobi(2, n);
	}
	
	// licznik nieparzysty
	
	if (m < n) {
		// z prawa odwrotności reszt kwadratowych
		
		if ((n % 4) == 1 || (m % 4) == 1) {
			return jacobi(n, m);
		} else {
			return -jacobi(n, m);
		}
	} else {
		return jacobi(m % n, n);
	}
}

//
// Oblicza a^{(n-1)/2} (mod n)
//

int apow(int a, long long int n)
{
	long long int p = 1, w = a; 
	long long int m = (n-1)/2;
	
	while (m > 0) {
		if (m & 1) { p = (p * w) % n; }
		w = (w * w) % n; m = m / 2;
	}

	return p;
}

//
// Test Solovaya-Strassena dla liczby n i świadka a
//

int SolovayStrassen(int n, int a)
{
	printf("  a = %d, n=%d, apow=%d jacobi=%d\n",a,n,apow(a,n),jacobi(a,n));

	if ((apow(a,n) - jacobi(a,n)) % n != 0) return true;
		
	return false;
}

int testPierwszosci(int n)
{
	for (int i = 2; i < 20 && i < n; i++) {
		if (SolovayStrassen(n,i)) return false;
	}
	return true;
}

int main()
{
	int n = 71119;
		
	for (int a = 2; a < 100; a++) {
		printf("n=%d, a=%d, złożona? %s\n", n,a,SolovayStrassen(n,a)?"TAK":"NIE");
	}
	
	return 0;
}
