#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> filenames;
vector<ifstream*> opened_files;
class MinHeapNode
{
    public:
    long long elem;
    ifstream *ifs;
    MinHeapNode(long long v,ifstream *ifst)
    {
        elem=v;
        ifs=ifst;
        opened_files.push_back(ifs);
    }
    
};
class MinHeap
{
    public:
    vector<MinHeapNode*> A;
    MinHeap()
    {

    }
    MinHeap(vector<MinHeapNode*> v)
    {
        A=v;
        heapify();
    }
    int parent(int i)
    {
        int x=(i-1)/2;
        return x;
    }
    int right_child(int i)
    {
        int x=2*i+2;
        return x;
    }
    int left_child(int i)
    {
        int x=2*i+1;
        return x;
    }
    int getSize()
    {
        return A.size();
    }
    void heapify_up(int i)
    {
        while(1)
        {
            int p=parent(i);
            if(p>=0 && A[p]->elem  > A[i]->elem)
            {
                swap(A[p],A[i]);
            }
            else
            {
                break;
            }
            i=p;
        }
    }
    void heapify_down(int i)
    {
        while(1)
        {
            int l=left_child(i);
            int r=right_child(i);
            int small=i;
            if(l<A.size() && A[l]->elem < A[i]->elem)
            {
                small=l;
            }
            if(r<A.size() && A[r]->elem < A[small]->elem)
            {
                small=r;
            }
            if(small==i)
                break;
            swap(A[i],A[small]);
            i=small;
        }
        
    }
    void heapify()
    {
        int n=A.size();
        for(int i=n/2;i>=0;i--)
        {
            heapify_down(i);
        }
    }
    void insertandheapify(MinHeapNode *n)
    {
        // MinHeapNode *n=new MinHeapNode(elem,ifst);
        A.push_back(n);
        int x=A.size()-1;
        heapify_up(x);
    }
    MinHeapNode* removeMin()
    {
        int x=A.size()-1;
        swap(A[0],A[x]);
        MinHeapNode *n=A.back();
        A.pop_back();
        heapify_down(0);
        return n;
    }
    void printheap()
    {
        cout<<"##############"<<endl;
        for(MinHeapNode *n:A)
        {
            cout<<n->elem<<" ";
        }
        cout<<endl;
        cout<<"###############"<<endl;
    }
};
void KWaymerge(string output)
{
    string text;
    vector<MinHeapNode*> v;
    ofstream ofs(output);
    ostream_iterator<long long> ositerator(ofs,",");
    try
    {
        /* code */    
    
        for(int i=0;i<filenames.size();i++)
        {
            ifstream *ifs=new ifstream(filenames[i]);
            opened_files.push_back(ifs);
            if(getline(*ifs,text,','))
            {
                MinHeapNode *n=new MinHeapNode(stoll(text),ifs);
                v.push_back(n);
            }
        }
        MinHeap heap(v);

        // heap.printheap();
        // Similar to Heap sort
        while (heap.getSize())
        {
            MinHeapNode *n=heap.removeMin();
            ofs<<n->elem;
            
            if(getline(*(n->ifs),text,','))
            {
                // cout<<"Removed "<<(n->elem)<<endl;
                n->elem=stoll(text);
                heap.insertandheapify(n);
                // heap.printheap();
            }
            else
            {
                n->ifs->close();
                free(n);
            }
            if(heap.getSize()!=0)
            {
                ofs<<',';
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        
    }


    for(int i=0;i<opened_files.size();i++)
    {
        if(opened_files[i]->is_open())
            opened_files[i]->close();
    }
    for(int i=0;i<filenames.size();i++)
    {
        remove(filenames[i].c_str());
    }
    // long pos=ofs.tellp();
    // ofs.seekp(pos-1);
    ofs.close();
    
}
void createchunks(string input_file,int chunksize)
{
    ifstream ifs(input_file);
    string text;
    ofstream ofs("temp1.txt");
    filenames.push_back("temp1.txt");
    ostream_iterator<long long> ositerator(ofs,",");
    int count=0,i=1;
    vector<long long> v;
    while(getline(ifs,text,','))
    {
        count++;
        // cout<<text<<endl;
        v.push_back(stoll(text));
        if(count>=chunksize)
        {
            i++;
            count=0;
            sort(v.begin(),v.end());
            copy(v.begin(),v.end(),ositerator);
            v.clear();
            ofs.close();
            string file_name="temp"+to_string(i)+".txt";
            ofs.open(file_name);
            filenames.push_back(file_name);
        }
    }
    if(v.size()>0)
    {
        sort(v.begin(),v.end());
        copy(v.begin(),v.end(),ositerator);
        v.clear();
    }
    ofs.close();
}
int main(int argc,char *argv[])
{
    string input(argv[1]);
    string output(argv[2]);
    // cout<<input<<endl;
    int chunksize=100;
    createchunks(input,chunksize);
    KWaymerge(output);
}