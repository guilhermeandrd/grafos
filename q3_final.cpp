#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <set>
#include <map>
#include <ostream>

using namespace std;

using Graph = std::unordered_map<string, std::vector<string>>;
#define WHITE 1
#define GRAY 2
#define BLACK 3


/*
ou um map não ordenado*/
// dados
map<pair<string, string>, string> g_arestas;
unordered_map<string, int> dist;
set<pair<string, string>> saida;


void printGraph(const Graph& G) {
    for (auto it = G.begin(); it != G.end(); ++it) {
        std::cout << "[" << it->first << "] : ";
        for (const string& neighbor : it->second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

void bfs(const Graph& G, string s) {
    unordered_map<string, string> parent;
    unordered_map<string, int> color;

    //inicializa o grafo
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

                saida.insert({v, u});
            }
        }
        color[u] = BLACK;
    }

}


int main() {

    Graph G;

    //arestas de G

    string linha;

    while(getline(cin, linha)){

        if(linha.empty()) break;

        stringstream ss(linha);
        string key_ator;
        string key_film;
        string key_ator2;

        //usar 3 getlines (ator, filme, ator)
        getline(ss,key_ator, ';');
        getline(ss,key_film, ';');
        getline(ss, key_ator2, ';');

        G[key_ator].push_back(key_ator2);
        G[key_ator2].push_back(key_ator);
        
        g_arestas[{min(key_ator, key_ator2), max(key_ator, key_ator2)}] = key_film;
    }


    bfs(G, "Kevin Bacon");

    for(auto& saidas : saida){
        cout << "O numero de bacon de "<< saidas.first << " é " << dist[saidas.first] << " pelo filme " << g_arestas.at({min(saidas.first, saidas.second), max(saidas.first, saidas.second)}) << endl;
    }

    return 0;
}