//
//  Graph.cpp
//  PROJECT City map
//
//  Created by Dennis Dimitrov on 22.12.20.
//

#include "Graph.hpp"
//default constructors that may not be used
Graph:: Graph(): vertexCount(0), g(std::vector<ListElem>()){}
Graph:: Graph(int n): vertexCount(n), g(std::vector<ListElem>(n)){}


int Graph:: getSize()const{
    return g.size();
}

ListElem& Graph:: getVert(const std::string& name){ //O(n)
    for(int i=0; i<g.size(); i++){
        if(g[i].getName() == name)
            return g[i];
    }
    throw "There is no street with such name";
}
ListElem& Graph:: getVert(int index){
    if(index<0 || index>vertexCount)
        throw "Invalid Index";
    
    return g[index];
}

const ListElem& Graph:: getVert(const std::string& name)const{
    for(int i=0; i<g.size(); i++){
        if(g[i].getName() == name)
            return g[i];
    }
    throw "There is no street with such name";
}
const ListElem& Graph:: getVert(int index)const{
    if(index<0 || index>vertexCount)
        throw "Invalid Index";
    
    return g[index];
}


int Graph:: getVertIndex(std::string name) const{
    for(int i=0; i< vertexCount; i++){
        if(g[i].getName() == name)
            return i;
    }
    return -1;
}
bool Graph::existsVertex(std::string vertex) const{
    
    return getVertIndex(vertex) != -1;
}


int Graph::addVertex() //O(1)
{
    g.push_back(ListElem());
    vertexCount++;
    return g.size() - 1;
}

int Graph:: addVertex(const std::string& name){
    g.push_back(ListElem(name));
    vertexCount++;
    return g.size() -1;
}


void Graph:: addEdge(std::string start, std::string end, unsigned cost){
    if (!existsVertex(start) || !existsVertex(end))
        throw "Invalid vertices!";
    if(start == end)
        throw "Street can't start and end in the same crossroad!";
    if(cost < 1)
        throw "Not a valid street length!";
    
    g[getVertIndex(start)].getEdges().push_back(Edge(end,cost));
}
void Graph:: removeEdge(std::string start, std::string end){
    if (!existsVertex(start) || !existsVertex(end))
        throw "Invalid vertices!";
    
    
    for(auto it = g[getVertIndex(start)].getEdges().begin(); it != g[getVertIndex(start)].getEdges().end(); it++){
        if(it->getStreet() == end)
            it = g[getVertIndex(start)].getEdges().erase(it);
    }
}

void Graph:: getSuccessors(std::string vertex, std::vector<std::pair<std::string, unsigned>>& vertexAdj) const{ //O(d)
    if (!existsVertex(vertex))
        throw "Invalid vertex!";
    
    for(auto it = g[getVertIndex(vertex)].getEdges().begin(); it != g[getVertIndex(vertex)].getEdges().end(); it++){
        vertexAdj.push_back(std::make_pair(it->getStreet(), it->getCost()));
    }
}

std::vector<std::pair<std::string, unsigned>> Graph:: getSuccessors(std::string vertex){
    if (!existsVertex(vertex))
        throw "Invalid vertex!";
    std::vector<std::pair<std::string, unsigned>> result;
    for(auto it = g[getVertIndex(vertex)].getEdges().begin(); it != g[getVertIndex(vertex)].getEdges().end(); it++){
        result.push_back(std::make_pair(it->getStreet(), it->getCost()));
    }
    return result;
}

int Graph:: getVertexCount() const{
    return vertexCount;
}


void BFS (Graph& g, std::string start){
    
    if(!g.existsVertex(start))
        return;
    
    std::vector<bool> visited(g.getVertexCount());
    
    std::queue<std::string> q;
    q.push(start);
    visited[g.getVertIndex(start)] = true;
    
    while(!q.empty()){
        std::string current = q.front();
        q.pop();
        
        std::cout << current << std::endl;
        
        std::vector<std::pair<std::string, unsigned>> adj;
        g.getSuccessors(current, adj);
        
        for(int i =0; i < adj.size(); i++){
            int index = g.getVertIndex(adj[i].first);
            if(visited[index])
                continue;
            visited[index] = true;
            q.push(adj[i].first);
        }
    }
}

void DFS (Graph& g, std::string start){
    std::vector<bool> visited(g.getVertexCount());
    
    std::stack<std::string> s;
    s.push(start);
    
    while(!s.empty()){
        std::string current = s.top();
        int currentIndex = g.getVertIndex(current);
        s.pop();
        
        if(visited[currentIndex])
            continue;
        visited[currentIndex] = true;
        std::cout << current << std::endl;
        
        std::vector<std::pair<std::string, unsigned>> adj;
        g.getSuccessors(current, adj);
        for (int i = 0; i < adj.size(); i++)
        s.push(adj[i].first);
    }
}

