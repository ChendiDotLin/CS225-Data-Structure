#ifndef _CORE_H_
#define _CORE_H_
#include <vector>

class Sorting{
    public:
        std::vector<int> cas (std::vector<int> & arr, int i, int j);
        std::vector<int> multiCas (std::vector<int> & arr, std::vector<int>swap);
        std::vector<int> nSort (std::vector<int> & arr, std::vector<std::vector<int>> sv);

};

#endif
