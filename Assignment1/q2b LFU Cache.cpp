#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;
class Node
{
    public:
    int key;
    int data;
    int freq;
    Node *next;
    Node *prev;
    Node(int key,int data)
    {
        this->key=key;
        this->data=data;
        this->next=NULL;
        this->prev=NULL;
        this->freq=1;
    }
    void update_frequency(int f)
    {
        this->freq=f;
    }
};
class DoublyLinkedList
{
    public:
    Node *head;
    Node *tail;
    DoublyLinkedList()
    {
        this->head=NULL;
        this->tail=NULL;
    }
    Node* insert_node(int key,int data)
    {
        Node *n=new Node(key,data);
        if(!head)
        {
            head=n;
        }
        else
        {
            tail->next=n;
            n->prev=tail;
        }
        tail=n;
        return n;
    }
    void delete_first_node()
    {
        if(!head)
            return;
        Node *temp=head->next;
        if(temp)
        {
            temp->prev=NULL;
        }
        temp=head;
        head=head->next;
        free(temp);
    }
    void move_to_last(Node *n)
    {
        if(!head)
        {
            head=n;
        }
        else
        {
            tail->next=n;
            n->prev=tail;
        }
        tail=n;
    }
    void purgenode(Node *n)
    {
        if(n==head)
            head=head->next;
        if(n==tail)
            tail=tail->prev;
        if(n->next)
            n->next->prev=n->prev;
        if(n->prev)
            n->prev->next=n->next;
        n->next=NULL;
        n->prev=NULL;
    }
    int isempty()
    {
        if(head)
            return 0;
        else
            return 1;
    }
    void print_doublyLinkedList()
    {
        Node *temp=head;
        while (temp)
        {
            cout<<temp->key<<" "<<temp->data<<" "<<temp->freq<<endl;
            temp=temp->next;
        }
        
    }
};
class LFUCache
{
public:
int capacity;
map<int,DoublyLinkedList*> freqmap;
unordered_map<int,Node*> m;
LFUCache(int n)
{
    capacity=n;
}
void set(int key,int value)
{
    if(capacity==0)
        return;
    auto itr=m.find(key);
    if(itr==m.end())
    {
        if(m.size()==capacity)
        {
            auto del=freqmap.begin();
            DoublyLinkedList *d=del->second;
            m.erase(d->head->key);
            d->delete_first_node();
            if(d->isempty())
                freqmap.erase(del->first);
        }
        auto x=freqmap.find(1);
        if(x==freqmap.end())
        {
            freqmap.insert(pair<int,DoublyLinkedList *>(1,new DoublyLinkedList()));
        }
        Node *n=freqmap[1]->insert_node(key,value);
        m.insert(pair<int, Node *>(key,n));
    }
    else
    {
        m[key]->data=value;
        get(key);
    }
}
int get(int key)
{
    if(capacity==0)
        return -1;
    auto itr=m.find(key);
    if(itr==m.end())
        return -1;
    Node *n=itr->second;
    int value=n->data;
    int freq=n->freq;
    DoublyLinkedList *d=freqmap[freq];
    d->purgenode(n);
    if(d->isempty())
        freqmap.erase(freq);
    freq++;
    n->update_frequency(freq);
    auto x=freqmap.find(freq);
    if(x==freqmap.end())
    {
        freqmap.insert(pair<int,DoublyLinkedList *>(freq,new DoublyLinkedList()));
    }
    freqmap[freq]->move_to_last(n);
    return value;
}
void print()
{
    // for(auto itr=freqmap.begin();itr!=freqmap.end();itr++)
    // {
    // cout<<"++++++++"<<endl<<"frequency "<<itr->first<<endl;
    // itr->second->print_doublyLinkedList();
    // }
    // cout<<"$$$$$$$$$$$$$$$$$$$$"<<endl;
    for(auto itr=m.begin();itr!=m.end();itr++)
    {
        cout<<itr->first<<" "<<itr->second->data<<endl;
    }
}
};
int main()
{
    int s;
    cin>>s;
    LFUCache c(s);
    // c.set(1,100);
    // c.set(2,200);
    // c.set(3,300);
    // c.set(4,400);
    // c.set(5,500);
    // cout<<c.get(2)<<endl;
    // cout<<c.get(3)<<endl;
    // cout<<c.get(4)<<endl;
    // cout<<c.get(5)<<endl;
    // cout<<c.get(1)<<endl;
    // c.set(6,600);

    c.set(1,1);
    c.set(2,2);

    cout<<c.get(1)<<endl;

    c.set(3,3);

    cout<<c.get(2)<<endl;
    cout<<c.get(3)<<endl;
    c.set(4,4);
    cout<<c.get(1)<<endl;
    cout<<c.get(3)<<endl;
    cout<<c.get(4)<<endl;
    cout<<"------------------"<<endl;
    c.print();

}