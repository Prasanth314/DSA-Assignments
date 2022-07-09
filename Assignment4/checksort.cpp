#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <algorithm>
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
    unsigned long long prev = 0;
    unsigned long long curr;
    ofstream myfile;
    fstream file("output.txt", ios::in);
    string csvElement;
    bool flag = false;
    int count=0,dis=0;
    while (getline(file, csvElement, ','))
    {
        count++;
        curr = stoll(csvElement);
        if (curr < prev)
        {
            flag = true;
            cout << "Unsorted At" << endl;
            cout << curr << endl;
            cout << prev << endl;
            cout<<"$$$$$$$$$$$$$$$"<<endl;
            dis++;
        }
        prev = curr;
    }
    if (flag == false)
    {
        cout << "Sorted" << endl;
    }
    cout<<"NO of elements:"<<count<<endl;
    cout<<"DIScrepencies :"<<dis<<endl;
    file.close();
    return 0;
}