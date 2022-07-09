#include <iostream>
#include <unordered_map>
using namespace std;
class Node
{
    public:
    int key;
    int data;
    Node *next;
    Node *prev;
    Node(int key,int data)
    {
        this->key=key;
        this->data=data;
        this->next=NULL;
        this->prev=NULL;
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
        if(tail==n)
            return;
        if(head==n)
            head=head->next;
        Node *temp=n->prev;
        if(temp)
            temp->next=n->next;
        n->next->prev=temp;
        n->next=NULL;
        tail->next=n;
        n->prev=tail;
        tail=n;
    }
    void print_doublyLinkedList()
    {
        Node *temp=head;
        while (temp)
        {
            cout<<temp->key<<" "<<temp->data<<endl;
            temp=temp->next;
        }
        
    }
};
class LRUCache
{
public:
int capacity;
DoublyLinkedList d;
unordered_map<int,Node*> m;
LRUCache(int n)
{
    capacity=n;
}
void set(int key,int value)
{

    auto itr=m.find(key);
    if(itr==m.end())
    {
        if(m.size()==capacity)
        {
            int del=d.head->key;
            m.erase(del);
            d.delete_first_node();
        }
        Node *n=d.insert_node(key,value);
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
    auto itr=m.find(key);
    if(itr==m.end())
        return -1;
    Node *n=itr->second;
    int value=n->data;
    d.move_to_last(n);
    return value;
}
void print()
{
    d.print_doublyLinkedList();
}
};
int main()
{
    int s;
    cin>>s;
    LRUCache c(s);
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
    c.set(2,1);
    c.set(1,1);
    c.set(2,3);
    c.set(4,1);
    cout<<c.get(1)<<endl;
    cout<<c.get(2)<<endl;
    cout<<"------------------"<<endl;
    c.print();

}