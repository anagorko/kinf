#include <iostream>
#include <string>

using namespace std;

int main()
{
    int z=0;
    int x;
    string txt;
    string txt2;

    cin>>x;

    for(int i=0; i<x; i++)
    {
        cin>>txt[i];
        cin>>txt2[i];
    }

    /*for(int i=0; i<x; i++)
    {
        cin>>txt2[i];
    }*/

    for(int i=0; i<x; i++)
    {

        if(txt[i]=!txt2[i])
        {
            z++;
        }
    }

    cout<<z;

    return 0;
}
