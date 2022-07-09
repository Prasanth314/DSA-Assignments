#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<string,int>> result;
int k=0;
bool comp(pair<string,int> &a,pair<string,int> &b)
{
    if(a.second<b.second)
        return true;
    else if(a.second==b.second && a.first<b.first)
        return true;
    else
        return false;
}
void dijkstra(vector<vector<int>> g,int s,int n)
{
    int dist[n];
    bool visited[n];
    int path[n];
    for(int i=0;i<n;i++)
    {
        dist[i]=1000;
        visited[i]=false;
        path[i]=n;
    }
    dist[s]=0;
    for(int i=0;i<n-1;i++)
    {
        int minnode=n;
        int mindist=1000;
        for(int j=0;j<n;j++)
        {
            int d=dist[j];
            if(!visited[j] && d<mindist)
            {
                mindist=d;
                minnode=j;
            }
        }
        visited[minnode]=true;
        for(int j=0;j<n;j++)
        {
            if(!visited[j] && (g[minnode][j]+dist[minnode]<dist[j] || (g[minnode][j]+dist[minnode]==dist[j] && path[j]>minnode)))
            {
                dist[j]=dist[minnode]+g[minnode][j];
                path[j]=minnode;
            }
        }
        // cout<<"Dist updated"<<endl;
        // for(int i=0;i<n;i++)
        // {
        //     cout<<dist[i]<<" ";
        // }
    }
    // for(int i=0;i<n;i++)
    // {
    //     cout<<path[i]<<endl;
    // }
    for(int i=k;i<n;i++)
    {
        if(i==s)
            continue;
        int city;
        string sdpath="";
        // cout<<"city "<<i<<endl;
        for(city=i;city!=s;city=path[city])
        {
            // cout<<city<<endl;
            sdpath=to_string(city)+" "+sdpath;
        }
        sdpath=to_string(city)+" "+sdpath;
        // cout<<sdpath<<" PATH"<<endl;
        result.push_back(make_pair(sdpath,dist[i]));
    }
    k++;
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n,vector<int>(n,1000));
    int graph[n][m];
    int a,b,c;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        g[a][b]=c;
        g[b][a]=c;
    }
    for(int i=0;i<n;i++)
    {
        g[i][i]=0;
    }
    int k;
    cin>>k;
    for(int i=0;i<n;i++)
        dijkstra(g,i,n);
    sort(result.begin(),result.end(),comp);
    for(int i=0;i<k;i++)
    {
        cout<<result[i].first<<endl;
    }
    return 0;
}