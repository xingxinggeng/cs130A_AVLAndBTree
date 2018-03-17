//implementation of AVL tree
//03/05/2018
//Samuel Fu, Xingxing Geng


#include"AVL.h"

using namespace std;

	AVL::AVL(){
			root = NULL;
	}

	AVL::~AVL(){
			makeEmpty(root);
	}

	void AVL::makeEmpty(avl_node* t){
			if( !t ){
					makeEmpty(t->left);
					makeEmpty(t->right);
					 delete t;
			}
	}


//search method

	bool AVL::search(string x){
			return search(root,x);
	}

	bool AVL::search( avl_node* t, string x){
			if( t == NULL){
					return false;
			}
			else if( t->word == x){
					return true;
			}
			else if( x < t->word){
					return search( t->left,x);
			}
			else if(x > t->word){
					return search( t->right, x);
			}
	}

// helper method and rotate methods
	
	int AVL::height(avl_node* t){
		if(t == NULL){
			return -1;
		}
		else{
			return t->height;
		}
	}
//rotate methods

	void AVL::singleRotateLeftChild(avl_node *& t){
		avl_node* node = t->left;
		t->left = node->right;
		node->right = t;
		t->height = std::max(height(t->left),height(t->right)) + 1;
		node->height = std::max(height(node->left), t->height) + 1;
		t = node;
	}
        void AVL::singleRotateRightChild(avl_node *& t){
		avl_node* node = t->right;
		t->right = node->left;
		node->left = t;
		t->height = std::max(height(t->left),height(t->right)) + 1;
		node->height = std::max(height(node->right),t->height) + 1;
		t  = node;
	}
        void AVL::doubleRotateLeftChild(avl_node *& t){
		singleRotateRightChild(t->left);
		singleRotateLeftChild(t);
	}
        void AVL::doubleRotateRightChild(avl_node *& t){
		singleRotateLeftChild(t->right);
		singleRotateRightChild(t);
	}


//insert method

	void AVL::insert(string x){
		insert(root,x);
	}

	void AVL::insert(avl_node *& t, string x){
		if(t == NULL){
			t = new avl_node(x, NULL, NULL);
		}
		else if( t->word == x){
			t->counter += 1;
		}
		else if ( x < t->word ){
			insert(t->left, x);
			if((height(t->left) - height(t->right)) == 2){
				if( x < t->left->word){
					singleRotateLeftChild(t);
				}
				else{
					doubleRotateLeftChild(t);
				}
			}
		}
		else if( x > t->word){
			insert(t->right, x);
			if((height(t->right) - height(t->left)) == 2){
			       if( x > t->right->word){
					singleRotateRightChild(t);
			       }
			       else{
				       doubleRotateRightChild(t);
			       }
			}
		}
		t->height  = std::max(height(t->left), height(t->right)) + 1;
	}


//delete method

	void AVL::remove(string  x){
		remove(root, x);
	}

	void AVL::remove(avl_node* t, string x){
		if( t == NULL ){
			return;
		}
		else{
			if( x < t->word ){
				return remove( t->left, x);
			}
			else if( x > t->word){
				return remove( t->right, x);
			}
			else if( x == t->word){
				t->counter -= 1;
				if(t->counter == 0){
					if( (!t->left) && (!t->right) ){
						avl_node *findMin;
						findMin = t->right;
						while(findMin->left){
							findMin = findMin->left;
						}
						t->word  = findMin->word;
						t->counter = findMin->counter;
						findMin->counter = 1;
						return remove(t->right, findMin->word);
					}
					else if( (t->left == NULL) || (t->right == NULL)){// t has one child or no child
						avl_node * oldNode = t;
						t = (t->left != NULL) ? t->left : t->right;
						delete oldNode;
					}
				}
			}
		}
		if( t == NULL){
			return;
		}
		t->height = std::max(height(t->left),height(t->right)) + 1;
		if((height(t->left) - height(t->right)) == 2){
			if( (height(t->left->left) - height(t->left->right)) > 0){
				singleRotateLeftChild(t);
			}
			else{
				doubleRotateLeftChild(t);
			}
		}
		if( (height(t->right) - height(t->left)) == 2 ){
			if( (height(t->right->right) - height(t->right->left)) > 0){
				singleRotateRightChild(t);
			}
			else{
				doubleRotateRightChild(t);
			}
		}
	}
						



//sort method


	vector<std::string> AVL::sort(){
		vector<std::string> v;
		sort(root,v);
		return v;
	}

	void AVL::sort(avl_node* t,vector<std::string>& vect){
		if( t == NULL){
			return;
		}
		else{
			sort(t->left, vect);
			vect.push_back(t->word);
			sort(t->right, vect);
		}
	}

//rangeSearch method

	void AVL::rangeSearch(string a, string b){
		string lt;
		string rt;
		if( a > b){
			lt  = b;
			rt = a;
		}
		else{
			lt = a;
			rt = b;
		}
		rangeSearch(root,lt,rt);
	}

	void AVL::rangeSearch(avl_node* t,string lt, string rt){
		if( t == NULL){
			return;
		}
		else{
			rangeSearch(t->left,lt,rt);
			if( lt <= t->word && rt >= t->word){
				cout<<t->word<<'\n';
			}
			rangeSearch(t->right,lt,rt);
		}
	}

