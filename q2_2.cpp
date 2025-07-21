#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <fstream> // Essencial para arquivos
#include <sstream>
#include <queue>
#include <limits>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

using Graph = std::unordered_map<int, std::vector<int>>;

#define WHITE 1
#define GRAY 2
#define BLACK 3

// Suas variáveis globais e funções originais (INALTERADAS)
std::unordered_map<int, int> color;
std::unordered_map<int, int> dist;
std::unordered_map<int, int> parent;
std::unordered_map<int, int> comp;
int tempoG;

void printGraph(const Graph& G) {
    for (auto it = G.begin(); it != G.end(); ++it) {
        std::cout << "[" << it->first << "] : ";
        for (const int& neighbor : it->second) {
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
    // --- ESTRATÉGIA DE LEITURA DE ARQUIVO ---
    Graph G;
    vector<string> respostas;

    ifstream arquivo("test.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo 'entrada.txt'" << endl;
        return 1;
    }

    int n;
    // Laço principal que lê cada caso de teste do arquivo
    while (arquivo >> n && n != 0) {
        G.clear(); // Garante que o grafo esteja vazio para o novo caso

        int k, j;
        // Laço que lê as arestas do caso de teste atual
        while (arquivo >> k >> j && (k != 0 || j != 0)) {
            G[k].push_back(j);
            G[j].push_back(k);
        }


        if (biparticao_bfs(G, G.begin()->first)) {
            respostas.push_back("SIM");
        } else {
            respostas.push_back("NAO");
        }
    }

    arquivo.close();

    // --- IMPRESSÃO DOS RESULTADOS E FINALIZAÇÃO (INALTERADO) ---
    for (auto& node : respostas) {
        cout << node << endl;
    }

    // A chamada printGraph estava no seu código, mantida aqui.
    // Ela imprimirá um grafo vazio, pois G é limpo a cada iteração
    // e o laço termina antes que G seja repopulado.
    printGraph(G); 
    return 0;
}