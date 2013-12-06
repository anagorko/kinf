#include <iostream>

using namespace std;

int main()
{
    int n,l=1;
    int p1,p2=0,p3=0,p4;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>p1;
        if(p1>p2)
        {
            p2=p1;
        }
        else
        {
            if(p1>p3)
            {
                p3=p1;
            }
            else
            {
                l++;
                p3=p1;
                if(p1==p2 && p3==p2)
                {
                    p4=p1;
                    l++;
                }
            }
        }
    }
    cout <<l<< endl;
    return 0;
}
