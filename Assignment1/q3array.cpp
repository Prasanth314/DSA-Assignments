#include <iostream>
using namespace std;
template <typename T>
class Node
{
    public:
    int row;
    int column;
    T data;
    Node(int row,int column,T data)
    {
        this->data=data;
        this->row=row;
        this->column=column;
    }
};

template <typename T>
class sparse
{
    public:
    int rows,columns;
    int noofnonzeros,maxsize;
    Node<T> **matrix;
    sparse(int r,int c)
    {
        noofnonzeros=0;
        rows=r;
        columns=c;
        maxsize=r*c+1;
        matrix=new Node<T>*[maxsize];
        for(int i=0;i<maxsize;i++)
            matrix[i]=NULL;
    }
    void insert(int index,int r,int c,T v)
    {
        matrix[index]=new Node<T>(r,c,v);
    }
    void take_input()
    {
       
        matrix[noofnonzeros]=new Node<T>(0,0,0);
        matrix[noofnonzeros]->row=rows;
        matrix[noofnonzeros]->column=columns;
        noofnonzeros++;
        T elem;
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<columns;j++)
            {
                cin>>elem;
                if(elem!=0)
                {
                    insert(noofnonzeros,i,j,elem);
                    noofnonzeros++;
                }
            }

        }
        // matrix[0]->data=noofnonzeros-1;
    }
    void print_matrix()
    {
        cout<<"++++++++++++++++++++++++"<<endl;
        for(int i=1;i<noofnonzeros;i++)
        {
            cout<<matrix[i]->row<<" "<<matrix[i]->column<<" "<<matrix[i]->data<<endl;
        }
    }
    sparse add(sparse B)
    {
        auto &a=matrix;
        auto &b=B.matrix;
        sparse<T> res(rows,columns);
        int aidx=1,bidx=1,residx=1;
        T sum=0;
        while(aidx<noofnonzeros && bidx<B.noofnonzeros)
        {
            if(a[aidx]->row < b[bidx]->row || (a[aidx]->row == b[bidx]->row && a[aidx]->column<b[bidx]->column))
            {
                res.insert(residx++,a[aidx]->row,a[aidx]->column,a[aidx]->data);
                aidx++;
            }
            else if(a[aidx]->row > b[bidx]->row || (a[aidx]->row==b[bidx]->row && a[aidx]->column>b[bidx]->column))
            {
                res.insert(residx++,b[bidx]->row,b[bidx]->column,b[bidx]->data);
                bidx++;
            }
            else
            {
                sum=a[aidx]->data+b[bidx]->data;
                res.insert(residx++,a[aidx]->row,a[aidx]->column,sum);
                aidx++;
                bidx++;
            }
        }
        while(aidx<noofnonzeros)
        {
            res.insert(residx++,a[aidx]->row,a[aidx]->column,a[aidx]->data);
            aidx++;
        }
        while (bidx<B.noofnonzeros)
        {
           res.insert(residx++,b[bidx]->row,b[bidx]->column,b[bidx]->data);
           bidx++;
        }
        
        res.noofnonzeros=residx;
        return res;
    }
    sparse fast_transpose()
    {
        int total[columns]={0};
        for(int i=1;i<noofnonzeros;i++)
        {
            total[matrix[i]->column]++;
        }
        int index[columns+1];
        index[0]=1;
        for(int i=1;i<=columns;i++)
        {
            index[i]=index[i-1]+total[i-1];
        }
        sparse<T> At(columns,rows);
        for(int i=1;i<noofnonzeros;i++)
        {
            At.insert(index[matrix[i]->column],matrix[i]->column,matrix[i]->row,matrix[i]->data);
            index[matrix[i]->column]++;
        }

        At.noofnonzeros=noofnonzeros;
        return At;
    }
    sparse multiply(sparse B)
    {
        // if(columns!=B.rows)
        // {
        //     cout<<"Multiplication not possible";
        //     return sparse<T>(0,0);
        // }
        B=B.fast_transpose();
        auto &a=matrix;
        auto &b=B.matrix;
        sparse<T> res(rows,B.rows);
        int aidx=1,bidx=1,residx=1;
        int r,c;
        int i=1,j=1;
        while(i<noofnonzeros)
        {
            r=a[i]->row;
            j=1;
            while(j<B.noofnonzeros)
            {
                aidx=i;
                c=b[j]->row;
                bidx=j;
                T sum=0;
                while (aidx<noofnonzeros && bidx<B.noofnonzeros)
                {
                    if(a[aidx]->row == r && b[bidx]->row==c)
                    {
                        if(a[aidx]->column == b[bidx]->column)
                        {
                            sum+=(a[aidx]->data)*(b[bidx]->data);
                            aidx++;
                            bidx++;
                        }
                        else if(a[aidx]->column < b[bidx]->column)
                            aidx++;
                        else
                            bidx++;
                    }
                    else if(aidx>=noofnonzeros||a[aidx]->row > r)
                        break;
                    else if(bidx>=B.noofnonzeros||b[bidx]->row > c)
                        break;
                    
                }
                while(j<B.noofnonzeros && b[j]->row == c)
                {
                    j++;
                }
                if(sum)
                    res.insert(residx++,r,c,sum);
            }
            while(i<noofnonzeros && a[i]->row == r)
            {
                i++;
            }
        }
 
        res.noofnonzeros=residx;
        return res;
    }
};
int main()
{
    int rA,rB,cA,cB;
    cout<<"Enter rows and columns of 1st matrix";
    cin>>rA>>cA;
    cout<<"Enter rows and columns of 2nd matrix";
    cin>>rB>>cB;
    sparse<double> A(rA,cA);
    sparse<double> B(rB,cB);
    cout<<"Enter the elements of matrix A:"<<endl;
    A.take_input();
    cout<<"Enter the elements of matrix B:"<<endl;
    B.take_input();
    sparse<double> C=A.multiply(B);
    sparse<double> D=A.add(B);
    cout<<"Multiplication"<<endl;
    C.print_matrix();
    cout<<"Addition"<<endl;
    D.print_matrix();
}