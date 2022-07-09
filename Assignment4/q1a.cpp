#include <iostream>
#include <map>
using namespace std;
class suffixarray
{
    public:
    string s;
    int *suffix;
    suffixarray(string x)
    {
        s=x;
        suffix=new int[s.size()];
        // for(int i=0;i<s.size();i++)
        // {
        //     suffix[i]=0;
        //     cout<<suffix[i]<<" ";
        // }
    }
    int* getSuffixArray()
    {
        
        map<string,int> m;
        int n=s.size();
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
};

int main()
{
    string s;
    cin>>s;
    suffixarray sa(s);
    int n=s.size();
    // cout<<s.max_size()<<endl;
    int *arr=sa.getSuffixArray();
    
    // for(int i=0;i<s.size();i++)
    // {
    //     cout<<arr[i]<<" ";
    // }
    // cout<<endl;
    
    string result=s.substr(arr[0])+s.substr(0,arr[0]);
    for(int i=1;i<s.size();i++)
    {
        string temp=s.substr(arr[i])+s.substr(0,arr[i]);
        if(s[arr[i]]==s[arr[i-1]])
        {
            if(temp<result)
            {
                result=temp;
            }
        }
        else
        {
            break;
        }
    }
    cout<<result<<endl;

    return 0;
}