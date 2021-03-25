#include<iostream>
#include<string.h>
using namespace std;

const int alpha=26;
inline int c_index(char s){return (int)s - (int)'a';}

struct tnode
{
    struct tnode* child[alpha];
    bool eow;
};

typedef struct tnode* tn;

tn getnode()
{
    tn node = new tnode;
    node->eow=false;
    for(int i=0;i<alpha;i++)
        node->child[i]=NULL;
    return node;
}

void ins(tn root,char * key)
{
    tn p=new tnode;
    p=root;
    int index;
    for(int i=0;i<strlen(key);i++)
    {
        index = c_index(key[i]);
        if(!p->child[index])
            p->child[index]=getnode();
        p=p->child[index];

    }
    p->eow=true;
}

int search_t(tn root,char *key)
{   int index;
    tn p=new tnode;
    p=root;
    for(int i=0;i<strlen(key);i++)
    {
        index=c_index(key[i]);
        if(p->child[index]==NULL)
            return 0;
        p=p->child[index];
    }
    return(p!=NULL && p->eow);
}

int main()
{   char keys[][20]={"the","a","there","is","a","cat"};
    tn root=getnode();
   for(int i=0;i<6;i++)
        ins(root,keys[i]);


   search_t(root,"there")?cout<<"yes":cout<<"no";
   cout<<endl;
   search_t(root,"dog")?cout<<"yes":cout<<"no";

    return 0;
}
