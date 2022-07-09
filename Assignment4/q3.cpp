#include <iostream>
using namespace std;
class TrieNode
{
    public:
    TrieNode* left;
    TrieNode* right;
    bool ended;
    TrieNode()
    {
        left=NULL;
        right=NULL;
        ended=false;
    }
};
class Trie
{
    public:
    TrieNode *root=NULL;
    int maxlength;
    Trie()
    {
        root=new TrieNode();
        maxlength=1;
    }
    int getRightMostSetBit(long long x)
    {
        x|=x>>1;
        x|=x>>2;
        x|=x>>4;
        x|=x>>8;
        x|=x>>16;
        x|=x>>32;
        return x-(x>>1);
    }
    void adjust(TrieNode *n,int l)
    {
        if(l<=maxlength)
        return;
        for(int i=0;i<l-maxlength;i++)
        {
            TrieNode *n=new TrieNode();
            n->left=root;
            root=n;
        }
    }
    void insert(long long x)
    {
        int p=getRightMostSetBit(x);
        // adjust(root,p);
        TrieNode *n=root;
        // cout<<x<<endl;
        for(long long i=42;i>=0;i--)
        {
            bool b=(bool)(x&(1LLU<<i));
            if(b)
            {
                if(!(n->right))
                    n->right=new TrieNode();
                n=n->right;
                // cout<<x<<" "<<i<<endl;
            }
            else
            {
                if(!(n->left))
                    n->left=new TrieNode();
                n=n->left;
                // cout<<x<<" "<<"0"<<endl;
            }
        }
        n->ended=true;
    }
    long long maxXor(long long x)
    {
        TrieNode *n=root;
        long long result=0;
        for(long long i=42;i>=0;i--)
        {
            bool b=(bool)(x&(1LLU<<i));
            if(b==0)
            {
                if(n->right)
                {
                    result+=(1LLU<<i);
                    n=n->right;
                }
                else
                    n=n->left;
            }
            else
            {
                if(n->left)
                {
                    result+=(1LLU<<i);
                    n=n->left;
                }
                else
                    n=n->right;
            }
        }
        // cout<<result<<endl;
        return result;
    }
    void printbinary(TrieNode *n,string s)
    {
        if(n->ended)
        {
            cout<<s<<endl;
        }
        if(n->left)
        {
            s+="0";
            printbinary(n->left,s);
        }
        if(n->right)
        {
            s+="1";
            printbinary(n->right,s);
        }
        
    }
};
int main()
{
    int n,q;
    cin>>n>>q;
    Trie t;
    long long e;
    for(int i=0;i<n;i++)
    {
        cin>>e;
        t.insert(e);
    }
    // for(int i=0;i<n;i++)
    // {
    //     cout<<arr[i]<<endl;
    // }
    long long res[q];
    for(int i=0;i<q;i++)
    {
        // Call Max XOR
        cin>>e;
        res[i]=t.maxXor(e);
    }
    // cout<<"******"<<endl;
    for(int i=0;i<q;i++)
    {
        cout<<res[i]<<endl;
    }
    // t.printbinary(t.root,"");
}