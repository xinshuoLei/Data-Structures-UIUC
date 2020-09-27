#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "List.h"


int main() {
  List<int> list;
  list.insertFront(3);
  list.insertFront(2);
  std::cout << "still working" << std::endl;
  stringstream s;
  list.print(s);
  std::cout << s.str();
}
