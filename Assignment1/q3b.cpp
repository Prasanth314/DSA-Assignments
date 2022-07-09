#include <iostream>
using namespace std;
template <typename T>
class Node
{
    public:
    int row;
    int column;
    T data;
    Node *next;
    Node(int row,int column,T data)
    {
        this->data=data;
        this->row=row;
        this->column=column;
        this->next=NULL;
    }
    int operator<(Node *n)
    {
        if(row<n->row)
            return 1;
        else if(row==n->row && column<n->column)
            return 1;
        else
            return 0;
    }

};

template <typename T>
class LinkedList
{
    public:

    Node<T> *head;
    Node<T> *tail;
    LinkedList()
    {
        this->head=NULL;
        this->tail=NULL;
    }
    void insert_node(int row,int column,T data)
    {
        Node<T> *n=new Node<T>(row,column,data);
        if(!this->head)
        {
            this->head=n;
        }
        else
        {
            this->tail->next=n;
        }
        this->tail=n;
    }
    void take_matrix_data(int r,int c)
    {
        T elem;
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                cin>>elem;
                if(elem!=0)
                {
                    insert_node(i,j,elem);
                }
            }
        }
    }
    void print_linked_list()
    {
        cout<<"++++++++++++++++++++++++++++++"<<endl;
        Node<T> *temp=head;
        while(temp)
        {
            cout<<temp->row<<" "<<temp->column<<" "<<temp->data<<endl;
            temp=temp->next;
        }
    }
    void transpose()
    {
        Node<T> *temp=head;
        int t;
        while(temp)
        {
            t=temp->row;
            temp->row=temp->column;
            temp->column=t;
            temp=temp->next;
        }
        // print_linked_list();
        head=sort(head);
    }
    void multiply(LinkedList A,LinkedList B)
    {
        B.transpose();
        // B.print_linked_list();
        // A.print_linked_list();
        Node<T> *i=A.head;
        Node<T> *j=B.head;
        Node<T> *res=head;
        Node<T> *aidx,*bidx,*residx;
        int r,c;
        while(i!=NULL)
        {
            r=i->row;
            j=B.head;
            while(j!=NULL)
            {
                aidx=i;
                c=j->row;
                bidx=j;
                T sum=0;
                while (aidx!=NULL && bidx!=NULL)
                {
                    if(aidx->row==r && bidx->row==c)
                    {
                        if(aidx->column==bidx->column)
                        {
                            sum+=(aidx->data)*(bidx->data);
                            aidx=aidx->next;
                            bidx=bidx->next;
                        }
                        else if(aidx->column < bidx->column)
                            aidx=aidx->next;
                        else
                            bidx=bidx->next;
                    }
                    else if(aidx==NULL || aidx->row > r)
                        break;
                    else if(bidx==NULL || bidx->row > c)
                        break;
                }
                while(j!=NULL && j->row ==c)
                {
                    j=j->next;
                }
                if(sum)
                {
                    insert_node(r,c,sum);
                }

            }
            while(i!=NULL && i->row==r)
            {
                i=i->next;
            }
        }
    }
    void split(Node<T> *f,Node<T> **fsthalf,Node<T> **sechalf)
    {
        Node<T> *fast;
        Node<T> *slow;
        slow=f;
        fast=slow->next;
        while(fast!=NULL)
        {
            fast=fast->next;
            if(fast!=NULL)
            {
                slow=slow->next;
                fast=fast->next;
            }
        }
        *fsthalf=f;
        *sechalf=slow->next;
        slow->next=NULL;
    }
    Node<T>* merge(Node<T> *first,Node<T> *second)
    {
        Node<T> *temp=NULL;
        if(first==NULL)
            return second;
        else if(second==NULL)
            return first;
        if(*first<second)
        {
            temp=first;
            first=first->next;
        }
        else
        {
            temp=second;
            second=second->next;
        }
        Node<T> *result=temp;
        while(first!=NULL && second!=NULL)
        {
            if(*first<second)
            {
                temp->next=first;
                first=first->next;
            }
            else
            {
                temp->next=second;
                second=second->next;
            }
            temp=temp->next;
        }
        while(first!=NULL)
        {
            temp->next=first;
            first=first->next;
            temp=temp->next;
        }
        while(second!=NULL)
        {
            temp->next=second;
            second=second->next;
            temp=temp->next;
        }
        temp->next=NULL;
        return result;
    }
    Node<T>* sort(Node<T> *h)
    {
        if((h==NULL)||(h->next==NULL))
        {
            return h;
        }
        Node<T> *firsthalf,*secondhalf;
        split(h,&firsthalf,&secondhalf);
        firsthalf=sort(firsthalf);
        secondhalf=sort(secondhalf);
        // print(firsthalf);
        // print(secondhalf);
        Node<T> *result=merge(firsthalf,secondhalf);
        return result;
    }
    void print(Node<T> *h)
    {
        cout<<"=========================="<<endl;
        Node<T> *temp=h;
        while(temp)
        {
            cout<<temp->row<<" "<<temp->column<<" "<<temp->data<<endl;
            temp=temp->next;
        }
    }
    void add(LinkedList A,LinkedList B)
    {
        Node<T> *i=A.head;
        Node<T> *j=B.head;
        
        T sum=0;
        while(i!=NULL && j!=NULL)
        {
            if(*i<j)
            {
                insert_node(i->row,i->column,i->data);
                i=i->next;
            }
            else if(*j<i)
            {
                insert_node(j->row,j->column,j->data);
                j=j->next;
            }
            else
            {
                sum=(i->data)+(j->data);
                if(sum)
                    insert_node(i->row,i->column,sum);
                i=i->next;
                j=j->next;
            }
        }
        while(i!=NULL)
        {
            insert_node(i->row,i->column,i->data);
            i=i->next;
        }
        while(j!=NULL)
        {
            insert_node(j->row,j->column,j->data);
            j=j->next;
        }
    }
};
int main()
{
    int rA,rB,cA,cB;
    cout<<"Enter rows and columns of 1st matrix";
    cin>>rA>>cA;
    cout<<"Enter rows and columns of 2nd matrix";
    cin>>rB>>cB;
    LinkedList<double> A;
    LinkedList<double> B;
    A.take_matrix_data(rA,cA);
    B.take_matrix_data(rB,cB);
    // B.transpose();
    // B.print_linked_list();
    //NOTE: First perform Addition nd then multiplication because its makes inplace transformation
    LinkedList<double> D;
    D.add(A,B);
    cout<<"Addition"<<endl;
    D.print_linked_list();
    LinkedList<double> C;
    C.multiply(A,B);
    cout<<"Multiplication"<<endl;
    C.print_linked_list();
    
}