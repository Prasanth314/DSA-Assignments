#include <iostream>
using namespace std;
void transpose(int B[][3],int n)
{
    int temp;
    for(int i=0;i<n;i++)
    {
        temp=B[i][0];
        B[i][0]=B[i][1];
        B[i][1]=temp;
    }
}
void print(int B[][3],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<B[i][0]<<" "<<B[i][1]<<" "<<B[i][2]<<endl;
    }
}
void multiply(int A[][3],int B[][3],int C[][3],int m,int n,int &res)
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(A[i][1]==B[j][1])
            {
                C[res][0]=A[i][0];
                C[res][1]=B[j][0];
                C[res][2]=A[i][2]*B[j][2];
                res++;
            }
        }
    }
}
void sort(int A[][3],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(A[j][0]<A[i][0])
                swap(A[i],A[j]);
            else if(A[j][0]==A[i][0]&&A[j][1]<A[i][1])
                swap(A[i],A[j]);
        }
    }
}
void add_sorted_duplicates(int A[][3],int C[][3],int &res)
{
    int k=0,mul=A[0][2];
    for(int i=1;i<res;i++)
    {
        if(A[i][0]==A[i-1][0]&&A[i][1]==A[i-1][1])
        {
            mul+=A[i][2];
            cout<<mul<<endl;
        }
        else
        {
            C[k][0]=A[i-1][0];
            C[k][1]=A[i-1][1];
            C[k][2]=mul;
            mul=A[i][2];
            k++;
        }
    }
    C[k][0]=A[res-1][0];
    C[k][1]=A[res-1][1];
    C[k][2]=mul;
    k++;
    res=k;
}
int main()
{
    int rA,rB,cA,cB;
    cout<<"Enter rows and columns of 1st matrix";
    cin>>rA>>cA;
    cout<<"Enter rows and columns of 1st matrix";
    cin>>rB>>cB;
    int m=rA*cA;
    int n=rB*cB;
    int res=rA*cB;
    int A[m][3],B[n][3],C[res][3];
    int elem;
    m=0;
    n=0;
    res=0;
    cout<<"Enter the elements of 1st matrix";
    for(int i=0;i<rA;i++)
    {
        for(int j=0;j<cA;j++)
        {
            cin>>elem;
            if(elem!=0)
            {
                A[m][0]=i;
                A[m][1]=j;
                A[m][2]=elem;
                m++;
            }
        }
    }
    cout<<"Enter the elements of 2nd matrix";
    for(int i=0;i<rB;i++)
    {
        for(int j=0;j<cB;j++)
        {
            cin>>elem;
            if(elem!=0)
            {
                B[n][0]=i;
                B[n][1]=j;
                B[n][2]=elem;
                n++;
            }
        }
    }
    transpose(B,n);
    multiply(A,B,C,m,n,res);
    sort(C,res);
    cout<<res<<endl;
    print(C,res);
    int result[res][3];
    add_sorted_duplicates(C,result,res);
    print(result,res);
}