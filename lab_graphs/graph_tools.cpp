/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */
#include "graph_tools.h"
#include <map>
/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 * 
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
    std::map<Vertex , Vertex> parents;
    std::queue<Vertex> lalala;
    lalala.push(start);
    //make a spanning tree first
    graph.setVertexLabel(start,"VISITED");
    while (!lalala.empty()){
        Vertex node = lalala.front();
        lalala.pop();
        std::vector<Vertex> neighbors = graph.getAdjacent(node);
        for (unsigned long i = 0; i <neighbors.size(); i ++){
            if (graph.getVertexLabel(neighbors[i]).compare("VISITED")!=0){
                graph.setVertexLabel(neighbors[i],"VISITED");
                lalala.push(neighbors[i]);   
                parents[neighbors[i]] = node;
            }
        }
    }
        //go over it from th end to the start
        Vertex now = end;
        int ccc = 0;
        while(now!=start){
            Vertex dad = parents[now];
            graph.setEdgeLabel(dad,now,"MINPATH");
            now = dad;
            ccc++;
        }
        return ccc;

}
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
    Vertex start = graph.getStartingVertex();
    std::queue<Vertex> haha;
    haha.push(start);
    Vertex ehh = graph.getAdjacent(start)[0];
    int min = graph.getEdgeWeight(start,ehh);
    Vertex head = start;
    Vertex tail = ehh;
    graph.setVertexLabel(start,"VISITED");
    while (!haha.empty()){
        Vertex now = haha.front();
        haha.pop();
        std::vector <Vertex> neighbors = graph.getAdjacent(now);
        for (unsigned long i = 0; i < neighbors.size(); i ++){
            if (graph.getVertexLabel(neighbors[i]).compare("VISITED")!= 0){
                graph.setEdgeLabel(now,neighbors[i],"VISITED");
                graph.setVertexLabel(neighbors[i],"VISITED");
                haha.push(neighbors[i]);
                if (graph.getEdgeWeight(now,neighbors[i])<min){
                    min = graph.getEdgeWeight(now,neighbors[i]);
                    head = now;
                    tail = neighbors[i];
                }
            }
            else if (graph.getEdgeLabel(now,neighbors[i]).compare("VISITED")!=0 &&graph.getEdgeLabel(neighbors[i],now).compare("VISITED")!=0){
                graph.setEdgeLabel(now,neighbors[i],"VISITED"); 
                if (graph.getEdgeWeight(now,neighbors[i])<min){
                    min = graph.getEdgeWeight(now,neighbors[i]);
                    head = now;
                    tail = neighbors[i];}
                    }
        }

    }
    graph.setEdgeLabel(head,tail,"MIN");
    return min;

}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
    std::vector<Vertex> ver = graph.getVertices();
    std::vector<Edge> edg = graph.getEdges();
    DisjointSets cycle;
    cycle.addelements(ver.size());
    std::map<Vertex,int> reverse;
    for (unsigned long i = 0; i <ver.size(); i ++){
        reverse[ver[i]] = i;
    }
    std::sort (edg.begin(),edg.end());
    unsigned long counter = 0;
    int i = 0;
    while (counter< ver.size() - 1){
        Vertex haha = edg[i].source;
        Vertex hehe = edg[i].dest;
        if (cycle.find(reverse[haha])!=cycle.find(reverse[hehe])){
            graph.setEdgeLabel(haha,hehe,"MST");
            cycle.setunion(reverse[haha],reverse[hehe]);
            counter++;
        }
        i++;
}
}
