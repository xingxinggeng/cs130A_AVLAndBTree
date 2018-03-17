// header file for AVL tree
// 03/05/2018
//Samuel Fu, Xingxing Geng


#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct avl_node{
	avl_node *left;
        avl_node *right;
        int counter;
        int height;
        string word;

        avl_node(string element,avl_node *lt, avl_node *rt){
		word  = element;
                counter = 1;
                height = 0;
                left = lt;
                right = rt;
        }
};


class AVL{
		public:
			AVL();
			~AVL();
	
			bool search(string  x);
    	   		void insert(string  x);
    	  		void remove(string  x);
    	    		vector<std::string> sort();
    	    		void rangeSearch(string a, string b);
			
			int height(avl_node* t);
				
			//rotate functions
			void singleRotateLeftChild(avl_node *& t);
			void singleRotateRightChild(avl_node *& t);
			void doubleRotateLeftChild(avl_node *& t);
			void doubleRotateRightChild(avl_node *& t);
			

		private:  
			avl_node *root;

			//private helper function
			void makeEmpty(avl_node* t);
			bool search( avl_node* t, string x);
			void insert(avl_node*& t, string x);
			void remove(avl_node* t, string x);
			void sort(avl_node* t,vector<std::string>& vect);
			void rangeSearch(avl_node* t,string lt, string rt);


};

#endif

