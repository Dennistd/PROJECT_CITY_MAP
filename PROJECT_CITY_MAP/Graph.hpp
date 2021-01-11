//
//  Graph.hpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 22.12.20.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include "Edge.hpp"

#include <iostream>
#include <queue>
#include <stack>
#include <functional>

const size_t COUNT_PATH = 3; //the number of shortest paths

///The main class for the graph of crossroads
///
/// Represents an adjacency list 
class Graph{
    
    int vertexCount;
    
    std::vector<ListElem> g;
public:
    Graph();
    Graph(int n);
    int getSize()const;
    
    //funcs
    int addVertex(); //return the index of the new vertex
    int addVertex(const std::string& name);
    bool existsVertex (std::string vertex)const; //checks if there is a crossroad with such name
    int getVertIndex(std::string name)const;
    
    void addEdge(std::string start, std::string end, unsigned cost =1);
    void removeEdge(std::string start, std::string end);
    
    void getSuccessors(std::string vertex, std::vector<std::pair<std::string, unsigned>>& vertexAdj) const;
    std::vector<std::pair<std::string, unsigned>> getSuccessors(std::string vertex); //returns the list
    
    int getVertexCount() const;
    
    ListElem& getVert(const std::string& name); //finding a vertex by name
    const ListElem& getVert(const std::string& name)const;
    ListElem& getVert(int index); //getting vertex by index
    const ListElem& getVert(int index)const;
    
    bool hasCycle (std::string start, std::vector<bool>& visited, std::vector<bool>& recstack)const; //checks if it has a cycle recursively
    
    void printPath(std::vector<int> prev, int start, int end, std::vector<std::string>& path)const; //prints the path from a given vector of parents
    
    int outDegrees(int vert)const; //the number of outgoing edges
    int outDegrees(std::string str)const;
    int inDegrees(int vert)const; //the number of incoming edges
    int inDegrees(std::string str)const;
    bool allSameDegrees()const; //if all of the verts have the same degrees
    bool has2Diff();
    Graph getTranspose();
    bool stronglyConnected();
    void visitedBFS(int index, std::vector<bool>& visited);
    bool hasEulerianPath(std::string name)const;
    
    void visitedDFS(std::string name,std::vector<bool>& visited)const;
    
};

//0. Search in the graph
void BFS (Graph& g, std::string start);
void DFS (Graph& g, std::string start);

//1. Checks if there is a path between 2 crossroads
bool existsPath(const Graph& g, const std::string& start, const std::string& end);

//2. Finds the 3 shortest paths between crossroads
void Dijkstra(const Graph& graph, std::string start, std::string dest, std::vector<std::string>& path);
std::vector<std::vector<std::string>> EppsteinSP (const Graph& graph, std::string start, std::string dest);
//O(m + nlogn + k) k=3

//3. Finds the 3 shortest path after removing given edges
std::vector<std::vector<std::string>> EppsteinSPList (const Graph& graph, std::string start, std::string dest,const std::vector< std::pair< std::string,std::string> >& banned);

//4. Checks if there is a cycle from given crossroad
bool hasCycleFrom(const Graph& graph, std::string start);

//5. Gets a path that visits every street once
std::vector<std::string> getEulerianPath(const Graph& graph, const std::string& start); //5. O(v+e)
std::vector<std::string> EulerianPath(const Graph& graph, const std::string& start);

//6. Checks if we can go to every street from a given one
bool canReachAll(const Graph& graph, const std::string& start);

//7. Finds all the crossroads of streets what are one way
std::vector<std::pair<std::string,std::string>> oneWayStreets (const Graph& graph);
std::vector<std::string> getOneWayStreets(const Graph& graph);
std::vector<std::pair<std::string,std::string>> oneWayEdge(const Graph& graph);
//O(EV)

#endif /* Graph_hpp */
