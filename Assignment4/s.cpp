// C++ program to find maximum XOR in
// a stream of integers
#include<bits/stdc++.h>
using namespace std;

struct TrieNode
{
	TrieNode* children[2];
	bool isLeaf;
};

// This checks if the ith position in
// binary of N is a 1 or a 0
bool check(long long N, int i)
{
	return (bool)(N & (1LLU<<i));
}

// Create a new Trie node
TrieNode* newNode()
{
	TrieNode* temp = new TrieNode;
	temp->isLeaf = false;
	temp->children[0] = NULL;
	temp->children[1] = NULL;
	return temp;
}

// Inserts x into the Trie
void insert(TrieNode* root, long long x)
{
	TrieNode* Crawler = root;

	// padding upto 32 bits
    cout<<x<<endl;

	for (long long i = 63; i >= 0; i--)
	{
		int f = check(x, i);
		if (! Crawler->children[f])
			Crawler->children[f] = newNode();
        if(f)
            cout<<x<<" "<<i<<endl;
		Crawler = Crawler->children[f];
	}
	Crawler->isLeaf = true;
}

// Finds maximum XOR of x with stream of
// elements so far.
int query2(TrieNode *root, int x)
{
	TrieNode* Crawler = root;

	// Do XOR from root to a leaf path
	int ans = 0;
	for (int i = 42; i >= 0; i--)
	{
		// Find i-th bit in x
		int f = check(x, i);

		// Move to the child whose XOR with f
		// is 1.
		if ((Crawler->children[f ^ 1]))
		{
			ans = ans + (1 << i); // update answer
			Crawler = Crawler->children[f ^ 1];
		}

		// If child with XOR 1 doesn't exist
		else
			Crawler = Crawler->children[f];
	}

	return ans;
}

// Process x (Add x to the stream)
void query1(TrieNode *root, int x)
{
	insert(root, x);
}

// Driver code
int main()
{
	TrieNode* root = newNode();
	query1(root, 1);
	query1(root, 2);
	// cout << query2(root, 10) << endl;
	// query1(root, 9);
	// query1(root, 5);
	// cout << query2(root, 6) << endl;
	return 0;
}
