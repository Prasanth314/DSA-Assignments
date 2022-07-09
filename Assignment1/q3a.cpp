#include <iostream>
using namespace std;
class sparse
{
    public:
    int rows,columns;
    int noofnonzeros,maxsize;
    int **matrix;
    sparse(int r,int c)
    {
        noofnonzeros=0;
        rows=r;
        columns=c;
        maxsize=r*c+1;
        matrix=new int*[maxsize];
        for(int i=0;i<maxsize;i++)
            matrix[i]=new int[3];
    }
    void insert(int index,int r,int c,int v)
    {
        matrix[index][0]=r;
        matrix[index][1]=c;
        matrix[index][2]=v;
    }
    void take_input()
    {
        cout<<"Take input"<<endl;
        matrix[noofnonzeros][0]=rows;
        matrix[noofnonzeros][1]=columns;
        noofnonzeros++;
        int elem;
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<columns;j++)
            {
                cin>>elem;
                if(elem!=0)
                {
                    matrix[noofnonzeros][0]=i;
                    matrix[noofnonzeros][1]=j;
                    matrix[noofnonzeros][2]=elem;
                    noofnonzeros++;
                }
            }

        }
        matrix[0][2]=noofnonzeros-1;
    }
    void print_matrix()
    {
        cout<<"++++++++++++++++++++++++"<<endl;
        for(int i=1;i<noofnonzeros;i++)
        {
            cout<<matrix[i][0]<<" "<<matrix[i][1]<<" "<<matrix[i][2]<<endl;
        }
    }
    sparse add(sparse B)
    {
        auto &a=matrix;
        auto &b=B.matrix;
        sparse res(rows,columns);
        int aidx=1,bidx=1,residx=1;
        int sum=0;
        while(aidx<noofnonzeros && bidx<B.noofnonzeros)
        {
            if(a[aidx][0]<b[bidx][0] || (a[aidx][0]==b[bidx][0] && a[aidx][1]<b[bidx][1]))
            {
                res.insert(residx++,a[aidx][0],a[aidx][1],a[aidx][2]);
                aidx++;
            }
            else if(a[aidx][0]>b[bidx][0] || (a[aidx][0]==b[bidx][0] && a[aidx][1]>b[bidx][1]))
            {
                res.insert(residx++,b[bidx][0],b[bidx][1],b[bidx][2]);
                bidx++;
            }
            else
            {
                sum=a[aidx][2]+b[bidx][2];
                res.insert(residx++,a[aidx][0],a[aidx][1],sum);
                aidx++;
                bidx++;
            }
        }
        while(aidx<noofnonzeros)
        {
            res.insert(residx++,a[aidx][0],a[aidx][1],a[aidx][2]);
            aidx++;
        }
        while (bidx<B.noofnonzeros)
        {
           res.insert(residx++,b[bidx][0],b[bidx][1],b[bidx][2]);
           bidx++;
        }
        
        res.matrix[0][0]=rows;
        res.matrix[0][1]=columns;
        res.matrix[0][2]=residx-1;
        res.noofnonzeros=residx;
        return res;
    }
    sparse fast_transpose()
    {
        int total[columns]={0};
        for(int i=1;i<noofnonzeros;i++)
        {
            total[matrix[i][1]]++;
        }
        int index[columns+1];
        index[0]=1;
        for(int i=1;i<=columns;i++)
        {
            index[i]=index[i-1]+total[i-1];
        }
        sparse At(columns,rows);
        for(int i=1;i<noofnonzeros;i++)
        {
            At.insert(index[matrix[i][1]],matrix[i][1],matrix[i][0],matrix[i][2]);
            index[matrix[i][1]]++;
        }
        At.matrix[0][0]=columns;
        At.matrix[0][1]=rows;
        At.matrix[0][2]=matrix[0][2];
        At.noofnonzeros=noofnonzeros;
        return At;
    }
    sparse multiply(sparse B)
    {
        if(columns!=B.rows)
        {
            cout<<"Multiplication not possible";
            return sparse(0,0);
        }
        B=B.fast_transpose();
        print_matrix();
        B.print_matrix();
        auto &a=matrix;
        auto &b=B.matrix;
        sparse res(rows,B.rows);
        int aidx=1,bidx=1,residx=1;
        int r,c;
        int i=1,j=1;
        while(i<noofnonzeros)
        {
            r=a[i][0];
            j=1;
            while(j<B.noofnonzeros)
            {
                aidx=i;
                c=b[j][0];
                bidx=j;
                int sum=0;
                while (aidx<noofnonzeros && bidx<B.noofnonzeros)
                {
                    if(a[aidx][0]==r && b[bidx][0]==c)
                    {
                        if(a[aidx][1]==b[bidx][1])
                        {
                            cout<<"multiplying A("<<a[aidx][0]<<","<<a[aidx][1]<<")&B("<<b[bidx][0]<<","<<b[bidx][1]<<endl;
                            sum+=a[aidx][2]*b[bidx][2];
                            aidx++;
                            bidx++;
                        }
                        else if(a[aidx][1]<b[bidx][1])
                            aidx++;
                        else
                            bidx++;
                    }
                    else if(aidx>=noofnonzeros||a[aidx][0]>r)
                        break;
                    else if(bidx>=B.noofnonzeros||b[bidx][0]>c)
                        break;
                    cout<<"Executing"<<endl;
                }
                while(j<B.noofnonzeros && b[j][0]==c)
                {
                    j++;
                }
                if(sum)
                    res.insert(residx++,r,c,sum);
            }
            while(i<noofnonzeros && a[i][0]==r)
            {
                i++;
            }
        }
        res.matrix[0][0]=rows;
        res.matrix[0][1]=B.rows;
        res.matrix[0][2]=residx-1;
        res.noofnonzeros=residx;
        return res;
    }
};
int main()
{
    int rA,rB,cA,cB;
    cout<<"Enter rows and columns of 1st matrix";
    cin>>rA>>cA;
    cout<<"Enter rows and columns of 1st matrix";
    cin>>rB>>cB;
    sparse A(rA,cA);
    sparse B(rB,cB);
    A.take_input();
    B.take_input();
    sparse C=A.multiply(B);
    C.print_matrix();
}