//1.
bool existsPath(const Graph& g, const std::string& start, const std::string& end){
    if(start == end)
        return true;
    
    std::vector<bool> visited(g.getVertexCount());
    
    std::queue<std::string> q;
    q.push(start);
    visited[g.getVertIndex(start)] = true;
    
    while(!q.empty()){
        std::string current = q.front();
        q.pop();
        
        
        std::vector<std::pair<std::string, unsigned>> adj;
        g.getSuccessors(current, adj);
        
        for(int i =0; i < adj.size(); i++){
            int index = g.getVertIndex(adj[i].first);
            
            if(adj[i].first == end)
                return true;
            
            if(visited[index]) 
                continue;
            visited[index] = true;
            q.push(adj[i].first);
        }
    }
    return false;
}




void Graph:: printPath(std::vector<int> prev, int start, int end, std::vector<std::string>& path)const{
    while(end != start){
        path.push_back(g[end].getName());
        std::cout << g[end].getName() << "<-";
        end = prev[end];
    }
    path.push_back(g[start].getName());
    std::cout << g[start].getName();
    std::cout << std::endl;
}


void Dijkstra(const Graph& graph, std::string start, std::string dest, std::vector<std::string>& path){
    struct Tuple{
        int index;
        int distFromStart;
        Tuple(int index, int distFromStart): index(index), distFromStart(distFromStart) {}
        bool operator< (const Tuple& other)const{
            return (this->distFromStart > other.distFromStart);
        }
    };
    
    if(!graph.existsVertex(start))
        throw "There is no such start";
    
    if(!graph.existsVertex(dest))
        throw "There is no such destination";
    
    int size = graph.getSize();
    std::vector<unsigned> dist(size);
    std::vector<int> prev(size);
    
    for(int i =0; i<size; i++){
        dist[i] = INT_MAX;
        prev[i] = INT_MAX;
    }
    
    int s = graph.getVertIndex(start);
    int d = graph.getVertIndex(dest);
    dist[s] = 0;
    std::priority_queue<Tuple> q;
    q.push(Tuple(s,0));
    
    while(!q.empty()){
        Tuple current = q.top();
        q.pop();
        
        if(current.index == d){
            graph.printPath(prev, s, d, path);
        }
        int currIndex = current.index;
        int distToCurr = current.distFromStart;
        std::vector<std::pair<std::string, unsigned>> adj;
        graph.getSuccessors(graph.getVert(currIndex).getName(), adj);
        for(int i=0;i< adj.size(); i++){
            std::string newDest = adj[i].first;
            int newDestIndex = graph.getVertIndex(newDest);
            int newDist = distToCurr + adj[i].second;
            
            if(newDist < dist[newDestIndex]){
                dist[newDestIndex] = newDist;
                q.push(Tuple(newDestIndex,newDist));
                prev[newDestIndex] = currIndex;
            }
        }
        
        
    }
    std::reverse(path.begin(), path.end());
}


std::vector<std::vector<std::string>> EppsteinSP (const Graph& graph, std::string start, std::string dest){
   // int s = graph.getVertIndex(start);
    int t = graph.getVertIndex(dest);
    
    struct Path{ //struct that contains a given path and its cost
        std::vector< std::pair<std::string,std::string>> path;
        unsigned cost;
        Path(const std::vector< std::pair<std::string,std::string>>& path, unsigned cost): path(path), cost(cost){}
        int getIndex(Graph graph){ return graph.getVertIndex(path[path.size()-1].second); }
        bool operator< (const Path& other)const{
            return (this->cost > other.cost);
        }
        void print(std::vector<std::string>& result){
            for(int i=0; i<path.size();i++){
                result.push_back(path[i].second);
            }
        }
        
    };
    
    std::vector<Path> result;
    std::vector<int> count(graph.getSize(),0);
    std::vector<std::vector<std::string>> P;
    std::priority_queue<Path> B;
    
    std::vector< std::pair<std::string,std::string> > starting;
    starting.push_back(std::make_pair(start,start));
    B.push(Path(starting,0));
    
    
    while(!B.empty() && count[t]<COUNT_PATH){
        Path current = B.top();
        B.pop();
        int c = current.cost;
        int u = current.getIndex(graph);
        count[u]++;
        
        if(u == t)
            result.push_back(current);
        
        if(count[u]<=COUNT_PATH){
            std::vector<std::pair<std::string, unsigned>> vertexAdj;
            std::string uNode = graph.getVert(u).getName();
            graph.getSuccessors(uNode, vertexAdj);
            
            for(int i=0; i<vertexAdj.size(); i++){
                std::vector< std::pair<std::string,std::string>> newPath(current.path);
                newPath.push_back(std::make_pair(uNode, vertexAdj[i].first));
                int newCost = c + vertexAdj[i].second;
                Path Pv(newPath,newCost);
                B.push(Pv);
            }
        }
        
    }
    for(int i=0 ;i< result.size(); i++){
        std::vector<std::string> temp;
        result[i].print(temp);
        P.push_back(temp);
    }
    return P;
}

