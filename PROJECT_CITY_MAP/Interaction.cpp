//
//  Interaction.cpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 31.12.20.
//

#include "Interaction.hpp"


void InteractiveMode:: addBanned(std::pair< std::string,std::string> pair){
    banned.push_back(pair);
}
void InteractiveMode:: removeBanned(std::pair< std::string,std::string> pair){
    banned.erase(std::remove(banned.begin(), banned.end(), pair),banned.end());
}

void InteractiveMode:: setCommand(std::string command){ //checks if the command is from the given list
    if(command=="location" || command=="change" || command=="neighbours" || command=="move" || command=="close" || command=="open" || command =="closed" ||command=="tour")
        this->command = command;
}
void InteractiveMode:: setIndex(int i){
    if(i>=0 && i<graph.getSize())
        this->i =i;
}
void InteractiveMode:: setGraph(const std::string& str){
    FileManager f;
    f.setFileName(str);
    f.read();
    this->graph = f.getGraph();
}
void InteractiveMode:: setGraph(const Graph& g){
    this->graph =g;
}

InteractiveMode:: InteractiveMode(int i, const std::string& command, const std::string& fileName){
    setIndex(i);
    setGraph(fileName);
    setCommand(command);
    banned = std::vector< std::pair< std::string,std::string>>();
}

InteractiveMode:: InteractiveMode(Graph& g,int i, const std::string& command){
    setGraph(g);
    setIndex(i);
    setCommand(command);
    banned = std::vector< std::pair< std::string,std::string>>();
}


void InteractiveMode:: ExecuteCommand(){
    std::string atName = graph.getVert(i).getName();
    
    while(command != "end"){
        if(command=="location"){
            std::cout<< atName<<std::endl;
        }
        
        else if(command == "change"){
            std::string changeTo;
            std::cout<<"Enter the name ot the crossroad you want to go to"<<std::endl;
            std::cin>>changeTo;
            int indexTo = graph.getVertIndex(changeTo);
            std::cout<<"Successfully changed your location to: "<<changeTo<<" at index "<< indexTo<< std::endl;
        }
        
        else if(command == "neighbours"){
            std::vector<std::pair<std::string, unsigned>> adj;
            graph.getSuccessors(atName, adj);
            std::cout<<"Your neighbours are: "<<std::endl;
            for(int i=0;i<adj.size();i++){
                std::cout<<"("<< adj[i].first << "," << adj[i].second << ") ";
            }
            std::cout<<std::endl;
        }
        
        else if(command == "move"){
            std::string end;
            std::cout<<"Ented the end destination of your path"<<std::endl;
            std::cin>>end;
            if(!existsPath(graph, atName, end))
                std::cout<<"No such path!"<<std::endl;
            else{
                std::vector<std::string> path;
                Dijkstra(graph, atName, end, path);
                
                std::cout << "->";
                for(int i=0;i<path.size();i++){
                    std::cout<<"->"<<path[i];
                }
                std::cout<<std::endl;
            }
        }
        
        else if(command == "close"){
            std::string start;
            std::cout<<"Enter the start of the edge to be added"<<std::endl;
            std::cin>>start;
            
            std::string end;
            std::cout<<"Enter the end of the edge to be added"<<std::endl;
            std::cin>>end;
            
            if(graph.existsVertex(start) && graph.existsVertex(end))
                addBanned(make_pair(start,end));
        }
        
        else if(command == "open"){
            std::string start;
            std::cout<<"Enter the start of the edge to be opened"<<std::endl;
            std::cin>>start;
            
            std::string end;
            std::cout<<"Enter the end of the edge to be opened"<<std::endl;
            std::cin>>end;
            
            if(graph.existsVertex(start) && graph.existsVertex(end))
                removeBanned(make_pair(start,end));
        }
        else if(command == "closed"){
            std::cout << "The banned crossroads are: "<<std::endl;
            for(int i=0;i<banned.size(); i++){
                std::cout << "("<< banned[i].first<<","<<banned[i].second<<")";
            }
            std::cout<<std::endl;
        }
        else if(command == "tour"){
            for(int i=0;i<graph.getSize();i++){
                if(graph.hasEulerianPath(graph.getVert(i).getName())){
                    getEulerianPath(graph, graph.getVert(i).getName());
                }
            }
        }
        else{
            std::cout<< "Enter a valid command: "<<std::endl;
            std::string str;
            std::cin>>str;
            setCommand(str);
        }
    }
}
