#ifndef BST_H
#define BST_H
#include<iostream>
using namespace std;

int probe;
template<typename T>
class BinarySearchTree{

    public:
        BinarySearchTree(){
            root = NULL;
        }
        ~BinarySearchTree(){
            makeEmpty();
        }
        bool isEmpty(){
            if(root == NULL)
                return true;
            else 
                return false;
        }
        int contains(T x){
            //return contains(x,root);
            probe = 1;
            return contains(x,root,probe);
        }
        int insert(T x){
            probe = 1;
            return insert(x,root,probe);
        }
        int remove(T x){
            probe = 1;
            return remove(x,root,probe);
        }
        void print(){
            if(isEmpty())
                cout<<"Empty tree";
            else
                print(root);
            cout<<endl;
        }
        void makeEmpty(){
            makeEmpty(root);
        }
        
    private:
        struct node{
            T element;
            node *left;
            node *right;

            node(T x,node* l,node* r){
                element = x;
                left = l;
                right = r;
            }
        };
        node *root;
        int insert(T x,node* & t,int probe){  //passed by reference so that root is changed
            if(t == NULL){
                t = new node(x,NULL,NULL);
                return probe;
            }
            else if(x<t->element){
                probe = probe + 1;
                insert(x,t->left,probe);
            }
                
            else if(x>t->element){
                probe = probe + 1;
                insert(x,t->right,probe);
            }
            else
                probe = probe + 1;//duplicate element
        }
        int remove(T x,node* & t,int probe){
            if(t == NULL)
                return probe;
            if(x < t->element){
                probe = probe + 1;
                remove(x,t->left,probe);
            }
            else if(x > t->element){
                probe = probe + 1;
                remove(x,t->right,probe);
            }
            else if(t->left != NULL && t->right != NULL){   //two child nodes
                t->element = findMin(t->right)->element;
                remove(t->element,t->right,probe);
            }
            else{   //one or zero child
                if(t->left == NULL)
                    t = t->right;
                else
                    t = t->left;
            }
        }
        node* findMin(node* t){
            if(t == NULL)
                return NULL;
            else if(t->left == NULL)
                return t;
            return findMin(t->left);
        }
        node* findMax(node* t){
            if(t == NULL)
                return NULL;
            else if(t->right == NULL)
                return t;
            return findMin(t->right);
        }
        int contains(T x,node* t,int probe){
            if(t == NULL){
                //return false;
                return probe;
            }
            else if(x < t->element){
                probe = probe + 1;
                return contains(x,t->left,probe);
            }
            else if(x > t->element){
                probe = probe + 1;
                return contains(x,t->right,probe);
            }   
            else{
                //return true;
                return probe;
            }    
        }
        void makeEmpty(node* & t){
            if(t!=NULL){
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
            t=NULL;
        }
        void print(node *t){
            if(t){
                print(t->left);
                cout<<t->element<<" ";
                print(t->right);
            }
        }
};
#endif