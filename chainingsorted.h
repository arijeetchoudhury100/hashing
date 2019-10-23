#ifndef CHAININGSORTED_H
#define CHAININGSORTED_H

#include<iostream>
#include<list>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;

int hashval(string key);
int hashval(int key);

template<typename Hashed>
class CSHashTable{
    private:
        int tablesize;
        list<Hashed> *table;
    public:
        CSHashTable(int x){
            tablesize = x;
            table = new list<Hashed>[tablesize];
        }
        int insert(Hashed x);
        int remove(Hashed x);
        int contains(Hashed x);
        void print();
        int hash(Hashed x);
};

template<typename Hashed>
int CSHashTable<Hashed> :: insert(Hashed x){
    int pos = hash(x);
    typename list<int> :: iterator itr = table[pos].begin();
    int probe = 1;
    //if( find(table[pos].begin(),table[pos].end(),x) != table[pos].end())
    //   return false;
    for(;itr != table[pos].end();itr++){
        probe++;
        if(*itr == x)
            return probe;
    }
    itr = table[pos].begin();
    while(x > *itr && itr != table[pos].end()){
        probe++;
        itr++;
    }
    table[pos].insert(itr,x);
    return probe;
}

template<typename Hashed>
int CSHashTable<Hashed> :: remove(Hashed x){
    int pos = hash(x);
    int probe = 1;
    //typename list<int> :: iterator itr = find(table[pos].begin(),table[pos].end(),x);
    //if(itr == table[pos].end())
    //   return false;
    typename list<int> :: iterator itr;
    for(itr = table[pos].begin();itr != table[pos].end();itr++){
        probe++;
        if(*itr == x)
            break;
    }
    if(itr == table[pos].end())
        return probe;
    table[pos].erase(itr);
    return probe;

}

template<typename Hashed>
int CSHashTable<Hashed> :: contains(Hashed x){
    int pos = hash(x);
    int probe = 1;
    //if( find(table[pos].begin(),table[pos].end(),x) != table[pos].end())
    //    return true;
    //return false;
    typename list<int> :: iterator itr;
    for(itr = table[pos].begin();itr != table[pos].end();itr++){
        probe++;
        if(*itr == x)
            break;
    }
    if(itr == table[pos].end())
        return probe;
    return probe;
}

template<typename Hashed>
int CSHashTable<Hashed> :: hash(Hashed x){
    float k = (sqrt(5)-1)/2;
    int val = hashval(x);
    float num = k*val;
    float frac = num-int(num);
    val = floor(tablesize*frac);
    return val;
}
template<typename Hashed>
void CSHashTable<Hashed> :: print(){
    for(int i=0;i<tablesize;i++){
        cout<<i;
        list<int> :: iterator itr;
        for(itr = table[i].begin();itr != table[i].end();itr++){
            cout<<"-->"<<*itr;
        }
        cout<<endl;
    }
}
#endif