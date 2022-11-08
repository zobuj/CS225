/* Your code here! */
#include "dsets.h"
#include <iostream>
using namespace std;

    /*
    A disjoint set data structure allows for organization of elements in sets and
    allows for the ability to query which set an element belongs to in constant time.
    The data structure that will create the disjoint set will be a forest of trees,
    where each set is represented by a tree and each tree is identified by its root node.

    NOTE: This means that each set will be represented on the tree by the root node
    Thus we should store a pointer to the root of the tree

    Unionize Sets:
    There are two types of unions:

    union by rank: which minimizes the height of the disjointset by appending
    the tree of smaller rank to the root of the other(seems to be a recursive algo
    where we are finding the tree with the smallest height and then pointing it to
    the root of the higher rank tree).

    union by size: appends the tree of smaller size to the root of the other
    This is also a recursive algo where instead of comparing height we are comparing,
    number of nodes. Seems that we will use the size function for this one.

    Path Compression is an algo that will lower the runtime of accessing nodes,
    by moving each node that it visits up to the representative node. It decreases
    the rank of each of the nodes in the tree

    Array Implementation:
    Disjoint sets can be implemented as arrays in which negative numbers indicate
    that they are representatives and positive numbers are pointers to their parents
    
    Example:
    | 2 | -3 | 2 | -1 | -1 | 7 | -4 | 9 | 7 |
      1    2   3    4    5   6    7   8   9

    As you can see in the array above, the negaive numbers are the representative nodes
    and will have a magnitude of the number of nodes that they hold within their tree.
    Then the positive numbers will have an number inside of them that is the index of 
    the node that they are pointing to. 

    It is important to keep in mind that with union by rank or size and path compression
    will change value of each of the elements in the array.

    Idea for union algo:

    iterate through the array and find the point a point that is a representative node
    once a representative node is found then store it as the greatest rank tree,
    then continue iterating until a new representative node is found once that node is found
    then compare it to the current greatest rank tree if which ever has the lower rank 
    will be the one that will point to the index of the new greatest rank tree.

    You also need to change the number of the nodes int the representative tree by storeing the
    negative number in the lower rank tree
    */

DisjointSets::DisjointSets(){
    numTrees=0;
}
void DisjointSets::addelements(int num){
    //Creates n unconnected root nodes at the end of the vector
    //Parameters: num-the number of nodes to create
    if(num==0){//if no elements are being added then just return
        return;
    }

    for(int i  = 0;i<num;i++){
        allNodes.push_back(-1);
        /*each of the elements that are added are not 
        connected so a -1 will represent different trees with one element*/
    }
    numTrees +=num;
    //cout<<"NumTrees:"<<numTrees<<endl;
}

int DisjointSets::find(int elem){
    //This function should compress paths and works as described in lecture
    //Returns: the index of the root of the up-tree in which the parameter element resides
    if(allNodes[elem]<0){
        return elem;//base case to check whether or not the value at the index is a representative node
    }
    else{
        
        allNodes[elem]=find(allNodes[elem]); //finds the representative node for the current node and then points to that node
        return allNodes[elem];//then we return the representative node
    }
    
}

void DisjointSets::setunion(int a, int b){
    /*
    This function should be implemented as union-by-size.

    That is when you setunion two disjoint sets, the smaller(in terms of number of nodes)
    should point at the larger. This function works as described in lecture, except that
    should not assume that the arguments to setunion are roots of existing uptrees.

    Your set union function should find the roots of its arguments before combining the trees.
    If the two sets are the same size, make the tree containing the second argument point to the tree
    containing the first. (Note that normally we could break this tie arbitrarily, but int his case we want
    to control things for grading)

    Parameters: 
    a - index of the first element to union
    b - index of the second element to union 
    */
    if((-1*allNodes[find(a)])>(-1*allNodes[find(b)])){
        /*if a's tree has more nodes then we are going to replace the value at the
        index for b's tree to be a pointer to a's tree, then we are going to update the
        value at the index of a's tree beacuse we added the points from b's tree.
        Thus we store the values from b's tree and then just add them to the value 
        at a's tree
        */
        int tempBSize = allNodes[find(b)];
        allNodes[find(b)]=find(a);
        allNodes[find(a)]+=tempBSize;
    }else{
        //we do the same as above but reverse
        int tempASize = allNodes[find(a)];
        allNodes[find(a)]=find(b);
        allNodes[find(b)]+=tempASize;
    }
}

int DisjointSets::size(int elem){
    //This function should return the number of nodes in the up-tree containing the element
    //Returns: number of nodes in the up-tree containing the element

    int index = find(elem);//finds the representative node for the element
    int result = allNodes[index]*-1;//then the negated value at the index of the representative node is the number of nodes in the tree
    return result;//then we just return that number of nodes
    
    
}

int DisjointSets::getNumTrees(){
    return numTrees;
}
void DisjointSets::printAllNodes(){
    for(size_t i  = 0;i<allNodes.size();i++){
            cout<<allNodes[i]<<" ";
    }
    cout<<endl;
}