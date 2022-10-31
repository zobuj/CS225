/* Your code here! */
#pragma once
#include <vector>
using namespace std;
class DisjointSets{
    public:
    DisjointSets();
    void addelements(int num);
    int find(int elem);
    void setunion(int a,int b);
    int size(int elem);
    int getNumTrees();
    void printAllNodes();
    private:
    vector<int> allNodes;//stores every node seen in the tree including the representative nodes
    int numTrees;
};

