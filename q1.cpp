#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits> //biblioteca que define limites para tipos num
#include <list>
#include <algorithm>

using namespace std;

//grafo representado por int e vetor de inteiros
//como deixar esse tipo genérico? //TODO
//haverá complicações se isso for feito refatoramento?

using Graph = std::unordered_map<string, std::vector<string>>;

#define WHITE 1
#define GRAY 2
#define BLACK 3

//funcão que ler o grafo de um arquivo
//vou fazer ele receber um buffer e ele trabalha em cima disso //TODO

std::unordered_map<string, int> color;
std::unordered_map<string, int> dist;
std::unordered_map<string, string> parent;
std::unordered_map<string, int> gTime;

int timeG;
bool existe;


void printGraph(const Graph& G) {
    for(auto it = G.begin(); it != G.end(); ++it) {
        std::cout << "[" << it->first << "] : ";
        for(const string& neighbor : it->second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

void bfs(const Graph& G, string s) {
    for(auto it = G.begin(); it != G.end(); ++it) {
        color[it->first] = WHITE;
        parent[it->first] = -1;
        dist[it->first] = std::numeric_limits<int>::max();
    }
    dist[s] = 0;
    color[s] = GRAY;
    std::queue<string> Q;
    Q.push(s);
    while(!Q.empty()) {
        string u = Q.front();
        Q.pop();
        for(const string& v : G.at(u)) {
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

void dfs_visit(const Graph& G, string root, string leaf, bool &existPath){
    if(root == leaf){
        existPath = true;
        return;
    }

    color [root] = GRAY;
    vector<string> vizinhos = G.at(root);
    for(auto it = vizinhos.begin(); it != vizinhos.end(); ++it ){
        /*if(auto et = it->second.begin(); et != it->second.end(); ++et){
            if(et == u) vizinho = true;
        }*/

        if(color.at(*it) == WHITE){
            dfs_visit(G, *it, leaf, existPath);
        }
    }

    color[root] = BLACK;

    gTime[root] = timeG;
}

bool dfs(const Graph & G, string root, string leaf){
    for(auto it = G.begin(); it!= G.end(); ++it){
        color[it->first] = WHITE;
    }
    timeG = 0;
    bool existPath = false;
    dfs_visit(G, root, leaf, existPath);
    return existPath;
}

//TODO agora como uso isso para verificar se um caminho existe?

int main() {
    Graph G;

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){

        string key;
        cin >> key;
        G[key];
    }

    cin >> n;

    for(int i = 0; i < n; i++){
        string key;
        string key2;

        cin >> key >> key2;

        G[key].push_back(key2);
        G[key2].push_back(key);
    }
    
    cin >> n;

    vector<pair<string, string>> paths;

    for(int i = 0; i < n; i++){
        string key;
        string key2;

        cin >> key >> key2;

        paths.push_back({key, key2});
    }

    for(auto& node : paths){
        if(dfs(G, node.first, node.second)){
            cout << "true " << node.first << " " << node.second << endl;
        }else{
            cout << "false " << node.first << " " << node.second << endl;
        }
    }
   

    return 0;
}