#include <iostream>
#include <sstream>
using namespace std;
template <typename K,typename V>
class Node
{
    public:
    K key;
    V val;
    Node *next;
    Node(){}
    Node(K k,V v)
    {
        this->key=k;
        this->val=v;
        this->next=NULL;
    }
};
template <typename K,typename V>
class singlyLinkedList
{
    public:
    Node<K,V> *head;
    Node<K,V> *tail;
    singlyLinkedList()
    {
        this->head=NULL;
        this->tail=NULL;
    }
    Node<K,V>* insert_node(K key,V val)
    {
        Node<K,V> *n=new Node<K,V>(key,val);
        if(!head)
        {
            head=tail=n;
        }
        else
        {
            tail->next=n;
            tail=n;
        }
        return n;
    }
    void delete_node(K k)
    {
        Node<K,V> *temp=head;
        Node<K,V> *prev=NULL;
        while(temp && temp->key!=k)
        {
            prev=temp;
            temp=temp->next;
        }
        if(temp)
        {
            if(temp==head)
                head=head->next;
            if(temp==tail)
                tail=prev;
            if(prev)
                prev->next=temp->next;
            free(temp);
        }
    }
    Node<K,V>* find(K k)
    {
        bool found=false;
        Node<K,V> *temp=head;
        while(temp)
        {
            if(temp->key==k)
            {
                found=true;
                break;
            }
        }
        if(found)
            return temp;
        return NULL;
    }
};
template <typename K>
class Hashing
{
    public:
        int d=256,q=257;
int hash(K pt)
{
    ostringstream s;
    s<<pt;
    string pat=s.str();
    // string pat=to_string(pt);
    int l=pat.length();
    int p=0;
    for(int i=0;i<l;i++)
    {
        p=(d*p+pat[i])%q;
    }
    return p;
}
};
template <typename K,typename V>
class unordered_map
{
    public:
    singlyLinkedList<K,V> *arr;
    int q=257;
    V noelem=V();
    Hashing<K> h;
    unordered_map()
    {
        arr=new singlyLinkedList<K,V>[q];
    }

    void insert(K k,V v)
    {
        int indx=h.hash(k);
        Node<K,V> *temp=arr[indx].find(k);
        if(temp)
            temp->val=v;
        else
            arr[indx].insert_node(k,v);
    }
    void erase(K k)
    {
        int indx=h.hash(k);
        arr[indx].delete_node(k);
    }
    bool find(K k)
    {
        int indx=h.hash(k);
        Node<K,V> *temp=arr[indx].find(k);
        if(temp)
            return true;
        return false;
    }
    
    V& operator [](K k)
    {
        int indx=h.hash(k);
        Node<K,V> *temp=arr[indx].find(k);
        if(temp)
            return temp->val;
        Node<K,V> *n=arr[indx].insert_node(k,noelem);
        return n->val;
    }
    
};
template <typename K>
void count_distinct_elements(K a[],int n,int k)
{
    unordered_map<K,int> m;
    int count=0;
    for(int i=0;i<k;i++)
    {
        if(m.find(a[i]))
        {
            m[a[i]]=m[a[i]]+1;
        }
        else
        {
            count++;
            m.insert(a[i],1);
        }
    }
    cout<<count<<endl;
    for(int i=k;i<n;i++)
    {
        if(m[a[i-k]]==1)
        {
            count--;
            m.erase(a[i-k]);
        }
        else
        {
            m[a[i-k]]=m[a[i-k]]-1;
        }
        if(m.find(a[i]))
        {
            m[a[i]]=m[a[i]]+1;
        }
        else
        {
            count++;
            m.insert(a[i],1);
        }
        cout<<count<<endl;
    }
}
int main()
{
    unordered_map<string,string> m;
    // string a[7] = { "1", "2", "1", "3", "4", "2", "3" };
    // int k=4;
    m.insert("15.8","hello");
    m["15.8"]="peter";
    cout<<m.find("15.8")<<endl;
    cout<<m.find("hello")<<endl;
    cout<<m["15.8"]<<endl;
    // count_distinct_elements(a,7,k);
    
}