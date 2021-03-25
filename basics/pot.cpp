#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

char po[7][10]={"START","USING","EQU","DS","DC","DROP","END"};
int spo(const char* str)
{
    for(int i=0;i<7;i++)
    if(!strcmp(po[i],str))
        return i;

    return -1;

}

void p_start() {}
void p_using(){}
void p_equ() {}
void p_ds(){}
void p_dc(){}
void p_drop(){}
void p_end() {}

void (*fptr[7]) (void) = {&p_start,&p_using,&p_equ,&p_ds,&p_dc,&p_drop,&p_end};
struct data
{
    char lable[80],inst[80],op1[80],med[80],op2[80];
}obj[100];

int main()
{
    fstream fp;
    fp.open("69.txt",ios::in);
    int i=0,j=0;
    cout<<"Pseudo-op\tAddress\n";
    cout<<"------------------------\n";
    while(!fp.eof())
    {
        fp>>obj[i].lable>>obj[i].inst>>obj[i].op1>>obj[i].med>>obj[i].op2;
        j=spo(obj[i].inst);
        if(j!=-1)
            cout<<obj[i].inst<<"\t\t"<<&fptr[j]<<endl;
        i++;
    } cout<<"------------------------\n";
    return 0;
}