//3
std::vector<std::vector<std::string>> EppsteinSPList (const Graph& graph, std::string start, std::string dest,const std::vector< std::pair< std::string,std::string> >& banned){
    Graph temp = graph;
    std::vector<std::vector<std::string>> result;
    
    int size = banned.size();
    for(int i=0; i<size; i++){
        temp.removeEdge(banned[i].first, banned[i].second);
    }
    result  = EppsteinSP(temp, start, dest);
    return result;
}


bool Graph:: hasCycle (std::string start, std::vector<bool>& visited, std::vector<bool>& recstack)const{
    int s = getVertIndex(start);
    if(!visited[s]){
        visited[s] = true;
        recstack[s] = true;
        
        std::vector<std::pair<std::string, unsigned>> vertexAdj;
        getSuccessors(start, vertexAdj);
        for(int i =0 ;i<vertexAdj.size(); i++){
            std::string currName = vertexAdj[i].first;
            int currIndex = getVertIndex(currName);
            if(!visited[currIndex] && hasCycle(currName, visited, recstack))
                return true;
            else if(recstack[currIndex])
                return true;
        }
    }
    recstack[s] = false;
    return false;
}

bool hasCycleFrom(const Graph& graph, std::string start){
    std::vector<bool> visited(graph.getSize());
    std::vector<bool> stackRec(graph.getSize());
    
    for(int i =0 ;i < graph.getSize(); i++){
        visited[i] = stackRec[i] = false;
    }
    
    return graph.hasCycle(start, visited, stackRec);
}


int Graph:: outDegrees(int vert)const{
    return getVert(vert).getEdges().size();
}

int Graph:: outDegrees(std::string str)const{
    return getVert(str).getEdges().size();
}

int Graph:: inDegrees(int vert)const{
    int count =0;
    std::string end = getVert(vert).getName();
    
    for(int i =0;i < vertexCount; i++){
        std::vector<std::pair<std::string, unsigned>> vertexAdj;
        getSuccessors(getVert(i).getName(), vertexAdj);
        for(int j=0; j<vertexAdj.size();j++){
            if(end == vertexAdj[j].first)
                count++;
        }
    }
    return count;
}

int Graph:: inDegrees(std::string str)const{
    int count =0;
    for(int i =0;i < vertexCount; i++){
        std::vector<std::pair<std::string, unsigned>> vertexAdj;
        getSuccessors(getVert(i).getName(), vertexAdj);
        for(int j=0; j<vertexAdj.size();j++){
            if(str == vertexAdj[j].first)
                count++;
        }
    }
    return count;
}

bool Graph:: allSameDegrees()const{
    for(int i =0;i<vertexCount;i++){
        if(inDegrees(i) != outDegrees(i))
            return false;
    }
    return true;
}

bool Graph:: has2Diff(){
    int count=0;
    int rest =0;
    for(int i=0;i<vertexCount; i++){
        if(inDegrees(i)==1+outDegrees(i) || outDegrees(i)==inDegrees(i)+1){
            count++;
        }
        else if(inDegrees(i)==outDegrees(i)){
            rest++;
        }
        if(count > 2 || rest> vertexCount-2){
            return false;
        }
    }
    return true;
}

Graph Graph:: getTranspose(){
    Graph g(vertexCount);
    for(int i=0 ;i<vertexCount;i++){
        g.addVertex(getVert(i).getName());
    }
    for(int i = 0; i< vertexCount; i++){
        for(auto it = getVert(i).getEdges().begin(); it != getVert(i).getEdges().end(); it++)
        g.addEdge(it->getStreet(), getVert(i).getName());
    }
    return g;
}
void Graph:: visitedBFS(int index, std::vector<bool>& visited){
    std::queue<int> q;
    visited[index] = true;
    q.push(index);
    
    while(!q.empty()){
        index = q.front();
        q.pop();
        
        for(auto it = getVert(index).getEdges().begin(); it != getVert(index).getEdges().end(); it++){
            int i = getVertIndex(it->getStreet());
            
            if(!visited[i]){
                visited[i]=true;
                q.push(i);
            }
            
        }
    }
    
}
bool Graph:: stronglyConnected(){
    std::vector<bool> visited(vertexCount,false);
    visitedBFS(0, visited);
    
    for(int i =0;i<visited.size(); i++){
        if(!visited[i])
            return false;
    }
    
    for(int i=0;i<visited.size();i++){
        visited[i] = false;
    }
    
    Graph graph = getTranspose();
    graph.visitedBFS(0, visited);
    
    for(int i =0;i<visited.size(); i++){
        if(!visited[i])
            return false;
    }
    
    return true;
}

