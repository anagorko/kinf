#include <iostream>
#include <string>

using namespace std;
main()
{
char cQuiz;
int Quiz;
int o,i,u;
char co,ci,cu;
int f,g,h;
char cf,cg,ch;
int r,e,w;
char cr,ce,cw;
int repeat;
string z,x,c;
string v,b,n;
string a,s,d;
char pytanie,ankieta;
bool powtorz,odp1,odp2,odp3,pow;
powtorz=true;
repeat=0;
odp1=false;
odp2=false;
odp3=false;
pow=false;
o=0; i=0; u=0; 
co=' '; ci=' '; cu=' ';
f=0; g=0; h=0;
cf=' '; cg=' '; ch=' ';
r=0; e=0; w=0;
cr=' '; ce=' '; cw=' ';
z=' '; x=' '; c=' ';
v=' '; b=' '; n=' ';
a=' '; s=' '; d=' ';
pytanie=' ';
ankieta=' '; 
 //do
//{
 do
{
   cout<<"Quizy: \n"; 
   cout<<"1-Władca Pierścieni 'Drużyna pierścienia'\n";
   cout<<"2-Władca Pierścieni 'Dwie wieże'\n";
   cout<<"3-Władca Pierścieni 'Powrót króla'\n";
   cout<<"4-Zakończ program.\n\n";
   cout<<"Wybierz numer: ";
   cin>>cQuiz;
   Quiz=cQuiz;
   //cout<<cQuiz<<" "<<Quiz;
   //repeat=Quiz;
   switch (Quiz)
  {
    case 49 :
      cout<<"\n\nDrużyna Pierścienia\n\n";
      cout<<"Po co Gandalf przyjechał na urodziny Bilba?\n\n" ;
   cout<<"1. Przyjechał z fajerwerkami na prośbę Bilba;\n";
   cout<<"2. Aby złożyć mu życzenia;\n";
   cout<<"3. Aby odwiedzić Bilba.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>co;
   o=co;
   if(o==49)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      z="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Przyjechał z fajerwerkami na prośbę Bilba.\n\n";
      z="źle";
     }
   
   cout<<"Ile lat miał skończyć Bilbo?\n\n" ;
   cout<<"1. 100 lat;\n";
   cout<<"2. 111 lat;\n";
   cout<<"3. 99 lat.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>ci;
   i=ci;
   if(i==50)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      x="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: 111 lat.\n\n";
      x="źle";
     }

  cout<<"W jaki sposób Bilbo znikł podczas przemówienia?\n\n" ;
   cout<<"1. Gandalf go zaczarował;\n";
   cout<<"2. Włożył na palec Pierścień;\n";
   cout<<"3. Znikł w sposób jakiego się nauczył podczas podróży z Krasnoludami.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>cu;
   u=cu;
   if(u==50)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      c="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Włożył na palec Pierścień.\n\n";
      c="źle";
     }

   cout<<"Na pierwsze pytanie odpowiedziałeś "<<z<<", na drugie "<<x<<", a na trzecie "<<c<<".\n\n";
   odp1=true;
    break ;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 50 :
       cout<<"\n\nDwie Wieże\n\n";
       cout<<"W Rohanie miała miejsce bitwa pod ...?\n\n" ;
   cout<<"1. Minas Tirith;\n";
   cout<<"2. Edoras;\n";
   cout<<"3. Helmowym Jarem.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>cf;
   f=cf;
   if(f==51)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      v="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Helmowym Jarem.\n\n";
      v="źle";
     }
   
   cout<<"Kto był szpiegiem Sarumana na dworze króla Theodena?\n\n" ;
   cout<<"1. Gadzi/Smoczy Język;\n";
   cout<<"2. Czarny Język;\n";
   cout<<"3. Płazi Język.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>cg;
   g=cg;
   if(g==49)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      b="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Gadzi/Smoczy Język.\n\n";
      b="źle";
     }

  cout<<"Gdzie była i jak się nazywała wieża Sarumana?\n\n" ;
   cout<<"1. Nazywała się Orodruina i była w Shire;\n";
   cout<<"2. Nazywała się Orthank i była w Isengardzie;\n";
   cout<<"3. Nazywała się Barad-dur i była w Mordorze.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>ch;
   h=ch;
   if(h==50)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      n="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Nazywała się Orthank i była w Isengardzie.\n\n";
      n="źle";
     }

      cout<<"Na pierwsze pytanie odpowiedziałeś "<<v<<", na drugie "<<b<<", a na trzecie "<<n<<".\n\n";
   odp2=true;
    break ;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 51 :
         cout<<"\n\nPowrót Króla\n\n";
         cout<<"Kto był tym 'powracającym królem'?\n\n" ;
   cout<<"1. Aragorn;\n";
   cout<<"2. Frodo;\n";
   cout<<"3. Faramir.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>cr;
   r=cr;
   if(r==49)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      a="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Aragorn.\n\n";
      a="źle";
     }
   
   cout<<"Kogo Aragorn zmusił do wypełnienia przysięgi?\n\n" ;
   cout<<"1. Umarłych;\n";
   cout<<"2. Dzikich ludzi z Dunlandu;\n";
   cout<<"3. Easterlingów.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>ce;
   e=ce;
   if(e==49)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      s="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Umarłych.\n\n";
      s="źle";
     }

  cout<<"Kto uratował Froda i Sama przed spaleniem się w lawie?\n\n" ;
   cout<<"1. Sam Sauron, który się nawrócił;\n";
   cout<<"2. Nikt, zginęli i przenieśli się do Iluvatara;\n";
   cout<<"3. Gandalf na orłach.\n\n";
   cout<<"Wpisz tu odpowiedź: ";
   cin>>cw;
   w=cw;
   if(w==51)
     {
      cout<<"\nDobra odpowiedź!\n\n"; 
      d="dobrze";
     }
   else
     {
      cout<<"\nŹle! Dobra odpowiedż to: Gandalf na orłach.\n\n";
      d="źle";
     }

      cout<<"Na pierwsze pytanie odpowiedziałeś "<<a<<", na drugie "<<s<<", a na trzecie "<<d<<".\n\n";
   odp3=true;
  break ;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  case 52 :
    //repeat=52;
	return 0;
  break;


  default :
    cout<<"Nie ma takiego numeru.\n\n";
  break;
 
 
  }
  if (Quiz<49 |Quiz>52)
     {
       
     }
  else if(repeat==52){}
  {
  
  do//do2
  {
   cout<<"Czy chcesz powtórzyć Quiz? Wpisz T, jeśli chcesz, a N, jesli nie chcesz.\n";
   cin>>pytanie;
   cout<<"\n";
   if(pytanie=='T' || pytanie=='t')
     {
      powtorz=true;
      pow=false;
     } 
   if(pytanie=='N' || pytanie=='n')
     {
      powtorz=false;
      pow=false;
     }
   if(pytanie!='T' && pytanie!='N' && pytanie!='t' && pytanie!='n')
     {
      cout<<"Wpisz jeszcze raz.\n";
      pow=true;
     }
   }while(pow==true);//do2
  }
 }while(Quiz==49 | Quiz==50 | Quiz==51 | Quiz!=52 && powtorz==true);
 if(repeat==52)
{cout<<"\n";}
else
{ 
  cout<<"\n===========================================================";
                                       //Twoje wszystkie odpowiedzi: 
  cout<<"\n|Nr |Quizy:               |Twoje odpowiedzi:              |\n===========================================================\n|1. |Drużyna Pierścienia: ";

  if(odp1==true)
  {
    cout<<"|"<<z<<","<<x<<","<<c<<"           |";
  }
  else
  {
    cout<<"|nie brałeś udziału w tym quizie|";
  }//if 1
  
  cout<<"\n===========================================================\n|2. |Dwie wieże: ";

  if(odp2==true)
  {
    cout<<"         |"<<v<<","<<b<<","<<n<<"           |";
  }
  else
  {
    cout<<"         |nie brałeś udziału w tym quizie|";
  }//if 2

  cout<<"\n===========================================================\n|3. |Powrót króla: ";

  if(odp3==true)
  {
    cout<<"       |"<<a<<","<<s<<","<<d<<"           |\n===========================================================";
  }
  else
  {                                                 
    cout<<"       |nie brałeś udziału w tym quizie|\n===========================================================";
  }//if 3
  cout<<"\n\nCzy podobał ci się quiz? \n";
  cout<<"Twoja odpowiedż: ";
  cin>>ankieta;
  cout<<"Dziękuję za twoją ocenę!\n\n";
}
}

 
