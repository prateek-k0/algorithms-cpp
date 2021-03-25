#include<iostream>
#include<fstream>
#include<ctype.h>
#include<string.h>
#include<vector>
#include<stdlib.h>
using namespace std;

struct table
{
    char inst[80];
    int s,len;
}tab[100];

struct input
{
    char lable[80],inst[80],op1[80],med[80],op2[80];

}obj[100];

int islit(int i)
{
    if(obj[i].op2[0]=='=')
        return 1;
    return 0;
}

void p_ltorg(int& lc,vector<int> x)
{
    if(lc%8!=0)
        lc = lc+8 -(lc%8);

    char str[80];
    int u;
    vector<int>::iterator i;
    for(i=x.begin();i!=x.end();i++)
    {
        u=0;
        strcpy(str,obj[*i].op2);
        while(str[u]!='\0')
        {
            str[u]=str[u+1];
            u++;
        }

        cout<<str<<"     \t"<<lc<<"\t4\tR\n";
        for(int j=0;j<24;j++)
        {
            if(!strcmp(obj[*i].inst,tab[j].inst))
            {
                lc+=tab[j].s;
                break;
            }
        }
    }
    return;

}

int d_resolve(int i)
{
    int a=0,u=0,c=0;
    char str[80];
    if(!strcmp(obj[i].inst,"DS"))
    {
        while(obj[i].op1[u]!='\0')
        {
            if(isalpha(obj[i].op1[0]))
            {
                str[0]=1;
                break;
            }
            if(!isalpha(obj[i].op1[u]))
            {
                str[u]=obj[i].op1[u];
            }
            else break;
            u++;
        }

        a=atoi(str);
        if(obj[i].op1[u]=='F')
            return a*4;
        else if(obj[i].op1[u]=='D')
            return a*8;
        else return a*2;
    }

    else
    {
        while(obj[i].op1[u]!='\0')
        {
            if(obj[i].op1[u]==',')
                c++;
            u++;
        }
        a=c+1;
         if(obj[i].op1[0]=='F')
            return a*4;
        else if(obj[i].op1[0]=='D')
            return a*8;
        else return a*2;
    }
    return 0;
}

int main()
{
    fstream fp;
    int i=0,j=0,a=0,b=0,lc=0;
    fp.open("table.txt",ios::in);
    vector<int> v;
    while(!fp.eof())
    {
        fp>>tab[b].inst>>tab[b].s>>tab[b].len;
        b++;
    }
    fp.close();
    fp.open("69.txt",ios::in);
    while(!fp.eof())
    {
        fp>>obj[i].lable>>obj[i].inst>>obj[i].op1>>obj[i].med>>obj[i].op2;
        if(!strcmp(obj[i].inst,"DS") || !strcmp(obj[i].inst,"DS"))
            a=d_resolve(i);
        else if(!strcmp(obj[i].inst,"LTORG"))
        {
            p_ltorg(lc,v);
            continue;
        }

        else
        {
            if(islit(i))
                v.push_back(i);
            for(j=0;j<b;j++)
            {
                if(!strcmp(obj[i].inst,tab[j].inst))
                {
                    a=tab[j].s;
                    break;
                }
            }
        }
        lc+=a;
        i++;
    }

    fp.close();
    return 0;
}
