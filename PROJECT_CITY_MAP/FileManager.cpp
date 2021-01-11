//
//  FileManager.cpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 31.12.20.
//

#include "FileManager.hpp"
void FileManager:: setFileName(const std::string& name){
    this->name=name;
}
void FileManager:: setGraph(const Graph& g){
    this->graph=g;
}
void FileManager:: read(){
    
    
    std::ifstream iFile(this->name, std::ios::in);
    
    if(iFile.fail())
        throw "Error while opening this file";
    
    Graph buffer;
    //containers for the names of the verts and the lists of edges
    std::vector<std::string> graphVertex;
    std::vector<std::vector<std::pair<std::string,unsigned>>> graphEdges;
    
    while(!iFile.eof()){
        std::string str;
        getline(iFile,str);
        std::stringstream sStream(str); // works only line by line
        
        std::string vert;
        sStream>>vert;
        graphVertex.push_back(vert);
        
        std::vector<std::pair<std::string,unsigned>> edges;
        
        while(!sStream.eof()){ //manages the current line
            std::string word;
            unsigned cost;
            sStream>>word;
            sStream>>cost;
            edges.push_back(make_pair(word,cost));
        }
        graphEdges.push_back(edges);
    }
    
    for(int i=0;i< graphVertex.size(); i++){
        buffer.addVertex(graphVertex[i]);
    }
    
    for(int i=0; i< graphVertex.size(); i++){
        for(int j=0; j<graphEdges[i].size(); j++){
            buffer.addEdge(graphVertex[i], graphEdges[i][j].first, graphEdges[i][j].second);
        }
    }
    
    this->graph =buffer;
}


void FileManager:: write(){
    std::ofstream oFile(this->name, std::ios::out );
    
    if(oFile.fail())
        throw "Error while opening this file";
    
    int size = this->graph.getSize();
    for(int i=0; i<size;i++){
        oFile << graph.getVert(i).getName();
        oFile << " -> ";
        std::vector<std::pair<std::string, unsigned>> adj;
        this->graph.getSuccessors(graph.getVert(i).getName(), adj);
        for(int j=0;j<adj.size();j++){
            oFile << "(" << adj[j].first << "," << adj[j].second << ")";
        }
        oFile << std::endl;
    }
}


void FileManager:: readList(){
    std::ifstream iFile(this->list, std::ios::in);
    
    if(iFile.fail())
        throw "Error while opening this file";
    
    std::vector< std::pair< std::string,std::string>> temp;
    while(!iFile.eof()){
        std::string s1;
        std::string s2;
        iFile >> s1;
        iFile >> s2;
        
        temp.push_back(std::make_pair(s1, s2));
    }
    this->banned = temp;
}
void FileManager:: writeList(){
    std::ofstream oFile(this->list, std::ios::out );
    
    if(oFile.fail())
        throw "Error while opening this file";
    
    oFile << "Banned List: " << std::endl;
    int size = banned.size();
    for(int i=0;i<size;i++){
        oFile << "(" << banned[i].first << "<->" << banned[i].second << ")"<<std::endl;
    }
}

Graph& FileManager:: getGraph(){
    return this->graph;
}
