#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;
MyColorPicker::MyColorPicker():hue(360){}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  
  HSLAPixel pixel(hue,1, 0.5);
  hue-=1;
  if(hue<0){
    hue=360;
  }
  if(hue%2==0){
    hue-=20;
  }
  return pixel;
}

