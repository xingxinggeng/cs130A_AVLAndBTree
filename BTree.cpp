//implementation of BTree


#include"BTree.h"

using namespace std;



BTree::BTree(){
	root = NULL;
}

BTree::~BTree(){

	makeEmpty(root);
}

void BTree::makeEmpty( BTreeNode* &t){
    while(t!=NULL){
        for(int i=0; i<= t->n; i++){
            makeEmpty((t->C)[i]);
        }
        delete [](t->C);
    }
}



/*
BTreeNode* search( string k){
    BTreeNode* n;
    if(root==NULL){
        n = NULL;
    }else{
        n = root->search(k);
    }
    return n;
}
*/

int BTreeNode::findKey(string k)
{
    int idx=0;
    while (idx<n && keys[idx].first < k)
        ++idx;
    return idx;
}


void BTreeNode::remove(string k){
    int idx = findKey(k);
    if(idx <n && keys[idx].first ==k){
        if(keys[idx].second>1){
            keys[idx].second--;
            return;
        } 
        if(leaf){
            removeFromLeaf(idx);
        }else{
            removeFromNonLeaf(idx);
        }
    }else{
        if(leaf){
            return;
        }

        bool flag;
        if(idx==n){
            flag=true;
        }else{
            flag=false;
        }

        if(C[idx]->n <2)
            fill(idx);

        if( flag && idx>n){
            C[idx-1]->remove(k);
        }else{
            C[idx]->remove(k);
        }
    }   
    return;
    }

void BTreeNode::removeFromLeaf(int idx){
    for(int i=idx+1; i<n; ++i){
        keys[i-1]=keys[i];
    }
    n--;
}

void BTreeNode::removeFromNonLeaf(int idx){
    pair<string,int> k = keys[idx];
    //if the child node of the predecessor has more than one keys
    if(C[idx]->n >=2){
        pair<string,int> pred=getPred(idx);
        keys[idx]=pred;
        C[idx]->remove(pred.first);
    }else if (C[idx+1]->n >=2){
        //if the next sibling has more than one keys 
        pair<string,int> succ = getSucc(idx);
        keys[idx]=succ;
        C[idx+1]->remove(succ.first);
    }else{
        merge(idx);
        C[idx]->remove(k.first);
    }
}

pair<string,int> BTreeNode::getPred(int idx){
    BTreeNode *find=C[idx];
    while(!find->leaf){
        find=find->C[find->n];
    }

    return find->keys[(find->n)-1];
}

pair<string,int> BTreeNode::getSucc(int idx){
    BTreeNode *find=C[idx+1];
    while(!find->leaf){
        find=find->C[0];
    }

    return find->keys[0];
}

void BTreeNode::fill(int idx){
    //if previous sibling has more than one key, borrow from it
    if(idx!=0 && (C[idx-1]->n) >=2){
        borrowFromPrev(idx);
    }else if(idx!=n && (C[idx+1]->n) >=2){
        //if the next sibling has more than one key, borrow from it
        borrowFromNext(idx);
    }else{
        if(idx!=n)
            merge(idx);
        else
            merge(idx-1);
    }
}

void BTreeNode::borrowFromPrev( int idx){
    BTreeNode *self=C[idx];
    BTreeNode *sibling=C[idx-1];

    for(int i=self->n-1;i>=0;--i){
        self->keys[i+1]= self->keys[i];
    }
    if(!self->leaf){
        for(int i=self->n;i>=0; --i){
            self->C[i+1]=self->C[i];
        }
    }

    self->keys[0]=keys[idx-1];
    
    if(!self->leaf){
        self->C[0] = sibling -> C[sibling->n];
    }

    keys[idx-1] = sibling->keys[sibling->n-1];

    (self->n)+=1;
    (sibling->n)-=1;
    return;
}

/*void BTreeNode::borrowFromNext(int idx){
    BTreeNode* child=C[idx];
    BTreeNode* sibling=C[idx+1];

    child->keys[(child->n)]=keys[idx];

    if(!(child->leaf)){
        child->C[(child->n)+1] = sibling->C[0];
    }

    keys[idx] = sibling->keys[0];

    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}*/

void BTreeNode::merge(int idx){
    BTreeNode*child = C[idx];
    BTreeNode*sibling=C[idx];
    //move down the node of parent
    child->keys[1]=keys[idx];
    //move over the sibling
    for(int i=0; i<sibling->n;i++){
        child->keys[i+2]=sibling->keys[i];
    }

    if(!child->leaf){
        for(int i=0;i<=sibling->n;i++){
            child->C[i+2]=sibling->C[i];
        }
    }

    for(int i=idx+1;i<n;++i){
        keys[i-1]=keys[i];
    }
    for(int i=idx+2;i<=n;i++){
        C[i-1]=C[i];
    }

    child->n += sibling->n+1;
    n--;

    delete(sibling);
}



void BTree::remove(string k){
    if(!root){
        return;
    }
    root->remove(k);
    if(root->n==0){
        BTreeNode* tmp =root;
        if(root->leaf){
            root=NULL;
        }else{
            root = root->C[0];
        }
        delete tmp;
    }
}


bool BTree::search(string  x){
	if(root == NULL){
		return false;
	}
	else{
		return root->searchNode(x);
	}
}


