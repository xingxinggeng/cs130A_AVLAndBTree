//header file for 2-5 tree

#ifndef BTREE_H
#define BTREE_H


#include <iostream>
#include <string>
#include <vector>
using namespace std;


class BTreeNode{
    //variables
	pair<string,int>* keys;
	int n;
	bool leaf;
	BTreeNode **C;
public:
    //methods
	BTreeNode(bool Leaf){
		keys = new pair<string,int>[4];
		C = new BTreeNode *[5];
		leaf = Leaf;
		n = 0;//changed
	}
	void insertNonFull(string x);//added
    void remove(string k);
  //  BTreeNode *search(string k);//----------------------unsure
    int findKey(string k);
	bool searchNode(string x);//changed
	void splitChild(int i, BTreeNode *y);//changed
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    pair<string,int> getPred(int idx);
    pair<string,int> getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    void rangeSearch(string a, string b);
    BTreeNode* searchNode2(string x);
    void sortNode(vector<std::string> vect);
    friend class BTree;
};


class BTree{
	public:
		BTree();
		~BTree();
		bool search(string  x);
        void insert(string  x);
   	  	void remove(string  x);
    	vector<std::string> sort();
    	void rangeSearch(string a, string b);
        void makeEmpty( BTreeNode* &t);
	private:
		BTreeNode *root;
};
#endif


