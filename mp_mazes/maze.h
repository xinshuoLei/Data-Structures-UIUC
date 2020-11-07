/* Your code here! */
#pragma once
#include <vector>
#include "maze.h"
#include "cs225/PNG.h"

class SquareMaze {
    public:
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        cs225::PNG* drawMaze() const;
        cs225::PNG* drawMazeWithSolution();
};