bool BTreeNode::searchNode(string x){
	int i = 0;
    if(this!=NULL){
	while( i < n && i<=3 && x > keys[i].first){
		i++;
	}
	if(i < n && keys[i].first==x){
		return true;
	}else{
	//not found and this is the leave then we done
	    if(leaf){
		    return false;
	    }
        bool b=true;
        for(int j=0; j<=n; j++)
            b=(b && C[i]->searchNode(x));
	    return b;
    }
    }
}

BTreeNode* BTreeNode::searchNode2(string x){
    int i = 0;
    while( i < n && x > keys[i].first){
		i++;
	}
	if(i < n && keys[i].first==x){
		return this;
	}else{
        if(leaf){
            return NULL;
        }
        BTreeNode* tmp=NULL;
        for(int j=0;j<=n;j++)
            tmp=C[i]->searchNode2(x);
        return tmp;
    }
}

void BTree::rangeSearch(string a, string b){
    if(root){
        if(root->leaf){
            for (int i = 0; i < root->n; i++){
                if(root->keys[i].first >= a && root->keys[i].first<= b){
                    cout  << root->keys[i].first<<endl;
                }
            }
        }
        else{//root is not leaf
            root->rangeSearch(a,b);
        }
    }
}

void BTreeNode::rangeSearch(string a, string b){
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false){
            for(int j = 0; j< n;j++){
                if(keys[j].first >= a && keys[j].first<= b)
                    cout  << keys[i].first<<endl;
            }
        }
        C[i]->rangeSearch(a,b);
     }
     if(leaf ==false){
         C[i]->rangeSearch(a,b);
    }
}



void BTreeNode::sortNode(vector<std::string> vect){
    int i;
    for( i = 0; i< n;i++){
        if(leaf){
            for(int j =0; j<n;j++){
                vect.push_back(keys[j].first);
            }
            return;
        }
        if (leaf == false){
            for(int k = 0; k<n;k++){
                C[k]->sortNode(vect);
            }
            vect.push_back(keys[i].first);
        }
    }
    if(leaf == false){
        for(int k = 0; k<n;k++){
            C[i]->sortNode(vect);
        }
    }
}


vector<std::string> BTree:: sort(){
    vector<std::string> v;
    if( root != NULL ){
        root->sortNode(v);
    }
    return v;
}


void BTree::insert(string  x){
	if(root == NULL){
		root = new BTreeNode(true);
		root->keys[0].first = x;
		root->keys[0].second = 1;
		root->n = 1;
	}
	else if(root->searchNode(x)==true){
        //x is a in the tree already
        BTreeNode* tmp = root->searchNode2(x);
        int idx=tmp->findKey(x);
        if(root->keys[idx].first==x){
            root->keys[idx].second++;
        }
    }else{


		//meet a full node
		if(root->n == 4){
			BTreeNode *s = new BTreeNode(false);
			s->C[0] =  root;
			s->splitChild(0,root);


			int i  = 0;
			if(s->keys[0].first < x){
				i++;
			}
			s->C[i]->insertNonFull(x);

			root = s;
		}
		else{//root is not full
			root->insertNonFull(x);
		}
	}
}


void BTreeNode::insertNonFull(string x){
	int i  = n-1;

	if(leaf==true){
		while( i >= 0 && keys[i].first > x){
            keys[i+1]=keys[i];
			i--;
		}
        keys[i+1].first=x;
        n=n+1;
        /*
		if( idx >= 0 && keys[idx].first == x ){
			keys[idx].second += 1;
			return;
		}
		else{
			while( i >= 0 && keys[i].first > x){
				 keys[i+1].first = keys[i].first;
				 keys[i+1].second = keys[i].second;
				 i--;
			}
			keys[i+1].first = x;
			keys[i+1].second  = 1;
			n = n+1;
		}
        */
	}
	else{//not a leaf
		while( i >=0 && keys[i].first > x){
			i--;
		}
        /*
		if( idx >= 0 && keys[idx].first == x ){
			keys[idx].second += 1;
			return;
		}
		else{
			while(i >= 0 && keys[i].first > x){
				i--;
			}
            */
		if(C[i+1]->n == 4){
				splitChild(i+1,C[i+1]);
				if(keys[i+1].first < x){
					i++;
				}
		}
			C[i+1]->insertNonFull(x);
		}
}



void BTreeNode::splitChild(int i, BTreeNode *y){
	BTreeNode* z = new BTreeNode(y->leaf);
	z->n = 2;

	for(int j = 0; j < 2; j++){
		z->keys[j] = y->keys[j+2];
	}
	if(y->leaf==false){
		for(int j = 0; j < 2; j++){
			z->C[i] = y->C[j+3];
		}
	}

	y->n = 2;
///////////////////////
	for(int j = n; j>= i+1; j--){
		C[j+1] = C[j];
	}
	C[i+1] = z;

	for (int j = n; j >= i+1; j--){
		keys[j] = keys[j-1];
	}

	keys[i]= y->keys[1];
 
    y->n = 1;
	n=n=1;
}


void BTreeNode::borrowFromNext(int idx){
    BTreeNode* child=C[idx];
    BTreeNode* sibling=C[idx+1];

    child->keys[(child->n)]=keys[idx];

    if(!(child->leaf)){
        child->C[(child->n)+1] = sibling->C[0];
    }   

    keys[idx] = sibling->keys[0];

    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    if (!sibling->leaf)
    {   
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }   

    child->n += 1;
    sibling->n -= 1;

    return;
}















