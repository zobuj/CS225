#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal=NULL;
}
ImageTraversal::Iterator::Iterator(ImageTraversal * tr, PNG i, Point s, double t) {
  /** @todo [Part 1] */
  traversal=tr;
  img=i;
  startP=s;
  currP=s;
  toler=t;
  /*for(unsigned int w = 0;w<img.width();w++){
    for(unsigned int h=0;h<img.height();h++){
      Point p = Point(w,h);
      visitedPoints[p]=false;
    }
  }*/
  visitedPoints.resize(img.width()*img.height());
  for(unsigned int i=0;i<img.width()*img.height();i++){
    visitedPoints[i]=false;
  }
}
int ImageTraversal::Iterator::transformPoint(Point p){
  unsigned int h= img.height();
  return p.x*(h)+p.y;
}
bool ImageTraversal::Iterator::validPoint(Point p){
  if(p.x>=0&&p.x<img.width() && p.y>=0&&p.y<img.height() && visitedPoints[transformPoint(p)]==false && calculateDelta(img.getPixel(startP.x,startP.y),img.getPixel(p.x,p.y))<toler){
    return true;
  }
  return false;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  /*--------------STEP 3-------------*/
  visitedPoints[transformPoint(currP)]=true;
  
  /*--------------STEP 4-------------*/
  Point r =Point(currP.x+1,currP.y);
  if(validPoint(r)){
    traversal->add(r);
  }
  Point d = Point(currP.x,currP.y+1);
  if(validPoint(d)){
    traversal->add(d);
  }
  Point l = Point(currP.x-1, currP.y);
  if(validPoint(l)){
    traversal->add(l);
  }
  Point u = Point(currP.x,currP.y-1);
  if(validPoint(u)){
    traversal->add(u);
  }
  /*--------------STEP 5-------------*/
  while(!traversal->empty()&&visitedPoints[transformPoint(traversal->peek())]==true){//negation of empty or not visited-> not empty and is visited
    traversal->pop();
  }
  /*--------------STEP 6-------------*/
  if(!traversal->empty()){
    currP=traversal->peek();
  }
  /*--------------STEP 7-------------*/
  else{
    traversal=NULL;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currP;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool tff, off;
  if(this->traversal==NULL){
    tff=true;
  }
  else{
    tff=false;
  }
  if(other.traversal==NULL){
    off=true;
  }
  else{
    off=false;
  }
  return !(tff&&off);
}


