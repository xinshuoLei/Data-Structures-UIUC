/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        elements.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if ((size_t) elem >= elements.size()) {
        return -1;
    }
    if (elements[elem] < 0) {
        return elem;
    }
    int root = find(elements[elem]);
    elements[elem] = root;
    return root;
}

void DisjointSets::setunion(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    if (root_a != -1 && root_b != -1) {
        int new_size = elements[root_a] + elements[root_b];
        if (elements[root_a] < elements[root_b]) {
            elements[root_b] = root_a;
            elements[root_a] = new_size;
        } else {
            elements[root_a] = root_b;
            elements[root_b] = new_size;
        }
    }
    
}

int DisjointSets::size(int elem) {
    if ((size_t) elem < elements.size()) {
        return (0 - elements[find(elem)]);
    }
    return -1;
}

