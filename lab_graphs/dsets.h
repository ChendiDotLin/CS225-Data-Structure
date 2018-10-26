/* Your code here! */
#ifndef _DISJOINTSETS_H_
#define _DISJOINTSETS_H_

#include <vector>
class DisjointSets{
    public:
        void addelements(int a);
        int find (int a );
        void setunion(int  a, int b );
    private:
        std::vector<int> elems;


};

#endif
