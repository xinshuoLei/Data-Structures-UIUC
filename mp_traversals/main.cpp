
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
  
  PNG base = PNG();
  base.readFromFile("tests/pacman.png");
  FloodFilledImage flood(base);

  BFS body(base, Point(100, 50), 0.2);
  HSLAPixel blue(231, 1, 0.5);
  HSLAPixel yellow(50, 1, 0.5);
  MyColorPicker color(blue, yellow, 10);
  flood.addFloodFill(body, color);

  HSLAPixel light_blue(200, 1, 0.5);
  SolidColorPicker solid_color1(light_blue);
  DFS background(base, Point(0,0), 0.4);
  flood.addFloodFill(background, solid_color1);

  HSLAPixel black(0, 1, 0);
  SolidColorPicker solid_color2(black);
  DFS left_eye(base, Point(50,90), 0.4);
  flood.addFloodFill(left_eye, solid_color2);

  DFS right_eye(base, Point(100,90), 0.4);
  flood.addFloodFill(right_eye, solid_color2);

  Animation animation = flood.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");


  return 0;
}
