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
    void LPS(int l)
    {
        vector<int> lcp=kasai();
        int m=0;
        string result;
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
        // cout<<"Segemnt tree calculated"<<endl;
        // cout<<"size:"<<l<<endl;
        for(int i=0;i<n-1;i++)
        {
            if((suffix[i]<l && suffix[i+1]>l) || (suffix[i]>l && suffix[i+1]<l))
            {
                if(lcp[i]>m)
                {
                    m=lcp[i];
                    result=s.substr(suffix[i],lcp[i]);
                    // cout<<"i:"<<i<<" suffix:"<<suffix[i]<<result<<endl;
                }
            }
        }
        // cout<<"###########"<<endl;
        cout<<result<<endl;
    }
};

int main()
{
    string s;
    cin>>s;
    string rev=string(s.rbegin(),s.rend());

    suffixarray sar(s+"$"+rev);
    int *sa=sar.getSuffixArray();
    sar.LPS(s.size());
}