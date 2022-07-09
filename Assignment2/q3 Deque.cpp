#include <iostream>
using namespace std;
template<typename T>
class deque
{
    public:
    int max_size,curr_size;
    int head=-1,tail=-1;
    T noelem=T();
    T *arr;
    deque()
    {
        max_size=10;
        curr_size=0;
        arr=new T[10];
    }
    deque(int n,T x)
    {
        max_size=n;
        curr_size=0;
        arr=new T[n];
        for(int i=0;i<n;i++)
        {
            arr[i]=x;
        }
        head=0;
        tail=n-1;
    }
    void push_back(T x)
    {
        if(curr_size==max_size)
        {
            resize(2*max_size,noelem);
            tail=max_size;
            max_size=2*max_size;
            // cout<<"Deque Full"<<endl;
            // return;
        }
        if(head==-1)
        {
            head=tail=0;
        }
        else if(tail==max_size-1)
        {
            tail=0;
        }
        else
        {
            tail++;
        }
        arr[tail]=x;
        curr_size++;
    }
    void pop_back()
    {
        if(curr_size==0)
        {
            cout<<"Deque Empty"<<endl;
            return;
        }
        int elem=arr[tail];
        if(curr_size==1)
        {
            head=tail=-1;
        }
        if(tail==0)
        {
            tail=max_size-1;
        }
        else
        {
            tail--;
        }
        curr_size--;
    }
    void push_front(T x)
    {
        if(curr_size==max_size)
        {
            resize(2*max_size,noelem);
            tail=max_size;
            max_size=2*max_size;
            // cout<<"Deque Full"<<endl;
            // return;
        }
        if(head==-1)
        {
            head=tail=max_size-1;
        }
        else if(head==0)
        {
            head=max_size-1;
        }
        else
        {
            head--;
        }
        arr[head]=x;
        curr_size++;
    }
    void pop_front()
    {
        if(curr_size==0)
        {
            cout<<"Deque Empty"<<endl;
            return;
        }
        int elem=arr[head];
        if(curr_size==1)
        {
            head=tail=-1;
        }
        if(head==max_size-1)
        {
            head=0;
        }
        else
        {
            head++;
        }
        curr_size--;
    }
    T front()
    {
        if(curr_size==0)
        {
            cout<<"Deque Empty"<<endl;
            return noelem;
        }
        return arr[head];
    }
    T back()
    {
        if(curr_size==0)
        {
            cout<<"Deque Empty"<<endl;
            return noelem;
        }
        return arr[tail];
    }
    bool empty()
    {
        return (curr_size==0);
    }
    int size()
    {
        return curr_size;
    }
    void resize(int x,T val)
    {
        if(x>max_size)
        {
            T *new_arr=new T[x];
            int k=0;
            int j=head;
            for(int i=0;i<curr_size;i++)
            {
                new_arr[k++]=arr[j];
                j=(j+1)%max_size;
            }
            while(k<x)
            {
                new_arr[k++]=val;
            }
            head=0;
            tail=x-1;
            arr=new_arr;
            max_size=x;
            curr_size=x;
        }
        else if(x>curr_size)
        {
            while(x>curr_size)
            {
                push_back(val);
            }
        }
        else
        {
            while(x<curr_size)
            {
                pop_back();
            }
        }
    }
    void clear()
    {
        head=tail=-1;
        curr_size=0;
    }
    T& operator[](int indx)
    {
        if(indx<0 || indx>curr_size)
        {
            cout<<"Array index out of bounds"<<endl;
            return noelem;
        }
        return arr[(head+indx)%max_size];
    }
    void print()
    {
        int j=head;
        for(int i=0;i<curr_size;i++)
        {
            cout<<arr[j]<<" ";
            j=(j+1)%max_size;
        }
    }
};
int main()
{
    deque<float> d;
    
    d.push_front(10.12);
    d.push_front(11.23);
    d.push_front(12.24);
    d.push_back(13.25);
    d.push_back(14.29);
    d.push_back(18.36);
    d.resize(20,3);
    cout<<d[2]<<endl;
    d.print();
    cout<<endl;
    cout<<d.front()<<endl;
    cout<<d.back()<<endl;
    cout<<d.size()<<endl;
    d.clear();
    cout<<d.front()<<endl;

}