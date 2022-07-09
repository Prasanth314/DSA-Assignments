#include <iostream>
using namespace std;
class BigInt
{
    public:
    string number;
    BigInt(string n)
    {
        number=n;
    }
    int isnonzero(string n)
    {
        n.erase(0,n.find_first_not_of("0"));
        if(n.length()>0)
            return 1;
        else
            return 0;
    }
    int isGreaterThan(string x,string y)
    {
        x.erase(0,x.find_first_not_of("0"));
        y.erase(0,y.find_first_not_of("0"));
        if(x.length()>y.length())
            return 1;
        else if(x.length()<y.length())
            return 0;
        else
        {
            for(int i=0;i<x.length();i++)
            {
                if(x[i]>y[i])
                    return 1;
                else if(x[i]<y[i])
                    return 0;
            }
        }
        return 0;
    }
    int isGreaterorequal(string x,string y)
    {
        x.erase(0,x.find_first_not_of("0"));
        y.erase(0,y.find_first_not_of("0"));
        if(x.length()>y.length())
            return 1;
        else if(x.length()<y.length())
            return 0;
        else
        {
            for(int i=0;i<x.length();i++)
            {
                if(x[i]>y[i])
                    return 1;
                else if(x[i]<y[i])
                    return 0;
            }
        }
        return 1;
    }
    int operator<=(BigInt b)
    {
        number.erase(0,number.find_first_not_of("0"));
        string &B=b.number;
        B.erase(0,B.find_first_not_of("0"));
        if(number.length()<B.length())
            return 1;
        else if(number.length()>B.length())
            return 0;
        else
        {
            for(int i=0;i<number.length();i++)
            {
                if(number[i]<B[i])
                    return 1;
                else if(number[i]>B[i])
                    return 0;
            }
        }
        return 1;
    }
    int operator>(BigInt b)
    {
        number.erase(0,number.find_first_not_of("0"));
        string &B=b.number;
        B.erase(0,B.find_first_not_of("0"));
        if(number.length()>B.length())
            return 1;
        else if(number.length()<B.length())
            return 0;
        else
        {
            for(int i=0;i<number.length();i++)
            {
                if(number[i]>B[i])
                    return 1;
                else if(number[i]<B[i])
                    return 0;
            }
        }
        return 0;
    }
    BigInt operator+(BigInt B)
    {
        string &a=this->number;
        string &b=B.number;
        int m=a.length()-1;
        int n=b.length()-1;
        int r=0;
        if(m>n)
        {
            r=m;
            b.insert(0,m-n,'0');
        }
        else
        {
            r=n;
            a.insert(0,n-m,'0');
        }
        string &res=a;
        int carry=0;
        // cout<<a<<endl;
        // cout<<b<<endl;
        for(int i=r;i>=0;i--)
        {
            int k=(a[i]-'0')+(b[i]-'0')+carry;
            if(k>9)
            {
                k-=10;
                carry=1;
            }
            else
                carry=0;
            res[i]=k+'0';
        }
        if(carry==1)
            res.insert(0,"1");
        res.erase(0,res.find_first_not_of("0"));
        b.erase(0,b.find_first_not_of("0"));
        return BigInt(res);
    }

