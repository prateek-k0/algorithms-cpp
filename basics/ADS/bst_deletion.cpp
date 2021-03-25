#include<iostream>
using namespace std;

typedef struct btree
{
    int data;
    struct btree *left,*right;
}*bt ;

bt root;

bt getnode()
{
    bt node=new btree;
    node->left=NULL;
    node->right=NULL;
    return node;
}
int search_node(bt root,int d)
{
    if(root==NULL)
        return 0;
    else if(root->data==d)
        return 1;
    else if(root->data<=d)
        search_node(root->right,d);
    else search_node(root->left,d);
}
void create()
{
    bt temp;
    char res;
    root = getnode();
    cout<<"Enter value of root: ";
    cin>>root->data;

    do
    {
        bt new1 = getnode();
        temp = root;
        cout<<"\nEnter next node: ";
        cin>>new1->data;

        while(true)
        {
            if(new1->data<temp->data)
            {
                if(temp->left==NULL)
                {
                    temp->left=new1;
                    break;
                }

                else temp=temp->left;
            }
            else
            {
                if(temp->right==NULL)
                {
                    temp->right=new1;
                    break;
                }

                else temp=temp->right;
            }

        }
        cout<<"\nWant to enter more?(y/n)";
        cin>>res;

    }while(res!='n');

}

bt find_successor(bt root)
{
    while(root->left!=NULL)
        root=root->left;
    return root;
}

bt delete_node(bt root,int v)
{
    if(search_node(root,v))
    {
        if(root==NULL)
            return root;
        else if(v<root->data)
            root->left=delete_node(root->left,v);
        else if(v>root->data)
            root->right=delete_node(root->right,v);

        else
        {
            if(root->left==NULL && root->right==NULL)
            {
                delete root;
                return NULL;
            }
            else if(root->left==NULL && root->right!=NULL)
            {
                bt temp=root;
                root=root->right;
                delete temp;
                return root;
            }
            else if(root->right==NULL && root->left!=NULL)
            {
                bt temp=root;
                root=root->left;
                delete temp;
                return root;

            }
            else
            {
                bt temp=find_successor(root->right);
                root->data=temp->data;
                root->right=delete_node(root->right,temp->data);
            }
        }
        return root;
    }

    else cout<<"No such node";
    return NULL;
}

void inorder(bt node)
{
    if(node==NULL)
        return;

    inorder(node->left);
    cout<<node->data;
    inorder(node->right);
}

int main()
{
    int opt;
    char s;
    int d;
   do{ cout<<"1. Creation\n2. Display\n3. Delete";
    cin>>opt;


    switch(opt)
    {
        case 1:create();
                break;

        case 2:cout<<endl<<endl;
                inorder(root);
                break;
        case 3:cout<<"Enter data to be deleted: ";
        cin>>d;
        root = delete_node(root,d);
        break;
        default:break;

    }
    cout<<"\nWant to continue?";
    cin>>s;
    }while(s!='n');
}



