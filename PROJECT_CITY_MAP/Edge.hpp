//
//  Edge.hpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 22.12.20.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <list>

/// Class for the edge street
///
/// Has the cost and the end crossroat of an edge in the graph
class Edge{
    unsigned cost;
    std::string street;
    
public:
    Edge(std::string name, unsigned cost) : cost(cost), street(name){}
    Edge(std::pair <std::string, unsigned> pair) : street(pair.first), cost(pair.second){}
    
    //getters
    unsigned getCost() const;
    std::string getStreet() const;
};


/// Class that has the name of the name of the crossroad and a list of the streets going out of it
class ListElem{
    std::string vert;
    std::list<Edge> edges;
    
public:
    ListElem();
    ListElem(std::string vert): vert(vert){
        edges = std::list<Edge>();
    }
    void add(const Edge& item);
    
    //getters
    std::string getName() const;
    const std::list<Edge>& getEdges() const;
    std::list<Edge>& getEdges();
    
};


#endif /* Edge_hpp */
