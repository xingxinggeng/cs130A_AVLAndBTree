#include "AVL.h"
#include "BTree.h"
//#include "hashTable.h"
#include <fstream>
#include <regex>
#include <experimental/filesystem>
#include <limits>
#include <sstream>

using namespace std;
namespace fs = std::experimental::filesystem;
int getTest() {
    cout << "Choice of tests:\n"
        << "  1. search\n"
        << "  2. insert\n"
        << "  3. delete\n"
        << "  4. sort\n"
        << "  5. rangeSearch\n";
    do {
        int choice;
        cout << "Enter choice:\n";
        cin >> choice;
        if (choice >=1 && choice < 6)
        	return choice;
        cout << "0, 1, 2, 3, 4 or 5 only!\n";
    } while (true);
}


void to_lower(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}


std::string stop[] = {"i","me","my","myself","we","our","ours","ourselves","you","your","yours","yourself","yourselves","he","him","his","himself","she","her","hers","herself","it","its","itself","they","them","their","theirs","themselves","what","which","who","whom","this","that","these","those","am","is","are","was","were","be","been","being","have","has","had","having","do","does","did","doing","a","an","the","and","but","if","or","because","as","until","while","of","at","by","for","with","about","against","between","into","through","during","before","after","above","below","to","from","up","down","in","out","on","off","over","under","again","further","then","once","here","there","when","where","why","how","all","any","both","each","few","more","most","other","some","such","no","nor","not","only","own","same","so","than","too","very","s","t","can","will","just","don","should","now"};


bool isStopword (string word){
    for(int i = 0; i < 127;i++){
        if(word == stop[i]){
            return true;
        }else{
            return false;
        }
    }
}


int main(){
    string path("hotels-small");
    vector <string> words;
    regex rgx("[a-z]+[a-z_'-]*");
    
	/* all words ignore stopwords and non-alphabetical text*/
	for (auto&p : fs::recursive_directory_iterator(path)){
        if(fs::is_regular_file(p)){
            ifstream infile;
            infile.open(p.path());
            string token;
            while(infile>>token){
                to_lower(token);
                for(sregex_iterator it(token.begin(), token.end(), rgx), it_end; it != it_end; ++it){
                    string word = it->str();
                    if(!isStopword(word)){
                        words.push_back(word);
                    }
                }
            }
        }
    }
	AVL avl;
	BTree BTree;
//	HashTable ht((unsigned  long)(1.5*words.size()));
	for(long i = 0; i< words.size();i++){
			avl.insert(words[i]);
			BTree.insert(words[i]);
	}
/*	for (auto& i : words)
		ht.insert(i);*/
    	while(true){
    	int testnum = getTest();


/* test 1 = search */
    	if(testnum == 1){
			cout<<"Enter a word to be searched: "<<endl;
			std::string w;
			cin >> w;

			//search the word in AVL tree
			clock_t t1;
            t1 = clock();
			bool result_avl = avl.search(w);
			t1 = clock() - t1;
			double timeSpent_avl = ((double)t1)/ CLOCKS_PER_SEC;

			//search the word in hash table
		/*	clock_t t2;
            		t2 = clock();
			bool result_ht = ht.search(w);//do research in ht
    	    		t2 = clock() - t2;
			double timeSpent_ht = ((double)t2) / CLOCKS_PER_SEC;
		*/

			clock_t t2;
			t2 = clock(); 
			bool result_BTree = BTree.search(w);//do search in BTree
			t2 = clock() - t2;
			double timeSpent_BTree = ((double)t2) / CLOCKS_PER_SEC;

			if( result_avl ){
				cout<<"true"<<endl;
			}
			else{
				cout<<"false"<<endl;
			}
			cout<<"AVL: "<<timeSpent_avl<<endl;
    		//	cout<<"Hash: "<<timeSpent_ht<<endl;
			cout<<"BTree: "<<timeSpent_BTree<<endl;
      	}

/* test2  = insert */
	if(testnum == 2){
            cout<<"Enter a word to be inserted: "<<endl;
            std::string w;
            cin >> w;
            
            clock_t t3 = clock();
            avl.insert(w);
            t3 = clock() - t3;
            double timeSpent_avl = ((double)t3) / CLOCKS_PER_SEC;
          /*
            clock_t t4 = clock();
            ht.insert(w);
            t4  = clock() -t4;
            double timeSpent_ht = ((double)t4) / CLOCKS_PER_SEC;
*/
	    clock_t t4 = clock();
	    BTree.insert(w);
	    t4  = clock() -t4;
	    double timeSpent_BTree = ((double)t4) / CLOCKS_PER_SEC;

            cout<<"AVL: "<<timeSpent_avl<<endl;
           // cout<<"Hash: "<<timeSpent_ht<<endl;
	    cout<<"BTree: "<<timeSpent_BTree<<endl;
    }


/* test3 = remove */
	if(testnum == 3){
            cout<<"Enter a word to be removed: "<<endl;
            string w;
            cin >> w;

            clock_t t5 = clock();
            avl.remove(w);
            t5  = clock()-t5;
            double timeSpent_avl = ((double)t5) / CLOCKS_PER_SEC;

            clock_t t6 = clock();
            BTree.remove(w);
            t6  = clock() -t6;
            double timeSpent_BTree =((double)t6) / CLOCKS_PER_SEC;
            cout<<"AVL: "<<timeSpent_avl<<endl;    
            cout<<"BTree: "<<timeSpent_BTree<<endl;
  
  }

 
/* test4 = sort() */
	if(testnum == 4){
		ofstream outfile("sortResult.txt");

		//sort in AVL tree
                clock_t t7 = clock();
                const vector<string> & avl_sorted = avl.sort();
                t7 = clock()-t7;
                double timeSpent_avl = ((double)t7) / CLOCKS_PER_SEC;
                            
		for( auto & word : avl_sorted){
                     outfile<< word << "\n";
                }
           
   
		// sort in hash table
		clock_t t8 = clock();
          	const std::vector<string> &BTree_sorted = BTree.sort(); 
        	t8 = clock()-t8;
                double timeSpent_BTree = ((double)t8) / CLOCKS_PER_SEC;

                /*/ sort in hash table
         clock_t t8 = clock();
             const std::vector<string> &BTree_sorted = BTree.sort();
             t8 = clock()-t8;
double timeSpent_BTree = ((double)t8) / CLOCKS_PER_SEC;
*/              for(auto &word : avl_sorted)
        	    {
         	         outfile << "\n" << word;
        	    }


	 	outfile.close();
                cout<<"AVL: "<<timeSpent_avl<<endl;
                cout<<"BTree: "<<timeSpent_BTree<<endl;
}


/* test5  = rangeSearch */
	if(testnum == 5){
            cout<<"Enter two words to rangeSearch: "<<endl;
            std::string x,y;
            cin >> x >> y;

            clock_t t9 = clock();
            avl.rangeSearch(x,y);
            t9 = clock()- t9;
            double timeSpent_avl = ((double)t9) / CLOCKS_PER_SEC;
	    cout<<'\n';
            clock_t t10 = clock();
            BTree.rangeSearch(x, y);
	    t10 = clock()- t10;
            double timeSpent_ht = ((double)t10) / CLOCKS_PER_SEC;
            
	    cout<<"AVL: "<<timeSpent_avl<<endl;
            cout<<"BTree: "<<timeSpent_ht<<endl;
    }
}

	return 0;
}







