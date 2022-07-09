#include <iostream>
#include <vector>
using namespace std;
vector<int> rq;
vector<int> cq;
vector<int> ridersr;
vector<int> ridersc;
int move_count=0;
int nodes_left_in_layer=1;
int nodes_in_next_layer=0;
bool reached_end=false;
void explore(int row,int column,auto &grid,auto &visited)
{
    int dr[]={-1,1,0,0};
    int dc[]={0,0,1,-1};
    int rr,cc;
    grid[row][column]='.';
    for(int i=0;i<4;i++)
    {
        rr=row+dr[i];
        cc=column+dc[i];

        if(cc<0)
            continue;
        if(grid[rr][cc]=='#'||grid[rr][cc]=='R')
            continue;
        if(visited[rr][cc])
            continue;
        rq.push_back(rr);
        cq.push_back(cc);
        visited[rr][cc]=true;
        nodes_in_next_layer++;
        if(grid[rr][cc]!='S')
            grid[rr][cc]='A';
    }

    
}
void explore_riders(auto &grid)
{
    int n=ridersr.size();
    int row,column,rr,cc;
    int dr[]={-1,1,0,0};
    int dc[]={0,0,1,-1};
    for(int i=0;i<n;i++)
    {
        row=ridersr.front();
        ridersr.erase(ridersr.begin());
        column=ridersc.front();
        ridersc.erase(ridersc.begin());
        for(int i=0;i<4;i++)
        {
            rr=row+dr[i];
            cc=column+dc[i];

            if(cc<0)
                continue;
            if(grid[rr][cc]=='#'||grid[rr][cc]=='A'||grid[rr][cc]=='R')
                continue;

            ridersr.push_back(rr);
            ridersc.push_back(cc);
            grid[rr][cc]='R';
        }
    }
}
int dungeon(vector<vector<char>> grid,int r,int c)
{
    int sr=r-2,sc=c-2;
    grid[1][0]='S';

    
    // bool visited[r][c]={false};
    vector<vector<bool>> visited(r,vector<bool>(c,false));

    rq.push_back(sr);
    cq.push_back(sc);
    visited[sr][sc]=true;
    int row,column;
    while(rq.size()>0)
    {
        int n=rq.size();
        for(int i=0;i<n;i++)
        {
            row=rq.front();
            rq.erase(rq.begin());
            column=cq.front();
            cq.erase(cq.begin());
            if(grid[row][column]=='S')
            {
                reached_end=true;
                break;
            }

            explore(row,column,grid,visited);


            nodes_left_in_layer--;
            if(nodes_left_in_layer==0)
            {
                nodes_left_in_layer=nodes_in_next_layer;
                nodes_in_next_layer=0;
                move_count++;
            }
        }
        if(reached_end)
            break;
        explore_riders(grid);
        
        if(grid[1][0]=='R')
            break;
    }
    if(reached_end)
        return move_count;
    return -1;

}
int main()
{
    int r,c;
    cin>>r>>c;
    vector<vector<char>> grid(r,vector<char>(c));

    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>grid[i][j];
            if(grid[i][j]=='R')
            {
                ridersr.push_back(i);
                ridersc.push_back(j);
            }
        }
    }

    int result=dungeon(grid,r,c);
    if(result==-1)
        cout<<"NO"<<endl;
    else
    {
        cout<<"YES"<<endl;
        cout<<result<<endl;
    }
    return 0;
}