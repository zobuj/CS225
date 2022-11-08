
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;


int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG finalImage;
  finalImage.readFromFile("../tests/i.png");
  FloodFilledImage i(finalImage);
  BFS b(finalImage, Point(finalImage.width()/2, finalImage.height()/2), 0.02);
  //DFS d(finalImage, Point(finalImage.width()/2, finalImage.height()/2), 0.001);
  MyColorPicker r;
  i.addFloodFill(b,r);
  //i.addFloodFill(d,r);
  Animation animation = i.animate(50);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  
  
return 0;

}
