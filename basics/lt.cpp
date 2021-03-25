#include<iostream>
#include<ctype.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<vector>
using namespace std;

struct input
{
    char lable[80],inst[80],op1[80],med[80],op2[80];
}obj[100];

struct table
{
    char inst[80];
    int s,len;
}tab[100];

int d_resolve(int s)
{
    int a,i=0,c=0;
    char str[80];
    if(!strcmp(obj[s].inst,"DS"))
    {   while(obj[s].op1[i]!='\0')
        {
            if(isalpha(obj[s].op1[0]))
            {
                str[0]='1';
                break;
            }
            if(!isalpha(obj[s].op1[i]))
                    str[i]=obj[s].op1[i];
            else break;
            i++;
        }
        a=atoi(str);
        if(obj[s].op1[i]=='F')
            return a*4;
        else if(obj[s].op1[i]=='D')
            return a*8;
        else return a*2;
    }

    if(!strcmp(obj[s].inst,"DC"))
    {
         while(obj[s].op1[i]!='\0')
         {
             if(obj[s].op1[i]==',')
                c++;

             i++;
         }
         a=c+1;
         if(obj[s].op1[0]=='F')
            return a*4;
         else if(obj[s].op1[0]=='D')
            return a*8;
         else return a*2;
    }
}

int islit(int i)
{
    if(obj[i].op2[0]=='=')
        return 1;
    return 0;
}

void p_ltorg(int& lc,vector<int> x)
{
    if(lc%8!=0)
        lc=lc-lc%8+8;
    char str[80];
    int u;
    vector<int>::iterator i;
    for(i=x.begin();i!=x.end();i++)
    {   u=0;
        strcpy(str,obj[*i].op2);
        while(str[u]!='\0')
        {
            str[u]=str[u+1];
            u++;
        }
        cout<<str<<"     \t"<<lc<<"\t4\tR";
        for(int j=0;j<24;j++)
            {
                if(!strcmp(obj[*i].inst,tab[j].inst))
                {
                    lc+=tab[j].s;
                    break;
                }
            }
        cout<<endl;
    }
}

int main()
{
    int i=0,j=0,a=0,b=0,lc=0;
    vector<int> v;
    fstream fp;
    fp.open("table.txt",ios::in);
    while(!fp.eof())
    {   fp>>tab[i].inst>>tab[i].s>>tab[i].len;
    i++;
    }
    fp.close();
    b=i;
    i=0;
    cout<<"Literal Table: \n";
    cout<<"Symbol\t\tValue\tLength\tRelocation\n------------------------------------------\n";
    fp.open("69.txt",ios::in);
    while(!fp.eof())
    {
         fp>>obj[i].lable>>obj[i].inst>>obj[i].op1>>obj[i].med>>obj[i].op2;
         if(!strcmp(obj[i].inst,"DS") || !strcmp(obj[i].inst,"DC"))
               a=d_resolve(i);

         else if(!strcmp(obj[i].inst,"LTORG"))
                 {
                    p_ltorg(lc,v);
                    continue;
                 }
         else
          {   if(islit(i))
                v.push_back(i);

              for(j=0;j<b-1;j++)
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


