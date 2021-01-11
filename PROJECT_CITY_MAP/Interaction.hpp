//
//  Interaction.hpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 31.12.20.
//

#ifndef Interaction_hpp
#define Interaction_hpp

#include <stdio.h>
#include "FileManager.hpp"

/// Class for user interactin
///
/// Works with the graoh by index and string commands
class InteractiveMode{
    int i; //current index
    std::string curr;
    Graph graph;
    std::string command; //given command
    std::vector< std::pair< std::string,std::string>> banned;
    
    void addBanned(std::pair< std::string,std::string> pair);
    void removeBanned(std::pair< std::string,std::string> pair);
    
public:
    void setCommand(std::string command);
    void setIndex(int i);
    void setGraph(const std::string& str);
    void setGraph(const Graph& g);
    
    InteractiveMode(int i, const std::string& command, const std::string& fileName);
    InteractiveMode(Graph& g,int i, const std::string& command);
    void ExecuteCommand(); //executes the current command
};

#endif /* Interaction_hpp */
