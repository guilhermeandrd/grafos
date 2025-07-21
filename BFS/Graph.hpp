#include <vector>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>

#ifndef GRAPH_HPP
#define GRAPH_HPP

class Graph{
private:

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits> //biblioteca que define limites para tipos num
#include <list>

using namespace std;

//grafo representado por int e vetor de inteiros
//como deixar esse tipo genérico? //TODO
//haverá complicações se isso for feito refatoramento?
using Graph = std::unordered_map<int, std::vector<int>>;

#define WHITE 1
#define GRAY 2
#define BLACK 3

//funcão que ler o grafo de um arquivo
//vou fazer ele receber um buffer e ele trabalha em cima disso //TODO

std::unordered_map<int, int> color;
std::unordered_map<int, int> dist;
std::unordered_map<int, int> parent;
std::unordered_map<int, int> gTime;

int timeG;
bool existe;

void readUndirectedGraphFromFile(Graph& graph, const std::string& filename) {
    std::fstream file(filename);


    if(!file.is_open()) {
        std::cerr << "erro ao abrir arquivo" << std::endl;
        return;
    }


    std::string line;
    //o arquivo já tá formatado para representar grafos
    //ou não, //TODO
    //eu posso deixar a entrada do programa como um arquivo
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        int u, v;
        ss >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }


}

void printGraph(const Graph& G) {
    for(auto it = G.begin(); it != G.end(); ++it) {
        std::cout << "[" << it->first << "] : ";
        for(const int& neighbor : it->second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

void bfs(const Graph& G, int s) {
    for(auto it = G.begin(); it != G.end(); ++it) {
        color[it->first] = WHITE;
        parent[it->first] = -1;
        dist[it->first] = std::numeric_limits<int>::max();
    }
    dist[s] = 0;
    color[s] = GRAY;
    std::queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(const int& v : G.at(u)) {
            if(color[v] == WHITE) {
                parent[v] = u;
                color[v] = GRAY;
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
        color[u] = BLACK;
    }

    for(auto it = dist.begin(); it != dist.end(); ++it) {
        std::cout << "dist(" << s << "," << it->first << ") = " << it->second << std::endl; 
    }
}

/*void dfs_visit(const Graph & G, int u, int timeG){
    color[u] = GRAY;
    timeG++;
    dist[u] = timeG;
    for(auto it = G.begin(); it != G.end(); ++it) {
        if(color[it->first] == WHITE){
            parent[it->first] = u;
            dfs_visit(G, it->first, timeG);
        }
        cout << "do verticie " << u << " para " << it->first << " demorou " << timeG << endl;
    }

    color[u] = BLACK;
    timeG++;
    gTime[u] = timeG;
}

void dfs(const Graph &G){

    for(auto it = G.begin(); it != G.end(); ++it){
        color[it->first] = WHITE;
        parent[it->first] = -1;
    } 
    

    for(auto it = G.begin(); it != G.end(); ++it){
        if(color[it->first] == WHITE)
            dfs_visit(G, it->first, 0);
    }
    
}*/

void dfs_visit(const Graph& G, int root, int leaf){
    if(root == leaf) existe = true;

    color [root] = GRAY;
    std::vector<int> vizinhos = G.at(root);
    for(auto it = vizinhos.begin(); it != vizinhos.end(); ++it ){
        /*if(auto et = it->second.begin(); et != it->second.end(); ++et){
            if(et == u) vizinho = true;
        }*/

        if(color.at(*it) == WHITE){
            dfs_visit(G, *it, leaf);
        }

        std::cout << "do verticie " << root << " para " << *it << " demorou " << timeG << endl;

    }

    color[root] = BLACK;

    gTime[root] = timeG;
}

void dfs(const Graph & G, int root, int leaf){
    for(auto it = G.begin(); it!= G.end(); ++it){
        color[it->first] = WHITE;
    }
    timeG = 0;
    
    dfs_visit(G, root, leaf);
}

//TODO agora como uso isso para verificar se um caminho existe?


public:

};

#endif //END_OF_GRAPH_HPP