#include "core.h"
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> Sorting::cas (std::vector<int>& arr, int i , int j){
    if (arr[j] < arr[i])
        std::swap(arr[j],arr[i]);
        return arr;
}


std::vector<int> Sorting::multiCas (std::vector<int> & arr, std::vector<int> swap){
    for (unsigned long i = 0; i <swap.size()-1 ; i+=2){
        cas(arr,swap[i],swap[i+1]);
    }
    return arr;
}

std::vector<int> Sorting::nSort (std::vector<int> & arr, std::vector<std::vector<int>> sv){
    for (unsigned long i =0 ; i <sv.size(); i ++){
        multiCas(arr,sv[i]);
    }
    return arr;
}
