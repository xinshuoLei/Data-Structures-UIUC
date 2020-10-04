/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode* temp = head_ -> next;
    delete head_;
    head_ = temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }

  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  if (splitPoint == 0) {
    return start;
  }

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* current = head_;
  int endIndex = 0;
  for (int i = 0; i + 2 < size() && current != NULL; i += 3) {
    if (i == 0) {
      head_ = current -> next;
    }

    ListNode* second = current -> next;
    ListNode* third = current -> next -> next;
    
    ListNode* temp = current -> prev;
    ListNode* nextStart = third -> next;
    
    second -> prev = temp;
    if (temp != NULL) {
      temp -> next = second;
    }

    current -> next = nextStart;
    if (nextStart != NULL) {
      nextStart -> prev = current;
    }

    current -> prev = third;
    third -> next = current;

    if (i + 2 == size() - 1) {
      tail_ = current;
    }
    
    current = current -> next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  }
  if (startPoint != NULL && endPoint != NULL) {
    ListNode* current = startPoint; 
    ListNode* endNext = endPoint -> next;
    ListNode* startPrev = startPoint -> prev;

    while (current != endNext && current != NULL) {
      ListNode* current_next = current -> next;
      ListNode* current_prev = current -> prev;
      current -> next = current_prev;
      current -> prev = current_next;
      current = current_next;
    }


    ListNode* temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;

    startPoint -> prev = startPrev;
    if (startPrev != NULL) {
      startPrev -> next = startPoint;
    }

    endPoint -> next = endNext;
    if (endNext != NULL) {
      endNext -> prev = endPoint;
    }

  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (head_ == NULL || tail_ == NULL || n <= 1) {
    return;
  }
  if (n >= size()) {
    reverse();
    return;
  }

  ListNode* current = head_;
  for (int i = 0; i + n - 1 < size() && current != NULL; i += n) {
    ListNode* end = current;
    for (int j = 0; j < n - 1; j++) {
      end = end -> next;
    }
    ListNode* next = end -> next;
    reverse(current, end);
    if (i == 0) {
      head_ = current;
    }
    if (i + n - 1 == size() - 1) {
      tail_ = end;
    }
    current = next;
  }

  if (current != NULL) {
    ListNode* new_tail = current;
    reverse(current, tail_);
    tail_ = new_tail;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }

  ListNode* current_second = second;
  ListNode* current_first = first;
  ListNode* new_start = NULL;
  
  if (current_first -> data < current_second -> data) {
    new_start = current_first;
    current_first = current_first -> next;
  } else {
    new_start = current_second;
    current_second = current_second -> next;
  }

  ListNode* current_new = new_start;

  while (current_first != NULL || current_second != NULL) {
    if (current_first == NULL) {
      current_new -> next = current_second;
      current_second -> prev = current_new;
      break;
    } else if (current_second == NULL) {
      current_new -> next = current_first;
      current_first -> prev = current_new;
      break;
    }
    if (current_first -> data < current_second -> data) {
      current_new -> next = current_first;
      current_first -> prev = current_new;
      current_new = current_first;
      current_first = current_first -> next;
    } else {
      current_new -> next = current_second;
      current_second -> prev = current_new;
      current_new = current_second;
      current_second = current_second -> next;
    }
  }
  return new_start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1) {
    return start;
  }
  ListNode* second_start = start;
  for (int i = 0; i < chainLength / 2; i++) {
    second_start = second_start -> next;
  }
  second_start -> prev -> next = NULL;
  second_start -> prev = NULL;
  return merge(mergesort(start, chainLength / 2), mergesort(second_start, chainLength / 2 + chainLength % 2));
}
