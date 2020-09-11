// dijkstra.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h>
// a soma do peso das arestas de um grafo de tamanho 300 vértices
// com arestas de pesos <= 300 não passa de 90.000
// logo 999999999 pode ser considerado infinito

const int myINFINITY = 999999999;
//#include "dijkstra.h"
using namespace std;

vector<string> split(const string &str, const string &delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}


int menorCustoAtual(int verticeAvaliado, int numeroVertices, int *custos, int *verticesAbertos) {
    int menor = myINFINITY + 1;
    int newVerticeAvaliado = verticeAvaliado;
    for (int i = 0; i < numeroVertices; i++) {
        if (menor > custos[i] && verticesAbertos[i]) {
            menor = custos[i];
            newVerticeAvaliado = i;
        }
    }
    return newVerticeAvaliado;
}

bool estaVazio(int *verticesAbertos, int numeroVertices) {
    int qtdeFechados = 0;
    for (int i = 0; i < numeroVertices; i++) {
        if (!verticesAbertos[i]) {
            qtdeFechados++;
        }
    }
    return qtdeFechados != numeroVertices;
}

/**
 * Aplica o algoritmo de Dijkstra ao grafo passado como parâmetro
 * Não possui retorno direto, mas os vetor int *custos, int *predecessores são ponteiros que serão atualizados
 * com o custo do caminho mínimo e o caminho mínimo respectivamente.
 *
 * @param verticeOrigem é o vértice de origem (para o qual serão encontrados os menores custos)
 * @param matrizAdjacencia é a representação do grafo, utilizamos uma representação por matriz de adjacência pois no pior caso sua complexidade é semelhante as listas de adjacência e é mais simples de implementar
 * @param numeroVertices é a quantidade de vértices do grafo, logicamente a dimensão da matriz de adjacência tem dimensão numeroVerticesxnumeroVertices
 * @param custos é um vetor de inteiros. Ao final da função, na posição i contém a distância do vértice de origem para o vértice (i+1), pois o grafo de entrada é indexado a partir de 1
 * @param predecessores é um vetor de inteiros. Ao final da função, na posição i contém o predecessor no caminho mínimo do vértice (i+1), pois o grafo de entrada é indexado a partir de 1
 * @return
 */
void *dijkstra(int verticeOrigem, int **matrizAdjacencia, int numeroVertices, int *custos, int *predecessores) {
    int verticeAvaliado = verticeOrigem;

    /**
     * Inicialização do algoritmo de Dijkstra, inicialmente os custos são definidos como infinito,
     * e não são conhecidos os predecessores, utilizamos -1 como null,
     * O vetor custos é a "chave" da fila de priooridades.
     */
    for (int i = 0; i < numeroVertices; ++i) {
        custos[i] = myINFINITY;
        predecessores[i] = -1;
    }
    /**
     * verticesAbertos servirá como a fila de prioridades
     * verticesAbertos[i] igual a zero significa que o vértice (i + 1) do grafo já saiu da fila de prioridade (está no conjunto S)
     */
    int *verticesAbertos = new int[numeroVertices];
    for (int i = 0; i < numeroVertices; ++i) {
        verticesAbertos[i] = 1;
    }
    custos[verticeAvaliado] = 0;


    /**
     * Faz a checagem na fila de prioridade para ver se está vazia
     */
    while (estaVazio(verticesAbertos, numeroVertices)) {

        /**
         * Atualiza como próximo vértice a ser descobertoo que tem menor distância ao caminho mínimo
         * E então remove esse vértice da fila de prioridades fazendo verticesAbertos[verticeAvaliado] = 0;
         */
        verticeAvaliado = menorCustoAtual(verticeAvaliado, numeroVertices, custos, verticesAbertos);
        verticesAbertos[verticeAvaliado] = 0;
        for (int i = 0; i < numeroVertices; i++) {
            /**
             * Como foi escolhido uma representação por matriz de adjacência, deve-se verificar se é vizinho (!= myINFINITY)
             */
            if ((matrizAdjacencia[verticeAvaliado][i]) != myINFINITY && i != verticeAvaliado) {
                if (custos[i] > custos[verticeAvaliado] + matrizAdjacencia[verticeAvaliado][i]) {
                    custos[i] = custos[verticeAvaliado] + matrizAdjacencia[verticeAvaliado][i];
                    predecessores[i] = verticeAvaliado;
                }
            }
        }

    }

    return nullptr;
}


int main() {

    int numVertex = 0;
    int numEdges = 0;
    int **weights = new int *;

    //std::ifstream file(argv[1]);
    //if (file.is_open()) {
        std::string line;
        int contLines = 0;
        while (std::getline(cin, line)) {
            if (contLines == 0) {
                vector<string> tokens = split(line, " ");
                numVertex = stoi(tokens[0]);
                numEdges = stoi(tokens[1]);

                weights = new int *[numVertex];
                for (int i = 0; i < numVertex; ++i) {
                    weights[i] = new int[numVertex]();
                    for (int j = 0; j < numVertex; ++j) {
                        if (i != j) {
                            weights[i][j] = myINFINITY;
                        }
                    }
                }
            } else {
                vector<string> tokens = split(line, " ");
                int v1 = stoi(tokens[0]);
                int v2 = stoi(tokens[1]);
                int w = stoi(tokens[2]);
                weights[v1 - 1][v2 - 1] = w;
                weights[v2 - 1][v1 - 1] = w;
            }
            contLines += 1;
            //printf("%s\n", line.c_str());
        }
        //file.close();
    //}


    int max_distancia = 0;

    int verticeOrigem = 0;
    int verticeDestino = 0;

    int *predecessores = {};

    /**
     * Chamando o algoritmo de Dijkstra |V| vezes para resolver o problema de caminhos mínimos entre todos os pares
     * Esse algoritmo pode ser aplicado pois assumimos como entrada que todas as arestas tem pesos positivos
     */
    for (int i = 0; i < numVertex; ++i) {
        int *custos = new int[numVertex];
        int *predecessors = new int[numVertex];

        dijkstra(i, weights, numVertex, custos, predecessors);
        /**
         * Verifica-se se a distância no caminho da origem para os demais vértices é o maior até então,
         * Ao final temos a maior distância de um caminho mínimo (max_distancia) e esse caminho (predecessores)
         */
        for (int u = 0; u < numVertex; ++u) {
            if (custos[u] > max_distancia) {
                verticeDestino = u;
                verticeOrigem = i;
                max_distancia = custos[u];
                predecessores = predecessors;
            }
        }
    }

    /**
     * Saídas da execução
     */

    cout << max_distancia << "\n";
    cout << verticeOrigem + 1 << " "<< verticeDestino + 1 << " " << "\n";

    int totalVerticesCaminho = 1;
    /**
     * Aplica-se então o print-path no caminho para visualizá-lo
     */
    int pai = verticeDestino;
    string path = "";
    path = to_string(pai + 1) + path;
    while (1) {
        if (predecessores[pai] == -1) {
            break;
        }
        path = to_string(predecessores[pai] + 1) + " " + path;
        pai = predecessores[pai];
        totalVerticesCaminho += 1;
    }

    cout << totalVerticesCaminho << "\n";
    cout << path;

    return 0;
}
