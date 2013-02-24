#include<iostream>
using namespace std;

typedef struct wymierna
{
	int l;
	int m;
};

wymierna iloczyn(wymierna p, wymierna q)
{
	wymierna r;

	r.l = p.l * q.l;
	r.m = p.m * q.m;

	return r;
}

wymierna suma(wymierna p, wymierna q)
{
	wymierna r;

	r.l = p.l * q.m + p.m * q.l;
	r.m = p.m * q.m;

	return r;
}

wymierna odwrotna(wymierna p)
{
	wymierna r;

	r.l = p.m;
	r.m = p.l;

	return r;
}

int main()
{
	wymierna p = { 1, 2 };
 	wymierna q = { 1, 3 };
     
  	wymierna a = suma(suma(p,q), iloczyn(p,q)); // obliczamy 1/2 + 1/3 + 1/2*1/3
  
  	cout << a.l << "/" << a.m << endl;

  	wymierna dwa = { 2, 1 };
  	
  	a = iloczyn(dwa, odwrotna(suma(odwrotna(p), odwrotna(q)))); // obliczamy średnią harmoniczną p i q
  
  	cout << a.l << "/" << a.m << endl;
         
  	return 0;
}
