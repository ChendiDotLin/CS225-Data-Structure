/* Your code here! */
#include "dsets.h"
#include <iostream>
using std::cout;
using std::endl;

void DisjointSets::addelements(int  a)
{
    for (int i = 0; i <a; i++)
        elems.push_back(-1);
}


int DisjointSets::find(int a)
{   
    if(elems[a] < 0)
        return a;
    else
        return (elems[a] = find(elems[a]));
                }

void DisjointSets::setunion(int i , int j)
{
    int a = find(i);
    int b = find(j);
    int size = elems[a] + elems[b];
    if ( elems[a] <= elems[b]){
        elems[b] = a;
        elems[a] = size;
    }
    else {
        elems[a] = b;
        elems[b] = size;
        }
    }
        

