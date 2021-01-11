//
//  Edge.cpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 22.12.20.
//

#include "Edge.hpp"


void ListElem:: add(const Edge& item){
    edges.push_back(item);
}

ListElem:: ListElem(): edges(std::list<Edge>()), vert(std::string()){}

unsigned Edge:: getCost()const{
    return cost;
}
std::string Edge:: getStreet()const{
    return street;
}

std::string ListElem:: getName() const{
    return vert;
}
std::list<Edge>& ListElem:: getEdges(){
    return edges;
}

const std::list<Edge>& ListElem:: getEdges() const{
    return edges;
}
