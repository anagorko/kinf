#include <iostream>
using namespace std;
main()
{

    int tmp;
int rok,dzien,miesiac;
    if (miesiac < 3)
         tmp = 365*rok + dzien+31*(miesiac-1) + (int)((rok-1)/4)-(int)(3*(int)((rok-1)/100+1)/4);
    else
         tmp = 365*rok+dzien+31*(miesiac-1)-(int)(0.4*miesiac+2.3)+(int)(rok/4)-(int)(3*(int)(rok/100+1)/4);
         tmp = tmp-7*(int)(tmp/7)-1;
         tmp++;
   
    cout << endl << "Jest to : ";
    switch (tmp)
      {
      case 0: cout << "sobota" << endl;break;
        case 1: cout << "niedziela" << endl;break;
        case 2: cout << "poniedzialek" << endl;break;
        case 3: cout << "wtorek" << endl;break;
        case 4: cout << "sroda" << endl;break;
        case 5: cout << "czwartek" << endl;break;
        case 6: cout << "piatek" << endl;break;
      }

}
 
