/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
 
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;
 
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]==second[curDim]){
      return first<second;
    }
    else if(first[curDim]<second[curDim]){
      return true;
    }
    return false;
}
 
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
      //calculate the distance from the target to the current best
      //calculate the distance from the target to the potential best
      int TtoC=0;
      int TtoP=0;
      for(int i =0;i<Dim;i++){
        TtoC+=((target[i]-currentBest[i])*(target[i]-currentBest[i]));
        TtoP+=((target[i]-potential[i])*(target[i]-potential[i]));
 
      }
      //compare the two distances and return true if the potential to target distance
      //is less than the target to current distance
      if(TtoP<TtoC){
        return true;
      }else if(TtoP>TtoC){
        return false;
      }else{
        return potential<currentBest;
      }
 
}
 
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildTree(int low, int high, int dim){
  if(low<=high){//checks if the vector is empty, the recursion will end when one of the sides of the vector will be zero, then no new nodes will be made
    int middle = floor((low+high)/2);//find the median of the vector that we are working with depending on whether that be the original or a left subtree or right subtree
    /* Select will do the most amount of work for this algo, where it sort the vector with regard to the current dimension
    and then the median of the sorted vector is the one that we will use to make a new node*/
    select(low,high,dim,middle);
    KDTreeNode*newNode = new KDTreeNode(permPoints[middle]);//new node will be made from the sorted vector
    newNode->left=buildTree(low,middle-1,(dim+1)%Dim);//now we will call the helper function again to work on the previously sorted vector, but only to work on the elements that are to the left of the median
    newNode->right=buildTree(middle+1,high,(dim+1)%Dim);//the same will go for the right side of the median
    return newNode;//then we will return the newnode, and since we are making a tree just returning a pointer to the root is what is needed to find any element in the tree.
  }
  return NULL; 
  
}
/*
QUICK SELECT ALGO:
Partition and Select Functions
*/
/*
Partition ensures that once select is done, every element left of k will be smaller, making the element at index k the kth smallest
Thus the point in the center of the vector will be the point that should be used to make a node on the k-d tree
*/
template <int Dim>
int KDTree<Dim>::partition(int low, int high, int dim, int pivotIndex){
  Point<Dim> pivotValue = permPoints[pivotIndex];//point for comparision
  swap(permPoints[pivotIndex], permPoints[high]);//move the point to the right of the vector 
  int storeIndex = low;//create a variable to store the point where the swap should occur if the value in the loop is smaller than the comparison point
  for(int i  = low;i<high;i++){//move through the vector checking if the current point has a smaller dimension value than the comparison point
    if(smallerDimVal(permPoints[i],pivotValue,dim)){
      swap(permPoints[storeIndex],permPoints[i]);//if the point does have a smaller dimension then we are able to swap it with the current store point
      storeIndex++;//increment the store point
    }
  }
  swap(permPoints[high],permPoints[storeIndex]);//finally swap the comparison point into its correct location
  return storeIndex;//the store index will be returned and used in the select function
}
 
template <int Dim>
 void KDTree<Dim>::select(int low, int high, int dim, int k){
  int pivotIndex = floor((low+high)/2);//middle of the vector
  pivotIndex = partition(low,high,dim,pivotIndex);//the pivot index will be updtated after each iteration as the array gets smaller and sorted
  //the remaning if statements will check if the pivot is in the final sorted position
  if(k==pivotIndex){//base case
    return;//once the base case is reached then we just return because now the middle of the vector is the node where we should make a new node
  }else if(k<pivotIndex){
    select(low,pivotIndex-1,dim,k);//left side of the vector
  }else{
    select(pivotIndex+1,high,dim,k);//right side of the vector
  }
}
 
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
   
    /*
    Things we need to store:
    1. Point that will represent the root of the tree
    2. Dimension variable counter
    3. Median of points across a splitting dimension
      a. ceil(n/2): middle most element of a sorted list containing n elements
      b. floor((a+b)/2): where a is the zero index and b is the final index
      c. Median index of n nodes is calculated as the cell floor((n-1)/2)
      d. you also have to consider if two pointes have equal value along a dimension
      that you are splitting, thus every point that exists on the splitting line must be
      moved to the right or the left subtree
 
    Things we need to consider:
    1. Which way we will split, in the x or y (d+1) mod k
      a. (0+1) mod 2 = 1, (1+1) mod 2 = 0 (will oscillate between zero and one, or x and y)
    2. The k-d tree will have two subtrees:
      a. A left subtree where if v is an element in that subtree then v_d <= r_d
      b. A right subtree where if v is an element in that subtree then v_d >= r_d
    3. Should use smaller dimension val
    */
    permPoints = newPoints;//copy the points from new points into a global variable that any function can access, a set of permanent points that will be sorted in a respect dimension
    //once sorted, nodes can be made from them
    root=buildTree(0,permPoints.size()-1,0);
   
}
template <int Dim>
void KDTree<Dim>::copyHelper_(KDTreeNode * from, KDTreeNode * to){
  from->permPoints = to->permPoints;
  to= new KDTreeNode(from->point);

}
template <int Dim>
void KDTree<Dim>::remove_(KDTreeNode * root){
 if(root==NULL){//if the tree is already empty then just return
  return;
 }
  remove_(root->left);
  remove_(root->right);
  delete root;
}
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copyHelper_(this->root,other.root);
 
}
 
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  remove_(this->root);
  copyHelper_(this->root,rhs.root);
  return *this;
}
 
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   remove_(root);
}
 
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(root,query,root->point, 0);
}
 
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * curr,const Point<Dim> query, Point<Dim> best, int dim) const
{
    /**
     * @todo Implement this function!
     */
    if(curr->left==NULL&&curr->right==NULL){
      return curr->point;
    }
    KDTreeNode*next =NULL;
    KDTreeNode*other =NULL;
    if(smallerDimVal(curr->point,query,dim)){
      if(curr->right!=NULL){
        next=curr->right;
        other=curr->left;
        best=findNearestNeighbor(next,query,best,(dim+1)%Dim);
      }
    }else{
      if(curr->left!=NULL){
        next=curr->left;
        other=curr->right;
        best=findNearestNeighbor(next,query,best,(dim+1)%Dim);
      }
    }
    if(shouldReplace(query,best,curr->point)){
      best=curr->point;
    }
    double radius = 0.0;
    for(int i = 0;i<Dim;i++){
      radius+=(best[i]-query[i])*(best[i]-query[i]);
    }
    double splitDist = (query[dim]-curr->point[dim])*(query[dim]-curr->point[dim]);
    if(radius>=splitDist){
      if(other){
        Point<Dim> near = findNearestNeighbor(other, query, best,(dim+1)%Dim);
          if(shouldReplace(query, best, near)){
            best=near;
          }
      }
    }

  return best;
}
