/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] > second[curDim]) {
      return false;
    }
    return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int current_distance = 0;
    int potential_distance = 0;
    for (int i = 0; i < Dim; i++) {
      current_distance += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
      potential_distance += (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    if (potential_distance < current_distance) {
      return true;
    } else if (potential_distance > current_distance) {
      return false;
    }
    return potential < currentBest;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& v, int left, int right, int pivotIndex, int dimension) {
    Point<Dim> pivot = v[pivotIndex];
    Point<Dim> right_value = v[right];
    // swap v[pivotIndex] and v[right]
    v[right] = pivot;
    v[pivotIndex] = right_value;
    int storeIndex = left;
    for (int i = left; i < right; i++) {
      if (smallerDimVal(v[i], pivot, dimension)) {
        // swap v[storeIndex] and v[i]
        Point<Dim> temp = v[i];
        v[i] = v[storeIndex];
        v[storeIndex] = temp;
        storeIndex++;
      }
    }
    // swap v[right] and v[storeIndex]
    right_value = v[right];
    v[right] = v[storeIndex];
    v[storeIndex] = right_value;
    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quick_select(vector<Point<Dim>>& v, int left, int right, int median, int dimension) {
    if (left == right) {
      return v[left];
    }
    int pivotIndex = (left + right) / 2;
    pivotIndex = partition(v, left, right, pivotIndex, dimension);
    if (pivotIndex == median) {
      return v[median];
    } else if (median < pivotIndex) {
      return quick_select(v, left, pivotIndex - 1, median, dimension);
    }
    return quick_select(v, pivotIndex + 1, right, median, dimension);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim, int left, int right) {
    if (left <= right) {
      int median = (left + right) / 2;
      Point<Dim> middle = quick_select(points, left, right, median, dim % Dim);
      KDTreeNode* currRoot = new KDTreeNode();
      currRoot -> point = middle;
      currRoot -> left = buildTree(points, (dim + 1) % Dim, left, median - 1);
      currRoot -> right = buildTree(points, (dim + 1) % Dim, median + 1, right);
      return currRoot;
    }
    return NULL;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> points_copy(newPoints);
    size = newPoints.size();
    root = buildTree(points_copy, 0, 0, size - 1);
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* subRoot) {
  if (subRoot == NULL) {
    return NULL;
  }
  KDTreeNode* currRoot = new KDTreeNode();
  currRoot -> point = subRoot -> point;
  currRoot -> left = copy(subRoot -> left);
  currRoot -> right = copt(subRoot -> right);
  return currRoot;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subRoot) {
  if (subRoot == NULL) {
    return;
  }
  clear(subRoot -> left);
  clear(subRoot -> right);
  delete subRoot;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = copy(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (*this != &rhs) {
    clear(root);
    root = copy(rhs.root);
    size = rhs.size;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return find(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::find(const Point<Dim>& query, int dim, KDTreeNode* subRoot) const{
    if (subRoot == NULL) {
      return Point<Dim>();
    }
    // if subRoot is leaf 
    if (subRoot -> left == NULL && subRoot -> right == NULL) {
      return subRoot -> point;
    }
    if (subRoot -> point == query) {
      return subRoot -> point;
    }
    // traverse down
    Point<Dim> nearest;
    bool left_recurse = false;
    if (smallerDimVal(query, subRoot -> point, dim)) {
      nearest = find(query, (dim + 1) % Dim, subRoot -> left);
      left_recurse = true;
    } else {
      nearest = find(query, (dim + 1) % Dim, subRoot -> right);
    }
    // if subRoot is closer, replace neareset with subRoot
    if (shouldReplace(query, nearest, subRoot -> point)) {
      nearest = subRoot -> point;
    }
    // calculate radius and splitDistance
    double radius = 0;
    for (int i = 0; i < Dim; i++) {
      radius += (nearest[i] - query[i]) * (nearest[i] - query[i]); 
    }
    double splitDistance = (subRoot -> point[dim] - query[dim]) * (subRoot -> point[dim] - query[dim]);
    // if radius >= splitDistance, check other subtrees
    if (radius >= splitDistance) {
      Point<Dim> temp;
      if (left_recurse) {
        temp = find(query, (dim + 1) % Dim, subRoot -> right);
      } else {
        temp = find(query, (dim + 1) % Dim, subRoot -> left);
      }
      if (shouldReplace(query, nearest, temp)) {
        nearest = temp;
      }
    }
    return nearest;
}



