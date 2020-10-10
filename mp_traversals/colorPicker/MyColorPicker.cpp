#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;


MyColorPicker::MyColorPicker(HSLAPixel color1, HSLAPixel color2, unsigned line_spacing) {
  color1_ = color1;
  color2_ = color2;
  line_spacing_ = line_spacing;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if (x % line_spacing_ == 0) {
    return color1_;
  }
  return color2_;
}
