/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <unordered_map>
#include <algorithm>
template <class K, class V>
V BST<K, V>::find(const K& key)
{
    return find(root,key)->value;
    // your code here
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if(subtree==NULL||subtree->key==key){
        return subtree;
    }
    if(subtree->key>key){
        return find(subtree->left,key);
    }
        return find(subtree->right,key);
    // Your code here
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
    // your code here
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{   
    if(find(subtree,key)==NULL){
        find(subtree,key)=new Node(key,value);
    }
    // your code here
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    Node*&temp=first;
    first=second;
    second =temp;
    // your code here
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root,key);
    // your code here
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    if(find(subtree,key)->left==NULL&&find(subtree,key)->right==NULL){
        Node*n=find(subtree,key);
        find(subtree,key)=NULL;
        delete n;
    }
    else if((find(subtree,key)->left!=NULL&&find(subtree,key)->right==NULL)||(find(subtree,key)->right!=NULL&&find(subtree,key)->left==NULL)){
        if(find(subtree,key)->left!=NULL){
            Node*n=find(subtree,key);
            find(subtree,key)=find(subtree,key)->left;
            delete n;
        }else if(find(subtree,key)->right!=NULL){
            Node*n=find(subtree,key);
            find(subtree,key)=find(subtree,key)->right;
            delete n;
        }
    }
    else if(find(subtree,key)->right!=NULL&&find(subtree,key)->left!=NULL){
        Node * pre=find(subtree,key)->left;
        while(pre->right!=NULL){
            pre=pre->right;
        }
        int nkey=pre->key;
        remove(subtree,nkey);
        find(subtree,key)->key=nkey;
    }
    
    // your code here
}


template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K,V> b= BST<K,V>();
    int counter = 0;
    for(typename std::vector<std::pair<K, V>>::iterator it=inList.begin();it!=inList.end();++it){
        b.insert(inList[counter].first,inList[counter].second);
        counter++;
    }
    return b;
    // your code here
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::unordered_map<int,int>map;
    std::vector<int> result;
    std::sort(inList.begin(),inList.end());
    int maxHeight=-1;
    do{
        int value = listBuild(inList).height();
        if(value>maxHeight){
            maxHeight=value;
        }
        map[value]++;

    }while ( std::next_permutation(inList.begin(),inList.end()));
    for(int i  = 0;i<maxHeight;i++){
        if(!map.count(i)){
            map[i]=0;
        }
    }
    for(auto x:map){
        //std::cout<<"First: "<<x.first<<std::endl;
            result.push_back(x.second);
    }
    return result;
    // your code here
}