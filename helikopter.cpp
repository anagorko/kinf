#include <iostream>
using namespace std;

int main ()

{
int n;
cin>>n;
for (int i=0;  i<=n; i++)

{
if (i==n/2) 

for (int j=0; j<n; j++){
cout<< "H";
}
else 
{
cout<< "H";
for (int j=0; j<n-2; j++){
cout<< " ";
}
cout<< "H";
}
cout<<"\n";
}
}


