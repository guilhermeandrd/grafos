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

using namespace std;

using Graph = std::unordered_map<string, std::vector<string>>;
#define WHITE 1
#define GRAY 2
#define BLACK 3


/*
ou um map não ordenado*/

struct aresta{
    string at1;

    string at2;

};


void printGraph(const Graph& G) {
    for (auto it = G.begin(); it != G.end(); ++it) {
        std::cout << "[" << it->first << "] : ";
        for (const string& neighbor : it->second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

void bfs(const Graph& G, string s, unordered_map<string, int> & dist) {
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
              
            }
        }
        color[u] = BLACK;
    }

}

//TODO guardar tudo em um vetor
//TODO ordenar o vetor por ordem alfabética dos nomes

int main() {

    Graph G;

    //arestas de G
    map<pair<string, string>, string> g_arestas;


    ifstream arquivo("filmes.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo 'entrada.txt'" << endl;
        return 1;
    }

    string linha;

    while(getline(arquivo, linha)){

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
        
        g_arestas[{key_ator2, key_ator}] = key_film;
        g_arestas[{key_ator, key_ator2}] = key_film;
    }

    arquivo.close();

    unordered_map<string, int> dist;

    bfs(G, "Kevin Bacon", dist);

    for(auto it = dist.begin(); it != dist.end(); ++it) {
        cout << "esse ator: " << it->first <<" esta a " << it->second << " bacons" << endl;
    }

    for(auto& node : g_arestas){
        cout << "filme: " << node.second << " ator 1 : " << node.first.first << " ator 2 : " << node.first.second << endl;
    }

    printGraph(G); 
    return 0;
}