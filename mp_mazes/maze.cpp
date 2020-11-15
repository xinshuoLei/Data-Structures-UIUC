/* Your code here! */
#include <stdlib.h>
#include "maze.h"

void SquareMaze::makeMaze(int width, int height) { 
    width_ = width;
    height_ = height;
    // initialize walls
    walls = std::vector<std::vector<std::vector<bool>>>(width);
    for (int i = 0; i < width; i++) {
        walls[i] = std::vector<std::vector<bool>>(height);
        for (int j = 0; j < height; j++) {
            walls[i][j] = std::vector<bool>(2);
            // initially all walls exist
            walls[i][j][0] = true;
            walls[i][j][1] = true;
        }
    }
    // disjoint set for cycle detection
    DisjointSets d;
    d.addelements(width * height);

    // break walls until all cells are connected
    int num_sets = width * height;
    while (num_sets != 1) {
        int random_x = rand() % width;
        int random_y = rand() % height;
        int random_wall = rand() % 2;
        // if wall exists
        if (walls[random_x][random_y][random_wall]) {
            int cell = random_x * height + random_y; 
            // if random wall is the right wall of the cell
            if (random_wall == 0 && random_x < width - 1) {
                // check cycle
                if (d.find(cell) != d.find(cell + height)) {
                    d.setunion(cell, cell + height);
                    num_sets--;
                    walls[random_x][random_y][random_wall] = false;
                }
            } else if (random_wall == 1 && random_y < height - 1) {
                // if random wall is the bottom wall
                if (d.find(cell) != d.find(cell + 1)) {
                    d.setunion(cell, cell + 1);
                    num_sets--;
                    walls[random_x][random_y][random_wall] = false;
                }
            }
        }
    }
}

/**
 * dir = 0 represents a rightward step (+1 to the x coordinate)
 * dir = 1 represents a downward step (+1 to the y coordinate)
 * dir = 2 represents a leftward step (-1 to the x coordinate)
 * dir = 3 represents an upward step (-1 to the y coordinate)
 */ 
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (x >= width_ || y >= height_ || x < 0 || y < 0) {
        return false;
    }
    if (dir == 0) {
        if (x + 1 >= width_ || walls[x][y][0]) {
            return false;
        } 
    } else if (dir == 1) {
        if (y + 1 >= height_ || walls[x][y][1]) {
            return false;
        }
    } else if (dir == 2) {
        if (x - 1 < 0 || walls[x - 1][y][0]) {
            return false;
        }
    } else if (dir == 3) {
        if (y - 1 < 0 || walls[x][y - 1][1]) {
            return false;
        }
    }
    return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (x < width_ && y < height_ && x >= 0 && y >= 0) {
        walls[x][y][dir] = exists;
    }
}

std::vector<int> SquareMaze::solveMaze() {
    return std::vector<int>();
}

cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* maze = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);
    // blacken the topmost row except (1,0) through (9,0)
    for (int i = 0; i < width_ * 10 + 1; i++) {
        if (i < 1 || i > 9) {
            cs225::HSLAPixel& p1 = maze -> getPixel(i, 0);
            p1.l = 0;
        }
    } 
    // blacken the leftmost row
    for (int j = 0; j < height_ * 10 + 1; j++) {
        cs225::HSLAPixel& p2 = maze -> getPixel(0, j);
        p2.l = 0;
    }
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            // if right wall exists
            if (walls[x][y][0]) {
                for (int k1 = 0; k1 <= 10; k1++) {
                    cs225::HSLAPixel& p3 = maze -> getPixel((x + 1) * 10, y * 10 + k1);
                    p3.l = 0;
                }
            }
            if (walls[x][y][1]) {
                for (int k = 0; k <= 10; k++) {
                    cs225::HSLAPixel& p4 = maze -> getPixel(x * 10 + k, (y + 1) * 10);
                    p4.l = 0;
                }
            }
        }
    }
    return maze;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    return NULL;
}