/* Your code here! */
#pragma once
#include <vector>
#include "maze.h"
#include "cs225/PNG.h"
#include "dsets.h"

class SquareMaze {
    public:
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        cs225::PNG* drawMaze() const;
        cs225::PNG* drawMazeWithSolution();
    private:
        /**
         * 2d array of cells, each cell has two bool for right and down walls
         * 0 is for right and 1 is for down
        */
        std::vector<std::vector<std::vector<bool>>> walls;
        int width_;
        int height_;
        int exit_x;
        int exit_y;
};
