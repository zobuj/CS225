/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
using namespace std;
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_=0;/*CHANGED Because the length must be set to zero*/
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(this->head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
 
template <typename T>
void List<T>::_destroy() { /*CHANGED THIS*/
  /// @todo Graded in MP3.1
  ListNode * tempHead = head_;
  while(head_!=NULL){
    head_ = head_->next;
    delete tempHead;
    tempHead = head_;
  }
  head_=NULL,tail_=NULL;
  length_=0;
  //std::cout<<"Called Destroy"<<std::endl;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */

template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;//new node points to the head of the original list
  newNode -> prev = NULL;// the node previous to the new node will be a null element because it is now the front of the list
  
  if (head_ != NULL) {// this is basically checking if there is actually an element that is located at the head of the list
    head_ -> prev = newNode;// if there is an element in the front of the list then we are able to 
  }
  if (tail_ == NULL) {//if the list is completely empty then we are able to just set the end of the list where it would also be the head to the newest node.
    tail_ = newNode;
  }
  head_=newNode;/*CHANGED THIS BECAUSE THE HEAD WAS NEVER RESET*/
  length_++;
  
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
 
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if(head_==NULL&&tail_==NULL){//Checking to see if the list is empty
    head_=newNode;//Since the list is empty we are essentialy setting the head and tail of the new list to the new node.
    tail_=newNode;
  }else{//if the list is not empty then we are going to first set the next pointer of our new node to be pointing to a NULL area in memory
    newNode->next = NULL;
    tail_->next = newNode;//then we are going to set the next pointer of the tail of the original list to be pointing to the new node
    tail_=newNode;//finally we set the tail pointer to point to the new node
  }
  length_++;//then we increment the size of the list.
}


/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
 /*CHANGED FUNCTION*/
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  /*
  Split(2) 
  <0 1 2 3 4 5> -> <0 1> <2 3 4 5>
  <2 3 4 5> is returned
  */
  ListNode * curr = start;
  ListNode * prevNode;
  if(splitPoint>0 && splitPoint<length_){//iteration will only occur when the split point lies within the span of the list
    for (int i = 0; i < splitPoint; i++) {
      prevNode = curr;//a second pointer will be used to track the node right before where the new head will be at, so we can just set the next of the previous node to NULL
      curr = curr->next;//the loop will iterate until the current node is the node where we split at, thus giving us the ability to return at that node making it the head of the new list
    }
    prevNode->next=NULL;

    return curr;
  }
  return start;//if the split point lies outside the span of the list, then there is no need to iterate through the list, and the list should just be returned
}



/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  int groupnum =this->size()/3;
  if(this->size()<3){
    return;
  }else{
    for(int i = 0;i<groupnum;i++){
      
      if(i==0){
        ListNode*move =head_;
        for(int i  = 0;i<2;i++){
          move=move->next;
        }
        ListNode*temp = head_->next;
        head_->next=move->next;
        move->next=head_;
        head_=temp;
      }
      else{
        ListNode*inner = head_;
        ListNode*outer = head_;
        ListNode*prevInner =head_;
        
        for(int k = 0;k<((i*3)+2);k++){
          outer=outer->next;
          if(k<(i*3)){
            inner =inner->next;
          }
          if(k<((i*3)-1)){
            prevInner =prevInner->next;
          }
        }
        
        ListNode*temp =inner->next;
        inner->next=outer->next;
        outer->next = inner;
        prevInner->next = temp;
      }
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

template <typename T>
void List<T>::reverseSome() {
  reverse(head_->next,head_->next->next->next->next->next);
}
/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(startPoint==head_&& endPoint==tail_){//if we are going to reverse the entire linked list, then a new head must be set
    ListNode*newNull= NULL;
    ListNode*slow=newNull;
    ListNode*fast=startPoint;
    ListNode*temp;
    while(fast!=NULL){
      temp=fast->next;
      fast->next=slow;
      slow=fast;
      fast=temp;
    }
    head_=endPoint;
    tail_=startPoint;
    
  }
  else if(startPoint==head_&&endPoint!=tail_){
    ListNode*end=endPoint;
    ListNode*newNext =endPoint->next;
    ListNode*slow=newNext;
    ListNode*fast= startPoint;
    ListNode*temp;
    while(fast!=newNext){
      temp=fast->next;
      fast->next=slow;
      slow=fast;
      fast=temp;
    }
    head_=end;
  }
  
  else if(startPoint!=head_&& endPoint==tail_){
    ListNode*prev=head_;//node previous to startpoint, Would be the nullptr if the start pointer was the head
    while(prev->next!=startPoint){
      prev=prev->next;
    }
    ListNode*slow=startPoint;
    ListNode*fast=startPoint->next;
    ListNode*temp;
    while(fast!=NULL){
      temp=fast->next;
      fast->next=slow;
      slow=fast;
      fast=temp;
    }
    startPoint->next=NULL;
    prev->next=endPoint;
    tail_=startPoint;
  }
  
  else if(startPoint!=head_&&endPoint!=tail_){
    ListNode*tempEndpoint=endPoint;
    ListNode*prev = head_;
    while(prev->next!=startPoint){
      prev=prev->next;
    }
    ListNode*next=endPoint->next;
    ListNode*slow=startPoint;
    ListNode*fast=startPoint->next;
    ListNode*temp;
    while(fast!=next){
      temp=fast->next;
      fast->next=slow;
      slow=fast;
      fast=temp;
    }
    
    startPoint->next=next;
    prev->next=tempEndpoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode*finalN=tail_;
  ListNode*innerScope = head_;
  ListNode*outerScope = head_;
  if(n<=1){return;}
  if(head_==NULL){
    return;
  }
  if(head_==tail_){
    return;
  }
  if(n>this->size()){
    return;
  }
  while(innerScope!=tail_->next){
    for(int i=0;i<n-1;i++){
      if(outerScope!=finalN){
        outerScope=outerScope->next;
      }
    }
    ListNode*temp=outerScope->next;
    reverse(innerScope,outerScope);
    innerScope=temp;
    outerScope=temp;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  /*
  List 1: <1 3 4 6>
  FirstPtr: <1>
  List 2: <2 5 7> 
  SecondPtr: <2>
  */
  ListNode*HOSL=NULL;
  if(first==NULL){
    return second;
  }
  if(second==NULL){
    return first;
  }
  if(first==NULL&&second ==NULL){
    return NULL;
  }
  if(first==second){
    return first;
  }
  if(first->data<second->data){
    HOSL=first;
    first=first->next;
  }else{
    HOSL=second;
    second=second->next;
  }
  ListNode*LI=HOSL;
  int counter=0;
  while(first!=NULL&&second!=NULL){
    if(first!=NULL){
      if(second!=NULL){
      if(first->data<second->data){
        LI->next=first;
        first=first->next;
      }else{
        LI->next=second;
        second=second->next;
      }
      LI=LI->next;
      }
    }else{
      break;
    }
    counter++;
  }
  if(first==NULL){
    LI->next=second;
  }else{
    LI->next=first;
  }
  cout<<counter<<endl;
  return HOSL;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode*first=start;
  ListNode*second=split(start,chainLength/2);
  ListNode*finalNode;
  int HOI;
  if(chainLength%2==0){
    HOI=(chainLength/2);
  }else{
    HOI=chainLength-(chainLength/2);
  }
  if(chainLength==0){
    return start;
  }
  if(chainLength==1){
    return start;
  }
  first=mergesort(first,chainLength/2);
  second=mergesort(second,HOI);
  finalNode=merge(first,second);
  return finalNode;
  
}

