#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  tolerance_ = tolerance;
  png_ = png;
  start_ = start;
  stack.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, start_, tolerance_, png_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  /**
  if (point.x + 1 < png_.width()) {
    stack.push(Point(point.x + 1, point.y));
  }
  if (point.x - 1 >= 0) {
    stack.push(Point(point.x - 1, point.y));
  }
  if (point.y + 1 < png_.height()) {
    stack.push(Point(point.x, point.y + 1));
  }
  if (point.y - 1 >= 0) {
    stack.push(Point(point.x, point.y - 1));
  }
  */
  stack.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  /**
  while (!stack.empty()) {
    bool visited_before = false;
    for (auto i = visited.begin(); i != visited.end(); ++i) {
      if (*i == stack.top()) {
        visited_before = true;
      }
    }
    HSLAPixel start_pixel = png_.getPixel(stack.top().x, stack.top().y);
    HSLAPixel top_pixel = png_.getPixel(stack.top().x, stack.top().y); 
    if (visited_before) {
      stack.pop();
    } else {
      break;
    }
  }
  */
  Point top = stack.top();
  stack.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return stack.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return stack.empty();
}
