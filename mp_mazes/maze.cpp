/* Your code here! */
#include <stdlib.h>
#include <queue>
#include <algorithm>
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
            int cell = random_x + random_y * width; 
            // if random wall is the right wall of the cell
            if (random_wall == 0 && random_x < width - 1) {
                // check cycle
                if (d.find(cell) != d.find(cell + 1)) {
                    d.setunion(cell, cell + 1);
                    num_sets--;
                    walls[random_x][random_y][random_wall] = false;
                }
            } else if (random_wall == 1 && random_y < height - 1) {
                // if random wall is the bottom wall
                if (d.find(cell) != d.find(cell + width)) {
                    d.setunion(cell, cell + width);
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
    std::queue<int> q;
    std::vector<int> prev = std::vector<int>(width_ * height_);
    std::vector<int> distance = std::vector<int>(width_ * height_);
    for (int i = 0; i < width_ * height_; i++) {
        // use -1 to indicate not visited
        prev[i] = -1; 
        distance[i] = 0;
    }
    // start bfs by visiting (0,0) 
    q.push(0);
    prev[0] = 0;
    while (!q.empty()) {
        int index = q.front();
        q.pop();
        // index = x + y * width;
        int x = index % width_;
        int y = (index - x) / width_;
        // if neighbors not visited
        // dir = 0 represents a rightward step (+1 to the x coordinate)
        // dir = 1 represents a downward step (+1 to the y coordinate)
        // dir = 2 represents a leftward step (-1 to the x coordinate)
        // dir = 3 represents an upward step (-1 to the y coordinate)
        if (canTravel(x, y, 0) && prev[index + 1] == -1) {
            q.push(index + 1);
            prev[index + 1] = index;
            distance[index + 1] = distance[index] + 1;
        }
        if (canTravel(x, y, 1) && prev[index + width_] == -1) {
            q.push(index + width_);
            prev[index + width_] = index;
            distance[index + width_] = distance[index] + 1;
        }
        if (canTravel(x, y, 2) && prev[index - 1] == -1) {
            q.push(index - 1);
            prev[index - 1] = index;
            distance[index - 1] = distance[index] + 1;
        }
        if (canTravel(x, y, 3) && prev[index - width_] == -1) {
            q.push(index - width_);
            prev[index - width_] = index;
            distance[index - width_] = distance[index] - 1;
        }
    }
    // compare all distances in the last row to find exit
    int exit = width_ * height_ - 1;
    for (int j = (height_ - 1) * width_; j < width_ * height_ - 1; j ++) {
        if (distance[j] > distance[exit]) {
            exit = j;
        } else if (distance[j] == distance[exit]) {
            int exit_x_ = exit % width_;
            int current_x = j % width_;
            // If multiple paths of maximum length exist, 
            // use the one with the destination cell that has the smallest x value.
            if (current_x < exit_x_) {
                exit = j;
            } 
        }
    }
    exit_x = exit % width_;
    exit_y = (exit - exit_x) / width_;
    // backtrack to get solution
    std::vector<int> solution;
    int current = exit;
    while (current != 0) {
        if (prev[current] == current - 1) {
            solution.push_back(0);
        } else if (prev[current] == current - width_) {
            solution.push_back(1);
        } else if (prev[current] == current + 1) {
            solution.push_back(2);
        } else {
            solution.push_back(3);
        }
        current = prev[current];
    }
    std::reverse(solution.begin(), solution.end());
    return solution;
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
    cs225::PNG* maze = drawMaze();
    std::vector<int> solution = solveMaze();
    cs225::HSLAPixel red = cs225::HSLAPixel(0, 1, 0.5, 1);
    int x = 5;
    int y = 5;
    /**
     * Start at pixel (5,5). Each direction in the solution vector corresponds to a trail 
     * of 11 red pixels in the given direction. If the first step is downward, color pixels 
     * (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). Then if the second step is right, 
     * color pixels (5,15) through (15,15) red. Then if the third step is up, color pixels 
     * (15,15) through (15,5) red. Continue in this manner until you get to the end of 
     * the solution vector
     * dir = 0 represents a rightward step (+1 to the x coordinate)
     * dir = 1 represents a downward step (+1 to the y coordinate)
     * dir = 2 represents a leftward step (-1 to the x coordinate)
     * dir = 3 represents an upward step (-1 to the y coordinate)
     */
    for (size_t i = 0; i < solution.size(); i++) {
        if (solution[i] == 0) {
            for (int k = x; k <= x + 10; k++) {
                cs225::HSLAPixel& pixel1 = maze -> getPixel(k, y);
                pixel1 = cs225::HSLAPixel(red);
            }
            x += 10;
        } else if (solution[i] == 1) {
            for (int k1 = y; k1 <= y + 10; k1++) {
                cs225::HSLAPixel& pixel3 = maze -> getPixel(x, k1);
                pixel3 = cs225::HSLAPixel(red);
            }
            y += 10;
        } else if (solution[i] == 2) {
            for (int k2 = x; k2 >= x - 10; k2--) {
                cs225::HSLAPixel& pixel3 = maze -> getPixel(k2, y);
                pixel3 = cs225::HSLAPixel(red);
            }
            x -= 10;
        } else {
            for (int k3 = y; k3 >= y - 10; k3--) {
                cs225::HSLAPixel& pixel4 = maze -> getPixel(x, k3);
                pixel4 = cs225::HSLAPixel(red);
            }
            y -= 10;
        }
    }
    /**
     * Make the exit by undoing the bottom wall of the destination square: call the 
     * destination maze coordinates (x,y), and whiten the pixels with coordinates 
     * (x*10+k, (y+1)*10) for k from 1 to 9.
     */
    for (int k4 = 1; k4 <= 9; k4++) {
        cs225::HSLAPixel& pixel5 = maze -> getPixel(exit_x * 10 + k4, (exit_y + 1) * 10);
        pixel5.l = 1;
    }
    return maze;
}