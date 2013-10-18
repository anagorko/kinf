#include<iostream>
using namespace std;
 void wypisz (int n , string s)
{
    for ( int i=0; i < n; i++) {
        cout<< s;
    }
}
 void x1 ()
{
cout << "                ||"<< endl;
}

 void x2 ()
{
cout << "             __/||\\__"<< endl;
}

void x3 ()
{
cout << "          __/:::||:::\\__"<< endl;
}

void x4 ()
{
cout << "       __/::::::||::::::\\__"<< endl;
}

void x5 ()
{
cout << "    __/:::::::::||::::::::::\\__"<< endl;
}

void x6 ()
{
cout << "    |\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|" << endl;
}

void x7 ()
{
cout << "    \\_/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\_/"<< endl;
}

void x8 ()

{
cout << "      \\_/\\/\\/\\/\\/\\/\\/\\/\\/\\_/"<< endl;
}

void x10 ()
{
cout << "          \\_/\\/\\/\\/\\/\\_/"<< endl;
}

void x9 ()
{
cout << "        \\_/\\/\\/\\/\\/\\/\\/\\_/" << endl;
}

void x11 ()
{
cout << "            |% %||% %|"<< endl;
}


int main ()
{
wypisz ( 5, "                ||\n");
x2();
x3();
x4();
x5();
x6();
x7();
x8();
x9();
x10();
wypisz ( 5 ,"                ||\n");
wypisz (16 ,"            |% %||% %|\n");
x2();
x3();
x4();
x5();
x6();

return 0 ;
}
