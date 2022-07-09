#include <iostream>
using namespace std;
class TrieNode
{
    public:
    // bool alpha[26]={0};
    TrieNode* child_nodes[26]={NULL};
    bool ended;
    char element;
    TrieNode(char elem)
    {
        element=elem;
        ended=false;
    }
};
class Node
{
    public:
    string data;
    Node *next;
    Node *prev;
    Node(string d)
    {
        data=d;
        next=NULL;
        prev=NULL;
    }
    int operator<(Node *n)
    {
        // cout<<data<<" < "<<n->data<<endl;
        if(data<n->data)
            return 1;
        return 0;
    }
};
class LinkedList
{
    public:

    Node *head;
    Node *tail;
    LinkedList()
    {
        this->head=NULL;
        this->tail=NULL;
    }
    void insert(string s)
    {
        if(!this->head)
        {
            Node *n=new Node(s);
            this->head=n;
            this->tail=n;
        }
        else
        {
            Node *n=new Node(s);
            Node *temp=tail;
            while (temp!=NULL && *n<temp)
            {
                temp=temp->prev;
            }
            n->prev=temp;
            if(temp!=NULL)
            {
                // if(s==temp->data)
                // return;
                n->next=temp->next;
                temp->next=n;
                if(temp->next)
                    temp->next->prev=n;
                if(temp==tail)
                    tail=n;
            }
            else
            {
                n->next=head;
                head->prev=n;
                head=n;
            }
            
        }
    }
};
class Trie
{
    public:
    TrieNode *root=NULL;
    void insert(string s)
    {
        
        if(s.size()==0)
            return;
        if(!root)
            root=new TrieNode('r');
        TrieNode *temp=root;
        for(int i=0;i<s.size();i++)
        {
            // cout<<"given "<<s[i]<<endl;
            auto &children=temp->child_nodes;
            int idx=s[i]-'a';
            if(children[idx]==NULL)
            {
                children[idx]=new TrieNode(s[i]);
                // cout<<s[i]<<" inseted"<<endl;
            }
            temp=children[idx];
        }
        temp->ended=true;
    }
    void constructTrie(int x,string *word_list)
    {
        for(int i=0;i<x;i++)
        {
            insert(word_list[i]);
        }
    }
    void findwords(int r,int c,auto g)
    {
        LinkedList res;
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                if(root->child_nodes[g[i][j]-'a'])
                {
                    traverse(g,i,j,r,c,string(1,g[i][j]),root->child_nodes[g[i][j]-'a'],res);
                }
            }
        }
        cout<<"&&&&&&&&&&&&&&&&&&"<<endl;
        for(Node *temp=res.head;temp!=NULL;temp=temp->next)
        {
            cout<<temp->data<<endl;
        }
    }
    void traverse(auto g,int i,int j,int &r,int &c,string s,TrieNode* t,LinkedList &res)
    {
        auto &children=t->child_nodes;
        if(g[i][j]=='$')
            return;
        if(t->ended)
        {
            // cout<<s<<endl;
            res.insert(s);
        }
        char ch=g[i][j];
        g[i][j]='$';
        if(i+1<r && g[i+1][j]!='$' && children[g[i+1][j]-'a'])
            traverse(g,i+1,j,r,c,s+g[i+1][j],children[g[i+1][j]-'a'],res);
        if(i-1>=0 && g[i-1][j]!='$' && children[g[i-1][j]-'a'])
            traverse(g,i-1,j,r,c,s+g[i-1][j],children[g[i-1][j]-'a'],res);
        if(j+1<c && g[i][j+1]!='$' && children[g[i][j+1]-'a'])
            traverse(g,i,j+1,r,c,s+g[i][j+1],children[g[i][j+1]-'a'],res);
        if(j-1>=0 && g[i][j-1]!='$' && children[g[i][j-1]-'a'])
            traverse(g,i,j-1,r,c,s+g[i][j-1],children[g[i][j-1]-'a'],res);
        g[i][j]=ch;
    }
};
int main()
{
    char grid[10][10];
    string word_list[10];
    int r,c,x;
    cin>>r>>c;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>grid[i][j];
        }
    }
    // cout<<"Enter the words"<<endl;
    cin>>x;
    for(int i=0;i<x;i++)
    {
        cin>>word_list[i];
    }
    Trie t;
    t.constructTrie(x,word_list);
    // cout<<"####################"<<endl;
    t.findwords(r,c,grid);
    // auto chi=t.root->child_nodes;
    // for(int i=0;i<26;i++)
    // {
    //     if(chi[i])
    //     {
    //         cout<<chi[i]->element<<endl;
    //     }
    // }
}