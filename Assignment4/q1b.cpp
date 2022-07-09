#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define INT_MAX 1e9;
int min(int a,int b)
{
    if(a<b)
        return a;
    return b;
}
int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
int MinRangeQuery(vector<int> &st,int index,int qs,int qe,int start,int end)
{
    if(end<qs || start >qe)
    {
        return INT_MAX;
    }
    if(qs<=start && qe>=end)
    {
        return st[index];
    }
    int m=start+(end-start)/2;
    return min(MinRangeQuery(st,2*index+1,qs,qe,start,m),MinRangeQuery(st,2*index+2,qs,qe,m+1,end));

}
int getsegmentTree(vector<int> &lcp,vector<int> &st,int start,int end,int index)
{
    if(start==end)
    {
        st[index]=lcp[start];
        return st[index];
    }
    int m=start+(end-start)/2;
    st[index]=min(getsegmentTree(lcp,st,start,m,2*index+1),getsegmentTree(lcp,st,m+1,end,2*index+2));
    // cout<<"segment tee"<<endl;
    return st[index];
}
class suffixarray
{
    public:
    string s;
    int *suffix;
    
    int n;
    suffixarray(string x)
    {
        s=x;
        n=s.size();
        suffix=new int[n];
        // lcp=new int[n];
    }
    int* getSuffixArray()
    {
        
        map<string,int> m;
        // int n=s.size();
        string temp="";
        for(int i=n-1;i>=0;i--)
        {
            temp=s[i]+temp;
            m[temp]=i;
        }
        // cout<<"Map DONE"<<endl;
        int k=0;
        
        for(auto x:m)
        {
            suffix[k++]=x.second;
        }
        
        return suffix;
    }
    vector<int> kasai()
    {
        vector<int> lcp(n,0);
        vector<int> rank(n,0);
        for(int i=0;i<n;i++)
        {
            rank[suffix[i]]=i;
        }
        int h=0;
        for(int i=0;i<n;i++)
        {
            if(rank[i]==n-1)
            {
                h=0;
                continue;
            }
            int k=suffix[rank[i]+1];
            while(k+h<n && i+h<n && s[i+h]==s[k+h])
            {
                h++;
            }
            lcp[rank[i]]=h;
            if(h>0)
                h--;
        }
        return lcp;
    }
    void LCSk(int k)
    {
        vector<int> lcp=kasai();
        // for(int i=0;i<n;i++)
        // {
        //     cout<<suffix[i]<<" ";
        // }
        // cout<<"Suffix"<<endl;
        // for(int i:lcp)
        // {
        //     cout<<i<<" ";
        // }
        // cout<<"LCP"<<endl;
        vector<int> st(n,0);
        int indx=getsegmentTree(lcp,st,0,n-1,0);
        // for(int i:st)
        // {
        //     cout<<i<<" ";
        // }
        int result=0;
        // cout<<"Segemnt tree calculated"<<endl;
        for(int i=0;i<n-k+1;i++)
        {
            result=max(result,MinRangeQuery(st,0,i,i+k-2,0,n-1));
        }
        // cout<<"Range done"<<endl;
        cout<<result<<endl;
    }
};

int main()
{
    string s;
    cin>>s;
    int k;
    cin>>k;
    suffixarray sar(s);
    int *sa=sar.getSuffixArray();
    sar.LCSk(k);
}