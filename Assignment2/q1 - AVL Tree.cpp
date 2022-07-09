#include <iostream>
using namespace std;
template <typename V>
class Node
{
    public:
    V value;
    Node* left;
    Node* right;
    int height;
    int frequency;
    int size;
    Node(V val)
    {
        value=val;
        height=1;
        left=NULL;
        right=NULL;
        frequency=1;
        size=1;
    }
};
template <typename V>
class comparator
{
    public:
    int operator()(V a,V b)
    {
        if(a<b)
            return -1;
        if(a==b)
            return 0;
        if(a>b)
            return 1;
    }  
};
template <typename V>
class AVL
{
    public:
    Node<V> *root=NULL;
    V noelem=V();
    // AVL()
    // {
    //     root=NULL;
    // }
    int getheight(Node<V>* n)
    {
        if(!n)
        return 0;
        return n->height;
    }
    int getsize(Node<V>* n)
    {
        if(!n)
        return 0;
        return n->size;
    }
    int getfrequency(Node<V>* n)
    {
        if(!n)
        return 0;
        return n->frequency;
    }
    int balancefactor(Node<V> *n)
    {
        int x=getheight(n->left) - getheight(n->right);
        return x;
    }
    int maximum(int a,int b)
    {
        if(a>b)
            return a;
        return b;
    }
    Node<V>* smallest(Node<V> *n)
    {
        Node<V> *temp=n;
        if(temp)
        {
            while(temp->left)
            {
                temp=temp->left;
            }
        }
        return temp;
    }
    Node<V>* largest(Node<V> *n)
    {
        Node<V> *temp=n;
        if(temp)
        {
            while(temp->right)
            {
                temp=temp->right;
            }
        }
        return temp;
    }
    V finddifference(V a,V b)
    {
        V diff=a-b;
        if(diff<0)
            diff=-diff;
        return diff;
    }
    Node<V>* leftrotate(Node<V> *n)
    {
        Node<V> *r=n->right;
        Node<V> *rl=r->left;
        n->right=rl;
        r->left=n;
        n->height=1+maximum(getheight(n->left),getheight(n->right));
        r->height=1+maximum(getheight(r->left),getheight(r->right));
        n->size=1 + getsize(n->left) + getsize(n->right);
        r->size=1 + getsize(r->left) + getsize(r->right);
        return r;
    }
    Node<V>* rightrotate(Node<V> *n)
    {
        Node<V> *l=n->left;
        Node<V> *lr=l->right;
        l->right=n;
        n->left=lr;
        n->height=1+maximum(getheight(n->left),getheight(n->right));
        l->height=1+maximum(getheight(l->left),getheight(l->right));
        n->size=n->frequency + getsize(n->left) + getsize(n->right);
        l->size=n->frequency + getsize(l->left) + getsize(l->right);
        return l;
    }
    void insert(V val,comparator<V> cmp)
    {
        root=insert_node(val,root,cmp);
    }
    void del(V val)
    {
        root=deleteelem(val,root);
    }
    Node<V>* deleteelem(V val,Node<V> *n)
    {
        if(!n)
            return n;
        if(val==n->value)
        {
            //If node has one child then the child is a leaf node(because of balancing a node cannot have
            //more than 1 depth single child) so delete the leaf
            Node<V> *temp=NULL;
            if(n->left && n->right)
            {
                temp=smallest(n->right);    //Inorder successor
                n->value=temp->value;
                n->right=deleteelem(temp->value,n->right);

            }
            else
            {
                if(n->left==NULL)
                    temp=n->right;
                else
                    temp=n->left;
                if(temp)
                {
                    n->value=temp->value;
                    n->left=temp->left;
                    n->right=temp->right;
                    n->frequency=temp->frequency;
                    n->height=temp->height;
                }
                else
                {
                    temp=n;
                    n=NULL;
                    return n;
                }
                free(temp);
            }
        }
        else if(val<n->value)
            n->left=deleteelem(val,n->left);
        else
            n->right=deleteelem(val,n->right);
        n->height=1+maximum(getheight(n->left),getheight(n->right));
        n->size=n->frequency + getsize(n->left) + getsize(n->right);
        int bf=balancefactor(n);
        if(bf>1)
        {
            int bfl=balancefactor(n->left); //bf of LST
            if(bfl>=0)  //Left-Left
            {
                return rightrotate(n);
            }
            else    //Left-Right
            {
                n->left=leftrotate(n->left);
                return rightrotate(n);
            }
        }
        else if(bf<-1)
        {
            int bfr=balancefactor(n->right);
            if(bfr<=0)  //  Right-Right
            {
                return leftrotate(n);
            }
            else    //Right-Left
            {
                n->right=rightrotate(n->right);
                return leftrotate(n);
            }
        }
        return n;
        
    }
    Node<V>* insert_node(V val,Node<V> *n,comparator<V> cmp)
    {
        if(!n)
        {
            Node<V> *new_node=new Node<V>(val);
            return new_node;
        }
        if(cmp(val,n->value)<0)
        n->left=insert_node(val,n->left,cmp);
        else if(cmp(val,n->value)>0)
        n->right=insert_node(val,n->right,cmp);
        else
        {
            n->frequency=n->frequency+1;
            return n;
        }
        n->height=1+maximum(getheight(n->left),getheight(n->right));
        n->size=n->frequency+getsize(n->left)+getsize(n->right);
        int bf=balancefactor(n);
        if(bf>1) //LST is bigger
        {
            if(cmp(val,((n->left)->value))<0) // Left-Left insertion
                return rightrotate(n);
            else if(cmp(val,((n->left)->value))>0)  // Left-Right insertion
            {
                n->left=leftrotate(n->left);
                return rightrotate(n);
            }
        }
        else if(bf<-1)  //RST is bigger
        {
            if(cmp(val,(n->right)->value)>0)   //  Right-Right insertion
                return leftrotate(n);
            else if(cmp(val,(n->right)->value)<0)  //  Right-Left insertion
            {
                n->right=rightrotate(n->right);
                return leftrotate(n);
            }
        }
        return n;
    }
    bool search(V val)
    {
        Node<V> *temp=root;
        while(temp)
        {
            if(val<temp->value)
            {
                temp=temp->left;
                continue;
            }
            if(val>temp->value)
            {
                temp=temp->right;
                continue;
            }
            return true;
        }
        return false;
    }
    int countelem(V val)
    {
        Node<V>* temp=root;
        while(temp)
        {
            if(val<temp->value)
                temp=temp->left;
            else if(val>temp->value)
                temp=temp->right;
            else
                return temp->frequency;
        }
        return 0;
    }
    Node<V>* lb(V val)
    {
        Node<V> *temp=root;
        Node<V> *result=NULL;
        while(temp)
        {
            if(val<temp->value)
            {
                result=temp;
                temp=temp->left;
            }
            else if(val>temp->value)
                temp=temp->right;
            else
                return temp;
        }
        return result;
    }
    Node<V>* ub(V val)
    {
        Node<V> *temp=root;
        Node<V> *result=NULL;
        while(temp)
        {
            // cout<<temp->value<<endl;
            if(val<temp->value)
            {
                result=temp;
                temp=temp->left;
            }
            else if(val>temp->value)
                temp=temp->right;
            else
            {
                Node<V> *t=smallest(temp->right);
                if(t)
                    result=t;
                break;
            }
        }
        return result;
    }
    V lower_bound(V val)
    {
        Node<V>* result=lb(val);
        if(result)
            return result->value;
        return noelem;
    }
    V upper_bound(V val)
    {
        Node<V>* result=ub(val);
        if(result)
            return result->value;
        return noelem;
    }
    V closest(V val)
    {
        Node<V> *temp=root;
        Node<V> *result=root;
        int diff=finddifference(val,root->value);
        while(temp)
        {
            if(val<temp->value)
                temp=temp->left;
            else if(val>temp->value)
                temp=temp->right;
            else
                return temp->value;
            if(temp)
            {
                int newdiff=finddifference(val,temp->value);
                if(newdiff<diff)
                {
                    result=temp;
                    diff=newdiff;
                }
            }
        }
        return result->value;
    }
    V findklargest(int k)
    {
        Node<V> *temp=root;
        if(k<1 || k>temp->size)
            return noelem;
        while(temp)
        {
            Node<V> *A=temp->left;
            Node<V> *B=temp->right;
            if(!B)
            {
                if(k<=temp->frequency)
                    return temp->value;
                else
                {
                    k=k-temp->frequency;
                    temp=A;
                }
            }
            else
            {
                if(k<=B->size)
                    temp=B;
                else if(k<=B->size+temp->frequency)
                    return temp->value;
                else
                {
                    k=k-B->size-temp->frequency;
                    temp=A;
                }
            }
        }
        return noelem;
    }
    int countrange(V a,V b)
    {
        Node<V> *A=lb(a);
        Node<V> *B=ub(b);
        int l=0,r=0;
        if(A)
        l=getsize(A->left);
        if(B)
        r=getsize(B->right);
        int result=getsize(root) - l - r - getfrequency(B);
        return result;
    }
    void preorder(Node<V> *n)
    {
        if(n)
        {
            cout<<n->value<<endl;
            preorder(n->left);
            preorder(n->right);
        }
    }
    void inorder(Node<V> *n)
    {
        if(n)
        {
            inorder(n->left);
            cout<<n->value<<" "<<n->frequency<<endl;;
            inorder(n->right);
        }
    }
};

int main()
{
    AVL<int> tree;
    comparator<int> cmp;
    tree.insert(9,cmp);
    tree.insert(5,cmp);
    tree.insert(10,cmp);
    tree.insert(-1,cmp);
    tree.insert(6,cmp);
    tree.insert(11,cmp);
    tree.insert(-3,cmp);
    tree.insert(1,cmp);
    tree.insert(2,cmp);
    tree.insert(11,cmp);

    // tree.preorder(tree.root);
    // tree.del("10.1");
    tree.inorder(tree.root);
    cout<<"++++++++++++++++++"<<endl;
    cout<<tree.closest(8)<<endl;
    cout<<tree.search(11)<<endl;
    cout<<tree.search(88)<<endl;
    cout<<tree.search(10)<<endl;
    cout<<tree.countelem(11)<<endl;
    cout<<tree.findklargest(10)<<endl;
    cout<<tree.lower_bound(9)<<endl;
    cout<<tree.countrange(-1,9)<<endl;
    cout<<tree.root->value<<endl;
}

//https://viewsourcecode.org/snaptoken/kilo/index.html