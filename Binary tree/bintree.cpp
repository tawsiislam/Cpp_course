#include "bintree.h"
#include <iostream>
using namespace std;


void insert(Node * & p, int key, double to_be_inserted){
    if(p==nullptr){
        p = new Node;
        p -> key = key;
        p -> data = to_be_inserted;
        p -> left = nullptr;
        p -> right = nullptr;
    }
    else{
        if(p -> key == key){    //Replace if key exists
            p -> data = to_be_inserted;
        }
        else{
            if(p -> key > key){
                insert(p -> left, key, to_be_inserted);
            }
            else{
                insert(p -> right, key, to_be_inserted);
            }
        }
    }
}

void remove(Node * & p, const int & key){
    
    Node* curr = p;
    Node* parent = p;
    
    while (curr != nullptr && curr->key != key){ //Finding the correct key
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    if(curr == nullptr){ //Key not found
        throw std::out_of_range("This node to be removed cannot be found");
    }
    
    if(curr -> left == nullptr && curr -> right == nullptr){ //If node has no child
        if(curr != p){
            if(parent ->left == curr){
                parent -> left = nullptr;
            }
            else{
                parent -> right = nullptr;
            }
            delete_tree(curr);
        }
        else{
            delete_tree(p);
        }   
    }
    else if(curr-> left && curr -> right){  //Node has left and right child
        Node * successor = curr -> right;
        while(successor -> left != nullptr){
            successor = successor -> left;
        }
        int tempData = successor -> data;
        int tempKey = successor -> key;
        remove(p, successor->key);
        curr -> data = tempData;
        curr -> key = tempKey;
    }
    else{   //Node has only one child
        Node* child = (curr -> left)? curr -> left: curr -> right;
        if(curr != p){
            if(parent -> left == curr){
                parent -> left = child;
            }
            else{
                parent -> right = child;
            }
            curr -> left = nullptr;
            curr -> right = nullptr;
            delete_tree(curr);
        }
        else{
            p = child;
            curr -> left = nullptr;
            curr -> right = nullptr;
            delete_tree(curr);  
        }
    }
}

const double & find(Node * p, const int & to_be_found){
    if(p != nullptr){
        if(p -> key == to_be_found){
            return p-> data;
        }
        else{
            return (p->key > to_be_found) ? find(p->left, to_be_found):find(p->right, to_be_found);
        }
    }
    else{
        throw std::out_of_range("This key cannot be found");
    }
}

double & edit(Node * p, const int & to_be_changed){
    if(p != nullptr){
        if(p-> key == to_be_changed){
            return p->data;
        }
        else{
            return (p->key > to_be_changed) ? edit(p->left, to_be_changed): edit(p->right, to_be_changed);
        }
    }
    else{
        throw std::out_of_range("This key to be edited cannot be found");
    }
}

void delete_tree(Node * & p){
    if(p==nullptr){
        delete p;
    }
    else{
        delete_tree(p->left);
        delete_tree(p->right);
        p -> left = nullptr;
        p -> right = nullptr;
        delete p;
        p = nullptr;
    }
}

unsigned int max_height(Node * p){
    if(p == nullptr){
        return 0;
    }
    else{
        int leftHeight = max_height(p->left);
        int rightHeight = max_height(p->right);
        return (leftHeight > rightHeight) ? leftHeight+1 : rightHeight+1;
    }
}

unsigned int min_height(Node * p){
    if(p == nullptr){
        return 0;
    }
    else{
        int leftHeight = min_height(p->left);
        int rightHeight = min_height(p->right);
        return (leftHeight < rightHeight) ? leftHeight+1 : rightHeight+1;
    }
}

unsigned int size(Node * p){
    if(p == nullptr){
        return 0;
    }
    else{
        int leftSize = size(p->left);
        int rightSize = size(p->right);
        return leftSize+rightSize+1;
    }
}

bool is_balanced(Node * p){
    if(p == nullptr){
        return true;
    }
    else{
        int leftHeight = max_height(p->left);
        int rightHeight = max_height(p->right);
        if(abs(leftHeight-rightHeight)<=1 && is_balanced(p->left) && is_balanced(p->right)){ //Left and right side can only differ by one height to be balanced
            return true;
        }
        else{
            return false;
        }
    }
}