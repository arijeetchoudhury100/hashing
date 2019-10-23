#include "bst.h"
#include "linearprobing.h"
#include "chaining.h"
#include "chainingsorted.h"
#include<fstream>
using namespace std;

int hashval(string key){
    int val=0;
    for(int i=0;i<key.length();i++){
        val += key[i];
    }
    return val;
}
int hashval(int key){
    return key;
}

int main(){
    BinarySearchTree<int> b;
    CHashTable<int> c(100);
    CSHashTable<int> cs(100);
    LHashTable<int> l(100);

    ifstream file("input.txt");
    int bst_probei[100]={0},chash_probei[100]={0},cshash_probei[100]={0},lhash_probei[100]={0},k=0;  
    float avg_bst_probei,avg_chash_probei,avg_cshash_probei,avg_lhash_probei;
    
    //get tokens from input file
    string word;
    while(file >> word){
        for(int i=0;i<word.length();i++)
            if(ispunct(word[i]))
                word.erase(word.find_first_of(word[i]));
        if(word.length()<10){
            int n = 10-word.length();
            word.append(n,'*');
        }
        if(word.length()>10){
            word = word.substr(0,10);
        }
        int val = hashval(word);
        bst_probei[k] = b.insert(val);
        chash_probei[k] = c.insert(val);
        cshash_probei[k] = cs.insert(val);
        lhash_probei[k] = l.insert(val);
        k++;
    }
    for(int i=0;i<58;i++){
        avg_bst_probei += bst_probei[i];
        avg_chash_probei += chash_probei[i];
        avg_lhash_probei += lhash_probei[i];
        avg_cshash_probei += cshash_probei[i];
    }
    avg_bst_probei /= k;
    avg_chash_probei /= k;
    avg_cshash_probei /= k;
    avg_lhash_probei /= k;

    cout<<"average probes for hashing with chaining(unsorted lists): "<<avg_chash_probei<<endl;
    cout<<"average probes for hashing with chaining(sorted lists): "<<avg_cshash_probei<<endl;
    cout<<"average probes for hashing with linear probing: "<<avg_lhash_probei<<endl;
    cout<<"average probes for binary search tree: "<<avg_bst_probei<<endl;

    return 0;
}