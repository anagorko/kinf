#include<stdio.h>

const int MAX = 1000000000;
const int MAXpierw = 31623;

int pwsza[MAXpierw + 1];
int pierwsze[MAXpierw + 1];
int lp = 0;



int hit = 0, lpierw = 0;


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
//	printf("  a = %d, n=%d, apow=%d jacobi=%d\n",a,n,apow(a,n),jacobi(a,n));

	if ((apow(a,n) - jacobi(a,n)) % n != 0) {
		hit++;
		return true;
	}
	
	return false;
}

int testPierwszosci(int n)
{
	for (int i = 1; i < 100; i++) {
		if (SolovayStrassen(n, i)) return false;
	}
	
	return true;
}














void sitoErastotenesa()
{
	pwsza[0] = false;
	pwsza[1] = true;
	for (int i = 2; i <= MAXpierw; i++) {
		pwsza[i] = true;
	}
	for (int i = 2; i <= MAXpierw; i++) {
		if (pwsza[i]) {
			for (int j = 2*i; j <= MAXpierw; j = j + i) {
				pwsza[j] = false;
			}
		}
	}
	for (int i = 2; i <= MAXpierw; i++) {
		if (pwsza[i]) { 
			pierwsze[lp++] = i; 
		}
	}

}

int pierwsza(int n)
{
	int tp = true;
	
	if (n > 1000000) {
		if (!testPierwszosci(n)) { return false; }
	}
	
	int i = 0;
	while (i < lp && pierwsze[i] * pierwsze[i] <= n) {
		if ((n % pierwsze[i]) == 0) return false; 
		i++;
	}

	lpierw++;
	
	return true;
}

int shift(int n)
{
  int c = 1, m = n;
  while (m > 9) {
    c = 10*c; m = m / 10;
  }
  return (n/10) + c*(n%10);
}

int nastepna(int n)
{  
  int c[20], nc = 0, m = n;
  while (m > 0)
  {
    c[nc++] = m % 10;
    m = m / 10;
  }
  c[nc] = 0; m = 0;
  while (c[m] == 9) {
    c[m] = 1; m++;
  }
  switch (c[m]) {
    case 0: c[m] = 1; break;
    case 1: c[m] = 3; break;
    case 3: c[m] = 7; break;
    case 7: c[m] = 9; break;
  }
  m = 1; n = 0;
  for (int i = 0; i <= nc; i++) {
    c[i] = c[i] * m; m = m * 10; n += c[i];
  }
  return n;
}

int main()
{
	sitoErastotenesa();

  int n = 1;
  int x = 0;
  
  while (n <= 1000000000) {
    int m = n; int kolowa = true;
    do {
      kolowa = kolowa && pierwsza(m);
      if (!kolowa) break;
      m = shift(m);
    } while (m != n);

	if (kolowa) {
      printf("%d kolowa? %s\n", m, kolowa ? "TAK" : "NIE");
	}
    n = nastepna(n); x++;
  }
  
  printf("hits %d lpierw %d x %d\n", hit, lpierw, x);
}
