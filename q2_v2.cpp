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

void dfs_visit(const Graph& G, int root, int leaf, bool& existPath) {
    if (root == leaf) {
        existPath = true;
        return;
    }

    color[root] = GRAY;
    // O uso de .at() pode lançar uma exceção se a chave não existir.
    // Em um grafo bem formado lido do arquivo, isso não deve ser problema.
    if (G.count(root)) {
        vector<int> vizinhos = G.at(root);
        for (auto it = vizinhos.begin(); it != vizinhos.end(); ++it) {
            if (G.count(*it) && color.at(*it) == WHITE) {
                tempoG++;
                dfs_visit(G, *it, leaf, existPath);
            }
        }
    }

    color[root] = BLACK;
}

bool dfs(const Graph& G, int root, int leaf) {
    for (auto it = G.begin(); it != G.end(); ++it) {
        color[it->first] = WHITE;
    }
    tempoG = 0;
    bool existPath = false;
    dfs_visit(G, root, leaf, existPath);
    return existPath;
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
            //G[j].push_back(k);
        }

        // --- LÓGICA DE DETECÇÃO DE TRIÂNGULOS (INALTERADA) ---
        bool afirmacao = false;
        for (auto it = G.begin(); it != G.end(); ++it) {
            for (auto neighbor = it->second.begin(); neighbor != it->second.end(); ++neighbor) {
                for (auto vizinho = next(neighbor); vizinho != it->second.end(); ++vizinho) {
                    if (G.count(*neighbor) > 0 && find(G.at(*neighbor).begin(), G.at(*neighbor).end(), *vizinho) != G.at(*neighbor).end()) {
                        afirmacao = true;
                        break;
                    }
                }
              
            }
        }

        if (afirmacao) {
            respostas.push_back("NAO");
        } else {
            respostas.push_back("SIM");
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