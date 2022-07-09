#include <iostream>
#include <vector>
using namespace std;
class AdlNode
{
    public:
    int node;
    int dist;
    // AdlNode* next;
    AdlNode(int n,int d)
    {
        node=n;
        dist=d;
        // next=NULL;
    }
};
// class Adl
// {
//     public:
//     AdlNode* head;
//     AdlNode* tail;
//     Adl(int i)
//     {
//         head=tail=new AdlNode(i,0);
//     }
//     void insert(int n,int d)
//     {
//         AdlNode* node=new AdlNode(n,d);
//         if(!this->head)
//         {
//             this->head=node;
//         }
//         else
//         {
//             this->tail->next=node;
//         }
//         this->tail=node;
//     }
    
// };
class Graph
{
    public:
    vector<vector<AdlNode*>> nodes_list;
    int n;
    Graph(int l)
    {
        n=l;
        for(int i=0;i<n;i++)
        {
            vector<AdlNode*> a;
            a.push_back(new AdlNode(i,0));
            nodes_list.push_back(a);
        }
    }
    void insert(int i,int j,int w)
    {
        nodes_list[i].push_back(new AdlNode(j,w));
        nodes_list[j].push_back(new AdlNode(i,w));
    }
    void display()
    {
        for(auto l:nodes_list)
        {
            for(auto n:l)
            {
                cout<<n->node<<" "<<n->dist<<endl;
            }
        }
    }
    void singledestpaths(int dest_node)
    {
        int distance[n];
        int path[n];
        for(int i=0;i<n;i++)
        {
            distance[i]=100;
            path[i]=n;
        }
        
        dijkstra(dest_node,distance,path);
        // cout<<"call over"<<endl;
        for(int i=0;i<n;i++)
        {
            if(i==dest_node)
                continue;
            int city;
            for(city=i;city!=dest_node;city=path[city])
            {
                cout<<city<<" ";
            }
            cout<<city<<endl;
        }
    }
    void dijkstra(int dest_node,int* distance,int* path)
    {
        distance[dest_node]=0;
        auto temp=nodes_list[dest_node];
        
        bool flag[n];
        for(int i=0;i<n;i++)
        {
            flag[i]=false;
        }
        
        for(int i=0;i<n-1;i++)
        {
            int minnode=n;
            int mindist=100;
            for(int j=0;j<n;j++)
            {
                int d=distance[j];
                if(!flag[j] && d<mindist)
                {
                    mindist=d;
                    minnode=j;
                }
            }
            // cout<<"DDDDDDDDDDDDDDD"<<minnode<<endl;
            flag[minnode]=true;
            temp=nodes_list[minnode];
            for(int j=1;j<temp.size();j++)
            {
                int nd=temp[j]->node;
                int d=temp[j]->dist;
                if(!flag[nd] && (distance[minnode]+d<distance[nd] || (distance[minnode]+d==distance[nd] && path[nd]>minnode)))
                {
                    distance[nd]=distance[minnode]+d;
                    path[nd]=minnode;
                }
            }

        }
    }
};
int main()
{
    int n,m;
    cin>>n>>m;
    Graph g(n);
    int a,b,c;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        g.insert(a,b,c);
    }
    int dest_node;
        cin>>dest_node;
    g.singledestpaths(dest_node);
    // g.display();
}