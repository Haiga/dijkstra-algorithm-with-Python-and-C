// dijkstra.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dijkstra.h"
//#include "dijkstra.h"
using namespace std;

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

/*
int distToVertex(int** weights, int  indexVertex, int numVertex) {
    int* custs = new int[numVertex];
    int* openedVertex = new int[numVertex];
    for (int i = 0; i < numVertex; ++i) {
        custs[i] = INFINITY;
    }
    for (int i = 0; i < numVertex; ++i) {
        openedVertex[i] = 1;
    }
     
    custs[indexVertex - 1] = 0;

    int cont = 0;
    while (true) {
        for (int i = 0; i < numVertex; ++i) {
        
        }

    }
    for i in weights[index_vertex] :
        if index_vertex in weights :
    if i in weights[index_vertex] :
        cust = weights[index_vertex][i]
        if custs[i - 1] > custs[index_vertex - 1] + cust:
    custs[i - 1] = custs[index_vertex - 1] + cust
        preds[i - 1] = index_vertex - 1

        cont += 1
        openedVertex[index_vertex - 1] = 0
        if cont == num_vertex:
    break
        menor = infinito + 1
        for i in range(1, num_vertex + 1) :
            if menor > custs[i - 1] and openedVertex[i - 1]:
    menor = custs[i - 1]
        index_vertex = i
        if menor >= infinito :
            break
            return custs, preds
}
*/

int menorCustoAtual(int& verticeAvaliado, int numeroVertices, int* custos, int* verticesAbertos) {
    int infinito = INFINITY;
    int menor = infinito + 1;
    for (int i = 0; i < numeroVertices; i++) {
        if (menor > custos[i] && verticesAbertos[i]) {
            menor = custos[i];
            verticeAvaliado = i;
        }
    }
    return menor;
}

int quantidadeDeVerticesFechados(int* verticesAbertos, int numeroVertices) {
    int qtdeFechados = 0;
    for (int i = 0; i < numeroVertices; i++) {
        if (!verticesAbertos[i]) {
            qtdeFechados++;
        }
    }
    return qtdeFechados;
}

int* distanciasAoVertice(int vertice, int** matrizAdjacencia, int numeroVertices) {
    int verticeAvaliado = vertice - 1;
    int infinito = INFINITY;
    int* custos = new int[numeroVertices];
    for (int i = 0; i < numeroVertices; ++i) {
        custos[i] = INFINITY;
    }
    int* verticesAbertos = new int[numeroVertices];
    for (int i = 0; i < numeroVertices; ++i) {
        verticesAbertos[i] = 1;
    }
    custos[verticeAvaliado] = 0;


    while (1) {

        for (int i = 0; i < numeroVertices; i++) {
            if ((matrizAdjacencia[verticeAvaliado][i]) != infinito && i != verticeAvaliado) {
                if (custos[i] > custos[verticeAvaliado] + matrizAdjacencia[verticeAvaliado][i]) {
                    custos[i] = custos[verticeAvaliado] + matrizAdjacencia[verticeAvaliado][i];
                }
            }
        }

        verticesAbertos[verticeAvaliado] = 0;
        if (quantidadeDeVerticesFechados(verticesAbertos, numeroVertices) == numeroVertices) {
            break;
        }


        if (menorCustoAtual(verticeAvaliado, numeroVertices, custos, verticesAbertos) >= infinito) {
            break;
        }
    }

    return custos;
}




int main(int argc, char* argv[])
{
    int numVertex = 0;
    int numEdges = 0;
    int **weights = new int* [1];

    cout << "You have entered " << argc
        << " arguments:" << "\n";
    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";

    std::ifstream file(argv[1]);
    if (file.is_open()) {
        std::string line;
        int contLines = 0;
        while (std::getline(file, line)) {
            if (contLines == 0) {
                vector<string> tokens = split(line, " ");
                numVertex = stoi(tokens[0]);
                numEdges = stoi(tokens[1]);
                
                weights = new int* [numVertex];
                for (int i = 0; i < numVertex; ++i) {
                    weights[i] = new int[numVertex]();
                }
            }
            else {
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
        file.close();
    }

    cout << "num vertices " << numVertex << "\n";
    cout << "num edges " << numEdges << "\n";


    int max_dist = 0;

    int vertexV = 0;
    int vertexU = 0;
    int* custs_v = {};
    for (int i = 0; i < numVertex; ++i) {
        int* dists = distanciasAoVertice(i+1, weights, numVertex);
        for (int u = 0; u < numVertex; ++u) {
            if (dists[u] > max_dist) {
                vertexU = u + 1;
                vertexV = i + 1;
                max_dist = dists[u];
                custs_v = dists;
            }
        }
    }

    int custoAtual = custs_v[vertexV];
    while (vertexV != vertexU) {
        for (int i = 0; i < numVertex; i++) {
            float distVerticeItoVertice2 = 0;
            for (int j = 0; j < numVertex; j++)
            {
                if (weights[i][j] != 0) {
                    if (custoAtual - distVerticeItoVertice2 == custs_v[i]) {
                        custoAtual = custoAtual - distVerticeItoVertice2;

                        int i1 = i + 1;
                        int i2 = j + 1;

                        vertexU = i;
                        cout << i1;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
