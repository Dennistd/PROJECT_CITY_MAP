//
//  FileManager.hpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 31.12.20.
//

#ifndef FileManager_hpp
#define FileManager_hpp
#include "Graph.hpp"
#include <fstream>
#include <istream>
#include <sstream>

#include <stdio.h>

/// Class for interacting with a graph and a text file
///
/// Reads from and writes into a file
class FileManager{
    std::string name; //name of the working file
    std::string list; //name of the file with the list
    Graph graph; //current graph
    std::vector< std::pair< std::string,std::string>> banned; //list of closed streets selected by the user
    
    
public:
    //setters
    void setFileName(const std::string& name);
    void setGraph(const Graph& g);
    
    void read(); //gets the graph from a text file
    void write(); //put the graph into a text file as an adjecency list format
    void readList(); //gets the closed list from a file by name
    void writeList();//puts the list into a file
    
    Graph& getGraph(); //allows to interact with graph
};

#endif /* FileManager_hpp */
