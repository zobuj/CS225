/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <iostream>
 #include <algorithm>
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * r= t->right;
    Node *RL=r->left;
    t->right=RL;
    r->left=t;
    
    
    t->height=fmax(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t=r;
    t->height= fmax(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * l= t->left;
    Node * LR=l->right;

    l->right=t;
    t->left=LR;
    
    t->height=fmax(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t=l;
    t->height=fmax(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree==NULL){
        return;
    }
    int bf = heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right);
    if(bf==-2){//right heavy
        int rbf=heightOrNeg1(subtree->right->left)-heightOrNeg1(subtree->right->right);
        if(rbf==-1){
            rotateLeft(subtree);
        }
        else{
            rotateRightLeft(subtree);
        }
    }
    else if(bf==2){//left heavy
        int lbf=heightOrNeg1(subtree->left->left)-heightOrNeg1(subtree->left->right);
        if(lbf==1){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{   
    // your code here
    if(subtree==NULL){
        subtree=new Node(key,value);
    }
    else if(subtree->key==key){
        subtree->value=value;
    }
    else if(subtree->key>key){
        insert(subtree->left, key, value);
    }
    else if(subtree->key<key){
        insert(subtree->right, key, value);
    }
    
    rebalance(subtree);
    subtree->height= fmax(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
   if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            Node*temp=subtree;
            delete temp;
            subtree=NULL;
            return;
        } else if((subtree->left!=NULL&&subtree->right==NULL)||(subtree->right!=NULL&&subtree->left==NULL)){
            /* one-child remove */
            // your code here
            if(subtree->left!=NULL){
                Node*temp=subtree;
                Node*n=subtree->left;
                delete temp;
                subtree=n;
                n=NULL;
            }else if(subtree->right!=NULL){
                Node*temp=subtree;
                Node*n=subtree->right;
                delete temp;
                subtree=n;
                n=NULL;
            }
        } else if(subtree->right!=NULL&&subtree->left!=NULL){
            /* two-child remove */
            // your code here
            Node * pre=subtree->left;
        while(pre->right!=NULL){
            pre=pre->right;
        }
        int nkey=pre->key;
        remove(subtree,nkey);
        subtree->key=nkey;

        }
        // your code here
    }
    rebalance(subtree);
    subtree->height = fmax(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
    
}
