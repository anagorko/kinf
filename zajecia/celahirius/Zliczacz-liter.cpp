#include <iostream>
#include <string>

using namespace std;

int main()
{
    char a[26];
    int b[26];
    char txt[200];
    int r=sizeof(txt);
    int l;

    cin>>l;

    //for(int k=0; k<l; k++)
    //{
        cin>>txt[200];

        for(int i=0; i<txt[r]; i++)
        {
            for(int j=0; j<26; j++)
            {
                if(txt[i]=a[j])
                {
                    a[j]=txt[i];
                    b[j]++;
                }
                else
                {
                    j=j+1;
                    a[j]=txt[i];
                    b[j]++;
                }
            }
        }
    //}

    for(int i=0; i<26; i++)
    {
        cout<<a[i]<<" "<<b[i]<<"\n";
    }


    return 0;
}
