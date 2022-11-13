/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "nim_learner.h"
#include <ctime>
using std::cout;
using std::endl;

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    for(int i = startingTokens;i>=0;i--){
      Vertex v1 = "p1-"+to_string(i);
      Vertex v2 = "p2-"+to_string(i);
      g_.insertVertex(v1);
      g_.insertVertex(v2);
      if(i>=2){
        g_.insertEdge(v1,"p2-"+to_string(i-2));
        g_.setEdgeWeight(v1,"p2-"+to_string(i-2),0);
        g_.insertEdge(v2,"p1-"+to_string(i-2));
        g_.setEdgeWeight(v2,"p1-"+to_string(i-2),0);
      }
      if(i>=1){
        g_.insertEdge(v1,"p2-"+to_string(i-1));
        g_.setEdgeWeight(v1,"p2-"+to_string(i-1),0);
        g_.insertEdge(v2,"p1-"+to_string(i-1));
        g_.setEdgeWeight(v2,"p1-"+to_string(i-1),0);
      }
    }
    tokens=startingTokens;
   // g_.print();
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
   /* Your code goes here! */
  //cout<<tokens<<endl;
   vector<Vertex> test = g_.getAdjacent("p1-"+to_string(tokens));
  //cout<<test.size()<<endl;
  int chooseRandom=0;
  Vertex s = "p1-"+to_string(tokens);
  Vertex d = "";
  //cout<<test.empty()<<endl;
  while(d!="p1-0"||d!="p2-0"){
    if(test.size()==0){
      break;
    }else if(test.size()==1){
      chooseRandom=0;
    }else{
      chooseRandom = (rand()%2);
    }
    //cout<<"Random Number: "<<chooseRandom<<endl;
    Vertex random = test[chooseRandom];
    d=random;
    Edge pathEdge = g_.getEdge(s,random);
    path.push_back(pathEdge);
    test=g_.getAdjacent(random);
    s=random;
  }
    return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
  Vertex win = path.back().dest;
  if(win=="p2-0"){
    //p1 wins
    for(size_t i=0;i<path.size();i++){
      int tempWeight = g_.getEdgeWeight(path[i].source,path[i].dest);
      if(path[i].source[1]=='1'){
        tempWeight+=1;
       g_.setEdgeWeight(path[i].source,path[i].dest,tempWeight);
      }else if(path[i].source[1]=='2'){
        tempWeight-=1;
       g_.setEdgeWeight(path[i].source,path[i].dest,tempWeight);
      }
    }
  }else if(win=="p1-0"){
    //p2 wins
    for(size_t j=0;j<path.size();j++){
      int tempWeight = g_.getEdgeWeight(path[j].source,path[j].dest);
      if(path[j].source[1]=='1'){
        tempWeight-=1;
       g_.setEdgeWeight(path[j].source,path[j].dest,tempWeight);
      }else if(path[j].source[1]=='2'){
        tempWeight+=1;
       g_.setEdgeWeight(path[j].source,path[j].dest,tempWeight);
      }
    }
  }

}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