bool Graph:: hasEulerianPath(std::string name)const{
    int index = getVertIndex(name);
    
    //    if(!stronglyConnected())
    //        return false;
    
    if(allSameDegrees())
        return true;
    if(inDegrees(index)+1==outDegrees(index)){
        int count =0;
        if(count >1)
            return false;
        for(int i=0;i<vertexCount;i++){
            
            if(inDegrees(i)==outDegrees(1))
                continue;
            
            else if(inDegrees(i)==outDegrees(i)+1)
                count++;
            else if(inDegrees(i)>outDegrees(i)+1 || outDegrees(i)>inDegrees(i)+1)
                return false;
            
        }
        
    }
    return true;
}

//6.

void Graph:: visitedDFS(std::string name,std::vector<bool>& visited)const{
    int index = getVertIndex(name);
    if(visited[index])
        return;
    visited[index] = true;
    std::vector<std::pair<std::string, unsigned>> vertexAdj;
    getSuccessors(name, vertexAdj);
    for(int i=0; i< vertexAdj.size(); i++){
        visitedDFS(vertexAdj[i].first, visited);
    }
}
bool canReachAll(const Graph& graph, const std::string& start){
    // int s = graph.getVertIndex(start);
    std::vector<bool> visited(graph.getVertexCount(), false);
    graph.visitedDFS(start, visited);
    
    for(int i =0; i< visited.size(); i++){
        if(!visited[i]){
            return false;
        }
    }
    return true;
}


std::vector<std::string> getEulerianPath(const Graph& graph, const std::string& start){
    Graph temp = graph;
    std::stack<std::string> s;
    std::vector<std::string> result;
    
    if(!graph.hasEulerianPath(start))
        throw "Can't find such path!";
    
    std::string curr = start;
    
    while(!temp.getSuccessors(curr).empty() && !s.empty()){
        std::vector<std::pair<std::string, unsigned>> neighbors = temp.getSuccessors(curr);
        if(neighbors.empty()){
            result.push_back(curr);
            curr = s.top();
            s.pop();
        }
        else{
            s.push(curr);
            std::string next = neighbors[0].first;
            temp.removeEdge(curr, next);
            curr = next;
        }
    }
    std::reverse(result.begin(), result.end()); //so the path is in the correbt order
    return result;
}

std::vector<std::string> getOneWayStreets(const Graph& graph){
    std::vector<std::string> result;
    for(int i=0;i<graph.getSize();i++){
        if(graph.inDegrees(i)==1 && graph.outDegrees(i)==0){
            result.push_back(graph.getVert(i).getName());
        }
    }
    return result;
}

std::vector<std::string> EulerianPath(const Graph& graph, const std::string& start){
    Graph temp = graph;
    std::stack<std::string> st;
    std::vector<std::string> result;
    
    if(!graph.hasEulerianPath(start))
        throw "Can't find such path!";
    
    st.push(start);
    
    while(!st.empty()){
        std::string curr = st.top();
        
        if(temp.outDegrees(curr)==0){
            result.push_back(curr);
            st.pop();
        }
        else{
            std::vector<std::pair<std::string, unsigned>> adj;
            temp.getSuccessors(curr,adj);
            std::string currEnd = adj[0].first;
            temp.removeEdge(curr, currEnd);
            st.push(currEnd);
        }
        
    }
    return result;
}

std::vector<std::pair<std::string,std::string>> oneWayEdge(const Graph& graph){
    std::vector<std::pair<std::string,std::string>> result;
    for(int i=0;i<graph.getSize();i++){
        std::vector<std::pair<std::string, unsigned>> adj;
        graph.getSuccessors(graph.getVert(i).getName(),adj);
        for(int j=0;j<adj.size();j++){
            if(graph.outDegrees(adj[j].first)==0){
                result.push_back(std::make_pair(graph.getVert(i).getName(), adj[j].first));
            }
        }
    }
    return result;
}