    BigInt operator-(BigInt B)
    {
        string &a=this->number;
        string &b=B.number;
        string res=subtract(a,b);
        return BigInt(res);
    }
    string subtract(string &a,string &b)
    {
        a.erase(0,a.find_first_not_of("0"));
        b.erase(0,b.find_first_not_of("0"));
        int m=a.length()-1;
        int n=b.length()-1;
        int r=m;
        b.insert(0,m-n,'0');
        if(a.compare(b)==0)
            return "0";
        int borrow=0;
        string &res=a;
        // cout<<a<<endl;
        // cout<<b<<endl;
        for(int i=r;i>=0;i--)
        {
            int k=a[i]-b[i]-borrow;
            if(k<0)
            {
                k+=10;
                borrow=1;
            }
            else
                borrow=0;
            res[i]=k+'0';
        }
        res.erase(0,res.find_first_not_of("0"));
        b.erase(0,b.find_first_not_of("0"));
        return res;
    }
    BigInt operator*(BigInt b)
    {
        string small=this->number;
        string large=b.number;
        BigInt res("0");
        if(small.length()>large.length())
            small.swap(large);
        int llength=large.length();
        int slength=small.length();
        for(int i=slength-1;i>=0;i--)
        {
            int carry=0;
            BigInt t(large);
            string &internum=t.number;
            int num=small[i]-'0';
            for(int j=llength-1;j>=0;j--)
            {
                int k=num*(large[j]-'0')+carry;
                if(k>9)
                {
                    carry=k/10;
                    k%=10;
                }
                else
                    carry=0;
                internum[j]=k+'0';
            }
            if(carry!=0)
                internum.insert(0,1,carry+'0');
            internum.append(slength-1-i,'0');
            res=res+t;
        }
        res.number.erase(0,res.number.find_first_not_of("0"));
        return res;
    }
    BigInt exponentiation(long long int e)
    {
        BigInt n=*this;
        BigInt res("1");
        while (e!=0)
        {
            if(e&1)
                res=res*n;
            n=n*n;
            e>>=1;
        }
        return res;
    }
    BigInt factorial()
    {
        BigInt res("1");
        BigInt i("2");
        BigInt one("1");
        while(i<=*this)
        {
            res=res*i;
            i=i+one;
        }
        return res;
    }
    string mod(string x,string y)
    {
        int m=y.length();
        string sub=x.substr(0,m+1);
        while(isGreaterorequal(x,y))
        {

            while(isGreaterorequal(sub,y))
            {
                sub=subtract(sub,y);
            }
            x.replace(0,m+1,sub);
            sub=x.substr(0,m+1);
        }
        return x;
    }
    BigInt gcd(BigInt B)
    {
        string x=this->number;
        string y=B.number;
        string r;
        if(isGreaterThan(y,x))
        {
            x.swap(y);
        }
        while(isnonzero(y))
        {

            r=mod(x,y);
            x=y;
            y=r;
        }
        return BigInt(x);
    }
};
int findnext(string s,int i)
{
    for(int j=i+1;j<s.length();j++)
    {
        if(s[j]=='+'||s[j]=='-')
            return j;
    }
    return s.length();
}
void parseandcalculate(string &s)
{
    int nums=0,back=0,forw=0;
    int flag=1;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='x')
        {
            back=forw=i;
            flag=1;
            while(flag && back>=0)
            {
                back--;
                switch(s[back])
                {
                    case '+':
                    case '-':
                    case 'x':flag=0;
                    break;
                }
            }
            flag=1;
            while(flag && forw < s.length())
            {
                forw++;
                switch(s[forw])
                {
                    case '+':
                    case '-':
                    case 'x':flag=0;
                    break;
                }
            }
            string a=s.substr(back+1,i-back-1);
            string b=s.substr(i+1,forw-i-1);
            BigInt A(a);
            BigInt B(b);
            BigInt c=A*B;
            s.replace(back+1,forw-back-1,c.number);
            i=back;
            // cout<<a<<" x "<<b<<endl;
            // cout<<s<<endl;
        }
    }
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='+'||s[i]=='-')
        {
            int index=findnext(s,i);
            string a=s.substr(0,i);
            string b=s.substr(i+1,index-i-1);
            BigInt A(a);
            BigInt B(b);
            if(s[i]=='+')
            A=A+B;
            else
            A=A-B;
            s.replace(0,index,A.number);
            // cout<<a<<" op "<<b<<endl;
            // cout<<s<<endl;
            i=0;
        }
    }
}
int main()
{
    int type;
    cout<<"1 for exponentiation"<<endl;
    cout<<"2 for GCD"<<endl;
    cout<<"3 for factorial"<<endl;
    cout<<"4 for calculator"<<endl;
    cin>>type;
    string s;
    switch(type)
    {
        case 1:
        {   cin>>s;
            BigInt a(s);
            long long int e;
            cin>>e;
            BigInt res=a.exponentiation(e);
            cout<<res.number<<endl;
            break;
        }
        case 2:
        {
            cin>>s;
            BigInt a(s);
            cin>>s;
            BigInt b(s);
            BigInt c=a.gcd(b);
            cout<<c.number<<endl;
            break;
        }
        case 3:
        {
            cin>>s;
            BigInt a(s);
            BigInt res=a.factorial();
            cout<<res.number<<endl;
            break;
        }
        case 4:
        {
            cin>>s;
            parseandcalculate(s);
            cout<<s<<endl;
            break;
        }
    }
    // string s;
    // cin>>s;
    // BigInt a(s);
    // cin>>s;
    // BigInt b(s);
    // BigInt c=a.gcd(b);
    // cout<<"----------------------"<<endl;
    // cout<<c.number;
    // string s;
    // cin>>s;
    // parseandcalculate(s);

    // cout<<"Hello world";
}