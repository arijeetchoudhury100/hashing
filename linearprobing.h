#ifndef LINEARPROBING_H
#define LINEARPROBING_H
#include<vector>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;

int hashval(string key);
int hashval(int key);

template<typename Hashed>
class LHashTable{
    public:
        LHashTable(int size = 101){
            tableSize = size;
            arr.reserve(tableSize);
            makeEmpty();
        }
        int contains(Hashed x){
            //return isActive(findPos(x));
            int initialPos = hash(x);
            int curPos = initialPos;
            int probe = 1;
            while(arr[curPos].info != EMPTY && arr[curPos].element != x){
                curPos = curPos + 1;
                probe = probe + 1;
                if(curPos >= arr.capacity()){
                    curPos = curPos - arr.capacity();
                }
                if(curPos == initialPos)
                    return probe;
            }
            return probe;
        }
        int insert(Hashed x){
            int probe = 1;
            int initialPos = hash(x);
            int curPos = initialPos;
            while( arr[curPos].info != EMPTY && arr[curPos].info != DELETED && arr[curPos].element != x){
                curPos = curPos + 1;
                probe = probe + 1;
                if(curPos >= arr.capacity())
                    curPos = curPos - arr.capacity();
                if(curPos == initialPos)
                    return probe;
            }
            if(isActive(curPos))
                return probe;
            arr[curPos] = HashItem(x,ACTIVE);
            return probe;
        }
        int remove(Hashed x){
            int initialPos = hash(x);
            int curPos = initialPos;
            int probe = 1;
            while(arr[curPos].info != EMPTY && arr[curPos].element != x){
                probe = probe+1;
                curPos = curPos + 1;
                if(curPos >= arr.capacity()){
                    curPos = curPos - arr.capacity();
                }
                if(curPos == initialPos){
                    return probe;   //failed deletion
                }
            }
            //if(curPos == -1)
            //    return probe;   //false
            if(!isActive(curPos))
                return probe;   //false
            arr[curPos].info = DELETED;
            return probe;   //true
        }
        void makeEmpty(){
            for(int i=0;i<arr.capacity();i++){
                arr[i].info = EMPTY;
                arr[i].element = -1;
            }
        }
        void print(){
            for(int i=0;i<arr.capacity();i++)
                cout<<i<<": "<<arr[i].element<<" "<<arr[i].info<<endl;
        }
        enum entry {ACTIVE,EMPTY,DELETED};
    private:
        struct HashItem{
            Hashed element;
            entry info;
            HashItem(Hashed x, entry e = EMPTY){
                element = x;
                info = e;
            }
        };
        vector<HashItem> arr;
        int tableSize;
        bool isActive(int curPos){
            if(arr[curPos].info == ACTIVE)
                return true;
            return false;
        }
        /*int findPos(Hashed x){
            int initialPos = hash(x);
            int curPos = initialPos;
            while(arr[curPos].info != EMPTY && arr[curPos].element != x){
                curPos = curPos + 1;
                if(curPos >= arr.capacity()){
                    curPos = curPos - arr.capacity();
                }
                if(curPos == initialPos)
                    return -1;
            }
            return curPos;
        }*/
        int hash(Hashed x){
            float k = (sqrt(5)-1)/2;
            int val = hashval(x);
            float num = k*val;
            float frac = num-int(num);
            val = floor(tableSize*frac);
            return val;
        }
};
#endif