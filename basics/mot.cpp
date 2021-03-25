#include<iostream>
#include<strings.h>
#include<fstream>
using namespace std;

struct table
{
    char oc[80],bc[80],type[80];
}tab[50];
struct input
{
    char lable[80],inst[80],op1[80],op2[80];
}obj[50];

int main()
{
    fstream fp1,fp2;
    int i=0,j=0,x=0;
    fp1.open("tab2.txt",ios::in);
    fp2.open("john.txt",ios::in);
    while(!fp1.eof())
    {
        fp1>>tab[i].oc>>tab[i].bc>>tab[i].type;
        i++;
    }
    cout<<"Machine op table: \n";
    cout<<"Mnemo\tOpcode\tLen\tFormat\n";

   while(!fp2.eof())
   {
       fp2>>obj[j].lable>>obj[j].inst>>obj[j].op1>>obj[j].op2;

       for(x=0;x<i;x++)
       {
           if(!strcmp(obj[j].inst,tab[x].oc))
           {
               if(strlen(obj[j].inst)<4)
                   {for(int z=strlen(obj[j].inst);z<4;z++)
                        strcat(obj[j].inst,"b");
                   }
               if(!strcmp(tab[x].type,"RR"))
               {
                   cout<<obj[j].inst<<"\t"<<tab[x].bc<<"\t"<<"01\t"<<"000\n";
               }
               if(!strcmp(tab[x].type,"RX"))
               {
                   cout<<obj[j].inst<<"\t"<<tab[x].bc<<"\t"<<"10\t"<<"001\n";
               }
               if(!strcmp(tab[x].type,"RS"))
               {
                   cout<<obj[j].inst<<"\t"<<tab[x].bc<<"\t"<<"10\t"<<"010\n";
               }
               if(!strcmp(tab[x].type,"SI"))
               {
                   cout<<obj[j].inst<<"\t"<<tab[x].bc<<"\t"<<"10\t"<<"011\n";
               }
               if(!strcmp(tab[x].type,"SS"))
               {
                   cout<<obj[j].inst<<"\t"<<tab[x].bc<<"\t"<<"11\t"<<"100\n";
               }
           }
       }
        j++;
   }
    return 0;
}
