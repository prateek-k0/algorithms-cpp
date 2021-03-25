#include<vector>
#include<list>
#include<algorithm>
#include<iostream>
using namespace std;
int main()
{   int a,n,o;
    cout<<"Enter number of elements: ";
    cin>>n;
    cout<<"Order of skip list: ";
    cin>>o;
    vector<list<int> > v(o);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++)
    {
        cin>>a;
        v[0].push_back(a);
    }
   v[0].sort();
    list<int>::iterator i;
    int c=0;
    for(int j=0;j<o-1;j++)
    {
        for(i=v[j].begin(),c=0;i!=v[j].end();i++,c++)
        {       if(c%(o-1)==0)
                v[j+1].push_back(*i);
        }
    }
    cout<<"\n\nSkip list: \n\n";
        for(int j=o-1;j>=0;j--)
    {       cout<<"Level "<<j<<": \t";
            for(i=v[j].begin();i!=v[j].end();i++)
                cout<<*i<<" ";

        cout<<endl;
    }
    return 0;
}
