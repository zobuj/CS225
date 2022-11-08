
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <cmath>
template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(2*currentIdx<_elems.size()){
        return true;
    }
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(2*currentIdx >=_elems.size()){
        return -1;
    }
    if(2*currentIdx+1 >=_elems.size()){
        return 2*currentIdx;
    }
    if(higherPriority(_elems[2*currentIdx+1],_elems[2*currentIdx])){
        return 2*currentIdx+1;
    }
    return 2*currentIdx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx)==false){
        return;
    }
    size_t minChildIndex = maxPriorityChild(currentIdx);
    if(higherPriority(_elems[minChildIndex],_elems[currentIdx])){
        std::swap(_elems[minChildIndex],_elems[currentIdx]);
        heapifyDown(minChildIndex);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    size_t counter = root()-1;
    while(counter!=elems.size()){
        _elems.push_back(elems[counter]);
        counter++;
    }
    for(size_t j = _elems.size()-root();j>0;j--){
        heapifyDown(j);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    
    T temp = _elems[root()];
    _elems[root()]=_elems[_elems.size()-root()];
    _elems.pop_back();
    heapifyDown(root());
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-root());
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx]=elem;
    if(idx==root()){
        heapifyDown(idx);
    }else{
        heapifyUp(idx);
    }

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size()<=root()){
        return true;
    }
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}

