#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits> //biblioteca que define limites para tipos num
#include <list>
#include <algorithm>
#include <iterator>

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

std::unordered_map<int, int> comp;
int tempoG;

void printGraph(const Graph& G) {
    for(auto it = G.begin(); it != G.end(); ++it) {
        std::cout << "[" << it->first << "] : ";
        for(const int& neighbor : it->second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

bool biparticao_bfs(const Graph& G, int s) {

    //inicializa o grafo
    for(auto it = G.begin(); it != G.end(); ++it) {
        color[it->first] = WHITE;
        parent[it->first] = -1;
        dist[it->first] = std::numeric_limits<int>::max();
    }

    color[s] = GRAY;
    std::queue<int> Q;
    Q.push(s);
    unordered_map<int, int> biparticao;

    biparticao[s] = 0;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(const int& v : G.at(u)) {
            if(color[v] == WHITE) {
                parent[v] = u;
                color[v] = GRAY;
                Q.push(v);
                //vizinho nao foi visitado
                if(biparticao.at(u)==0){
                    //atribui cor oposta do atual
                    biparticao[v] = 1;
                }else{
                    biparticao[v] = 0;
                }
            }else{
                if(biparticao[u]==biparticao[v]){
                    return false;
                }
            }
        }
        color[u] = BLACK;
    }

    return true;
}


int main() {
    int n = 1;

    Graph G;
    vector<string> respostas;

    cin >> n;
    while(n!= 0){
        
        int k, j;

        cin >> k >> j;

        while(k != 0 || j != 0){
            G[k].push_back(j);
            G[j].push_back(k);
            
            cin >> k >> j;
        }
        //para todos vertices do grafo



        
        if(biparticao_bfs(G, G.begin()->first)){
            respostas.push_back("NAO");
        }else{
            respostas.push_back("SIM");
        }
        G.clear();
        cin >> n;

    }

    for(auto& node : respostas){
        cout << node << endl;
    }
    /*
    para todo vertice do grafo
    verifico os seus vizinhos
    agora verifiico se dentre dos vizinhos dos vizinhos
    eu consigo chegar nos vizinhos desse vertice
    exemplo
    0 : 1, 2, 3
    1 : 6, 9
    2 : 4, 5
    3 : 7, 8
    Nesse caso eu não consigo chegar nem em 1 e nem 3 a partir de 2
    o meso vale para 1 e 3
    o que significa que não há formação triangular
    o que necessitaria de mais de duas cores (3+)*/

    return 0;
}