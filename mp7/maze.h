/* Your code here! */
#include <ostream>
#include <vector>
#include "dsets.h"
#include "png.h"

class SquareMaze
{
    public:
        SquareMaze();
        void makeMaze( int width, int height);
        bool canTravel(int x, int y , int dir) const;
        void setWall( int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
    
    private:
        DisjointSets cycle;
        int w;
        int h;
        std::vector< std::pair<bool,bool> > table;
};
