#include <iostream>
#include <map>
#include <vector>
using namespace std;
class TrieNode
{
    public:
    map<char,TrieNode*> child_nodes;
    bool ended;
    char element;
    TrieNode(char c)
    {
        element=c;
        ended=false;
    }
};
class Trie
{
    public:
    TrieNode *root=NULL;
    Trie()
    {

    }
    void insert(string s)
    {
        if(s.size()==0)
            return;
        if(!root)
            root=new TrieNode('r');
        TrieNode *temp=root;
        for(int i=0;i<s.size();i++)
        {
            
            auto &um=temp->child_nodes;
            if(um.find(s[i])==um.end())
            {
                TrieNode *tn=new TrieNode(s[i]);
                um.insert(make_pair(s[i],tn));
            }
            temp=um[s[i]];
        }
        temp->ended=true;
        // cout<<s<<" inserted"<<endl;
    }
    int spellcheck(string s)
    {
        TrieNode *temp=root;
        for(int i=0;i<s.size();i++)
        {
            auto &um=temp->child_nodes;
            if(um.find(s[i])!=um.end())
            {
                temp=um[s[i]];
            }
            else
            {
                return 0;
            }
        }
        if(temp->ended)
            return 1;
        return 0;
    }
    vector<string> autocomplete(string s)
    {
        vector<string> res;
        TrieNode *temp=root;
        for(int i=0;i<s.size();i++)
        {
            auto &um=temp->child_nodes;
            if(um.find(s[i])!=um.end())
            {
                temp=um[s[i]];
            }
            else
            {
                return res;
            }
        }
        display_all(temp,s,res);
        return res;
    }
    void autocorrect(string s)
    {
        // lev_distance(root,s,"",0,3,0);
        vector<vector<int>> res;
        vector<int> a;
        for(int i=0;i<=s.size();i++)
        {
            a.push_back(i);
        }
        res.push_back(a);
        levsdisttable(root,res,s,"");
    }
    //                        Given string  ,Currentstring,current distance,maxallowed dist,current index
    void lev_distance(TrieNode *temp,string givens,string curs,int cd,int maxd,int index)
    {
        if(cd>=maxd)
            return;
        if(index==givens.size())
            return;
        bool flag=false;
        auto m=temp->child_nodes;
        for(auto i=m.begin();i!=m.end();i++)
        {
            
            if(givens[index]==i->first)
            {
                lev_distance(i->second,givens,curs+i->first,cd,maxd,index+1);
            }
            else
            {
                lev_distance(i->second,givens,curs+i->first,cd+1,maxd,index);
                if(!flag)
                {
                    lev_distance(temp,givens,curs,cd+1,maxd,index+1);
                    flag=true;
                }
                lev_distance(i->second,givens,curs+i->first,cd+1,maxd,index+1);
            }
            if(i->second->ended)
            {
                cout<<curs+i->first<<endl;
            }
        }
    }
    void levsdisttable(TrieNode *temp,auto &res,string s,string n)
    {
        int maxd=3;
        auto m=temp->child_nodes;
        int k=res.size();
        for(auto i=m.begin();i!=m.end();i++)
        {
            vector<int> a;
            a.push_back(k);
            for(int j=0;j<s.size();j++)
            {
                if(i->first==s[j])
                {
                    a.push_back(res[k-1][j-1]);
                }
                else
                {
                    a.push_back(min(res[k-1][j],res[k-1][j-1],a.back()));
                }
            }
            res.push_back(a);
            if(a.back()<maxd)
                levsdisttable(i->second,res,s,n+i->first);
            res.pop_back();
            if(a.back()<=maxd && i->second->ended)
                cout<<n+i->first<<endl;
        }
    }
    void display_all(TrieNode *r,string s,vector<string> &res)
    {
        if(!r)
            return;
        if(r->ended)
        {
            // cout<<s<<endl;
            res.push_back(s);
        }
        auto m=r->child_nodes;
        for(auto i=m.begin();i!=m.end();i++)
        {
            string n=s+i->first;
            display_all(i->second,n,res);
        }
        
    }
    int min(int a,int b,int c)
    {
        int m=a;
        if(m>b)
            m=b;
        if(m>c)
            m=c;
        return m;
    }
};
int main()
{
    Trie t;
    int n;
    cin>>n;
    string s;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        t.insert(s);
    }
    int ai;
    string ti;
    cin>>ai;
    cin>>ti;
    vector<string> res;
    switch(ai)
    {
        case 1:
        cout<<t.spellcheck(ti)<<endl;
        break;
        case 2:
            res=t.autocomplete(ti);
            cout<<res.size()<<endl;
            for(string x:res)
            {
                cout<<x<<endl;
            }
            break;
        case 3:
            res=t.autocomplete(ti);
            cout<<res.size()<<endl;
            for(string x:res)
            {
                cout<<x<<endl;
            }
            break;
    }
    // t.insert("aad");
    // t.insert("am");
    // t.insert("she");
    // t.insert("ash");
    // t.insert("ashwant");
    // t.insert("ashwarya");
    // cout<<"^^^^^^^^^^^^^"<<endl;
    // // t.display_all(t.root,"");
    // cout<<"printed all"<<endl;
    // cout<<"####################"<<endl;
    // vector<string> res1=t.autocomplete("ash");
    // t.autocorrect("ash");
}