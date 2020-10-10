#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
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
  traversal_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point point, double tolerance, PNG png) {
  start_point = point;
  it_tolerance_ = tolerance;
  traversal_ = traversal;
  current_point = traversal -> peek();
  it_png = png;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  visited.push_back(current_point); 
  if (!traversal_ -> empty()) {
    current_point = traversal_-> pop();
  } 
  if (current_point.x + 1 < it_png.width()) {
    traversal_ -> add(Point(current_point.x + 1, current_point.y));
  }
  if (current_point.y + 1 < it_png.height()) {
    traversal_ -> add(Point(current_point.x, current_point.y + 1));
  }
  if (current_point.x >= 1) {
    traversal_ -> add(Point(current_point.x - 1, current_point.y));
  }
  if (current_point.y >= 1) {
    traversal_ -> add(Point(current_point.x, current_point.y - 1));
  }
  HSLAPixel start_pixel = it_png.getPixel(start_point.x, start_point.y);
  while (!traversal_ -> empty()) {
    HSLAPixel current_pixel = it_png.getPixel(traversal_ -> peek().x, traversal_ -> peek().y);
    bool visited_before = false;
    for (auto i = visited.begin(); i != visited.end(); ++i) {
      if (*i == traversal_ -> peek()) {
        visited_before = true;
      }
    }
    if (calculateDelta(start_pixel, current_pixel) >= it_tolerance_ || visited_before) {
      traversal_ -> pop();
    } else {
      break;
    }
  }
  if (!traversal_->empty()) {
    current_point = traversal_ -> peek(); 
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
  return current_point;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool traversal_empty = false;
  bool other_empty = false;
  if (traversal_ == NULL || traversal_ -> empty()) {
    traversal_empty = true;
  }
  if (other.traversal_ == NULL || other.traversal_ -> empty()) {
    other_empty = true;
  }
  if (traversal_empty && other_empty) {
    return false;
  } else if (!traversal_empty && !other_empty) {
    return traversal_ != other.traversal_;
  } 
  return true;
}

