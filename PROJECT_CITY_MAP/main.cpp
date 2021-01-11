//
//  main.cpp
//  PROJECT_CITY_MAP
//
//  Created by Dennis Dimitrov on 22.12.20.
//

#include <iostream>
#include "Graph.hpp"
#include "Interaction.hpp"

int main(int argc, const char * argv[]) {
    
    
    Graph g; //graph from the project
    g.addVertex("NDK");
    g.addVertex("5Kiosheta");
    g.addVertex("BSFS");
    g.addVertex("Popa");
    g.addVertex("FMI");
    
    g.addEdge("Popa", "BSFS",150);
    g.addEdge("Popa", "5Kiosheta", 1000);
    g.addEdge("BSFS", "Popa", 150);
    g.addEdge("5Kiosheta", "NDK",400);
    g.addEdge("NDK", "Popa",800);
    g.addEdge("FMI", "Popa",1100);
    
    //0.
    // BFS(g,"5Kiosheta");
    // DFS(g, "Popa");
    
    //1.
    std::cout<<"Task 1: "<<std::endl;
    
    std::cout<<existsPath(g, "Popa", "NDK")<<std::endl;
    std::cout<<existsPath(g, "Popa", "FMI")<<std::endl;
    
    
    //   1
    // 2   3
    // 4   5
    //   6
    
    Graph g1; //cyclic graph
    g1.addVertex("1");
    g1.addVertex("2");
    g1.addVertex("3");
    g1.addVertex("4");
    g1.addVertex("5");
    g1.addVertex("6");
    g1.addEdge("1", "2",12);
    g1.addEdge("3", "1",12);
    g1.addEdge("2", "4",912);
    g1.addEdge("4", "6",24);
    g1.addEdge("5", "3",2);
    g1.addEdge("6", "5",43);
    
    Graph g2(g1);
    g2.addVertex("7");
    Graph g3(g1);
    g3.removeEdge("6", "5");
    
    std::vector<std::string> path;
    Dijkstra(g1, "1", "6", path);
    for(int i =0; i<path.size(); i++){
        std::cout <<"("<< path[i] <<") ";
    }
    std::cout << std::endl;
    
    //2.
    std::cout<<"Task 2: "<<std::endl;
    Graph g4; //graph with different paths
    
    //     1
    //  /  |  \  \
    //  2  3  4  5
    //  |  |  |  |
    //  6  7  8  9
    //  |  |  |  |
    // 10  11 12 13
    //  \  \  /  /
    //      14
    
    g4.addVertex("1");
    g4.addVertex("2");
    g4.addVertex("3");
    g4.addVertex("4");
    g4.addVertex("5");
    g4.addVertex("6");
    g4.addVertex("7");
    g4.addVertex("8");
    g4.addVertex("9");
    g4.addVertex("10");
    g4.addVertex("11");
    g4.addVertex("12");
    g4.addVertex("13");
    g4.addVertex("14");
    g4.addEdge("1", "2", 1);
    g4.addEdge("2", "6", 2);
    g4.addEdge("6", "10", 3);
    g4.addEdge("10", "14", 4);
    g4.addEdge("1", "3", 5);
    g4.addEdge("3", "7", 6);
    g4.addEdge("7", "11", 7);
    g4.addEdge("11", "14", 8);
    g4.addEdge("1", "4", 9);
    g4.addEdge("4", "8", 10);
    g4.addEdge("8", "12", 11);
    g4.addEdge("12", "14", 12897);
    g4.addEdge("1", "5", 11);
    g4.addEdge("5", "9", 1);
    g4.addEdge("9", "13", 1);
    g4.addEdge("13", "14", 1);
    
    std:: vector<std::vector<std::string>> s;
    s = EppsteinSP (g4, "1", "14");
    
    for(int i =0 ;i< s.size(); i++){
        for(int j=0;j<s[i].size();j++){
            std::cout<<"("<<s[i][j]<<")";
        }
        std::cout<<std::endl;
    }
    
    
    //3.
    std::cout<<"Task 3: "<<std::endl;
    std::vector< std::pair< std::string,std::string> > banned;
    
    //    banned.push_back(std::make_pair("12", "14"));
    //    banned.push_back(std::make_pair("8", "12"));
    
    banned.push_back(std::make_pair("1", "2"));
    banned.push_back(std::make_pair("2", "6"));
    
    std:: vector<std::vector<std::string>> s2;
    s2 = EppsteinSPList(g4, "1", "14", banned);
    
    for(int i =0 ;i< s2.size(); i++){
        for(int j=0;j<s2[i].size();j++){
            std::cout<<"("<<s2[i][j]<<")";
        }
        std::cout<<std::endl;
    }
    
    //4.
    std::cout<<"Task 4: "<<std::endl;
    std::cout << hasCycleFrom(g1, "1")<<"/"<<hasCycleFrom(g3, "1")<<std::endl;
    
    //5.
    std::cout<<"Task 5: "<<std::endl;
    Graph g5;
    g5.addVertex("1");
    g5.addVertex("2");
    g5.addVertex("3");
    g5.addVertex("4");
    g5.addVertex("5");
    g5.addEdge("1", "2");
    g5.addEdge("2", "4");
    g5.addEdge("4", "3");
    g5.addEdge("3", "1");
    g5.addEdge("5", "1");
    std::vector<std::string> p = EulerianPath(g5, "5");
    if(p.empty())
        std::cout<<"Error"<<std::endl;
    
    std::cout << p[0];
    for(int i=1;i<p.size();i++){
        std::cout << "->" << p[i] ;
    }
    std::cout<<std::endl;
    
    //6.
    std::cout<<"Task 6: "<<std::endl;
    std::cout<< canReachAll(g1, "1")<<"/"<<canReachAll(g2, "1")<<std::endl;
    
    //7;
    std::cout<<"Task 7: "<<std::endl;
    Graph g6 = g5;
    g6.removeEdge("5", "1");
    g6.addVertex("6");
    g6.addEdge("1", "5");
    g6.addEdge("1", "6");
    std::vector<std::string> oneWay = getOneWayStreets(g6);
    std::vector<std::pair<std::string,std::string>> oneWayStreet = oneWayEdge(g6);
    for(int i=0;i<oneWay.size();i++){
        std::cout<<oneWay[i]<<";";
    }
    std::cout<<std::endl;
    for(int i=0; i<oneWayStreet.size(); i++){
        std::cout << "("<<oneWayStreet[i].first <<","<<oneWayStreet[i].second <<")";
    }
    std::cout<<std::endl;
    
    // Getting from file
    std::cout<<"Get from file: "<<std::endl;
    
    Graph inputed;
    FileManager f;
    f.setFileName("Input.txt");
    f.read();
    inputed = f.getGraph();
    
    //Put graph into test file
    
    FileManager m;
    m.setFileName("Output.txt");
    m.setGraph(inputed);
    m.write();
    
    BFS(inputed, "JK");
    
    
    return 0;
}
