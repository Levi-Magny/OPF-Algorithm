#ifndef OPF_H
#define OPF_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <math.h>
#include <queue>
#include "Vertice.h"
using namespace std;

const double INF = numeric_limits<double>::max();

/**
 * @brief 
 * O primeiro valor é o custo e o segundo e o indice do vertice
 */
typedef pair<double, int> iPar;

/**
 * @brief Grafo contendo o algoritmo de floresta de caminhos otimos
 * 
 */
class OPF {
private:
    int tamanho;
    vector<Vertice> vertices;
    double **matrizAdj;
    int size;
    void criarMatriz(int size);
    bool buscarVertices(string path);
    double calcEuclDist(Vertice& a, Vertice& b);
    void setMatrizAdj(double** MAdj);
    void excluiMatrizAdj();
    void DFS_EncontraPrototipo(int v, bool *visitado, bool jaEncontrado);
public:
    OPF(){
        // buscarVertices("./files/banana.txt");
        buscarVertices("./files/spirals.txt");
        // buscarVertices("./files/teste.txt");
        size = vertices.size();
        criarMatriz(size);
        gerarOPF();
        primsAlg();
        bool *visitado = new bool[size];
        DFS_EncontraPrototipo(0, visitado, false);
    }
    ~OPF(){
        excluiMatrizAdj();
    }
    int getSize(){return vertices.size();}
    void gerarOPF();
    double matrizValue(int i, int j){return matrizAdj[i][j];}
    double** novaMatriz();
    void primsAlg();
};

/**
 * @brief método que realiza uma "busca por profundidade".
 * neste caso, ele apenas está percorrento e atualizando o valor de 'visitado'.
 * Essa estratégia é baseada na programação dinâmica.
 * 
 * @param v vértice atual 
 * @param visitado vetor que guarda o estado atual dos vértices quanto a busca.
 */
void OPF::DFS_EncontraPrototipo(int v, bool *visitado, bool jaEncontrado) {
    if(!visitado[v]){ // verifica se o vértice ja foi visitado
        visitado[v] = true; // se nao foi, marca como visitado.
        for(int i = 0; i < size && !jaEncontrado; i++) {
            if(matrizAdj[v][i] != -1){ // procura vertices adjacentes ao atual
                if(vertices.at(i).get_class() != vertices.at(v).get_class()) {
                    vertices.at(v).set_prototipo();
                    vertices.at(i).set_prototipo();
                    matrizAdj[v][i] = matrizAdj[i][v] = -1;
                    cout << "I: " << i << " v: " << v << endl;
                    jaEncontrado = !jaEncontrado;
                    return;
                }
                DFS_EncontraPrototipo(i, visitado, jaEncontrado); // quando acha, vai para o vertice encontrado recursivamente.
            }
        }
    }
}

/**
 * @brief Modifica a matrizAdj
 * 
 * @param MAdj Nova matriz
 */
void OPF::setMatrizAdj(double** MAdj){
    excluiMatrizAdj();
    matrizAdj = MAdj;
    // for(int i = 0; i < size; i++) {
    //     cout << i << "::=> ";
    //     for(int j = 0; j < size; j++) {
    //         cout << matrizAdj[i][j] << " ";
    //     }
    //     cout << endl;
    // }
};

/**
 * @brief metodo para desalocar a memoria alocada
 * 
 */
void OPF::excluiMatrizAdj(){
    for(int i = 0; i < size; i++){
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
}

/**
 * @brief Cria um grafo completo com arestas ponderadas de acordo com a
 * distância euclidiana entre os dois vertices.
 * 
 * A diagonal principal (que indicaria laços) é marcada como 'infinito'
 */
void OPF::gerarOPF(){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if(i == j){
                matrizAdj[i][j] = INF;
            } else if (matrizAdj[i][j] == 0){
                double dist = calcEuclDist(vertices[i], vertices[j]);
                matrizAdj[i][j] = dist;
                matrizAdj[j][i] = dist;
            }
        }
    }
}

/**
 * @brief Calcula a distancia euclidiana entre dois pontos em R3
 * 
 * @param a 
 * @param b 
 * @return double distancia entre 2 pontos
 */
double OPF::calcEuclDist(Vertice& a, Vertice& b){
    return sqrt(pow((b.get_x() - a.get_x()),2) + pow((b.get_y() - a.get_y()),2));
}

/**
 * @brief Inicializa a matriz com '0's
 * 
 * @param size Quantidade de vertices do grafo
 */
void OPF::criarMatriz(int size){
    matrizAdj = new double*[size];
    for(int i = 0; i < size; i++){
        matrizAdj[i] = new double[size] ();
    }
}

/**
 * @brief busca as coordenadas dos vertices dentro dos seus respectivos arquivos.
 * 
 * @param path Caminho do arquivo contendo os vértices.
 * @param classe Classe a qual o vertice pertence.
 * @return true se conseguir abrir o arquivo.
 * @return false se nao conseguir abrir o arquivo.
 */
bool OPF::buscarVertices(string path){
    ifstream file(path);
    string firstLine;
    getline(file, firstLine);
    if(file.is_open()){
        while (!file.eof()){
            string x, y;
            int classe;
            file >> x >> y >> classe;

            Vertice nv = Vertice(stod(x), stod(y), classe);
            nv.set_class(classe);
            vertices.push_back(nv);
        }
        file.close();
        return true;
    }
    return false;
}

/**
 * @brief Aloca memoria para uma nova matriz de adjacencias
 * 
 * @return double** retorna a matriz
 */
double** OPF::novaMatriz(){
    double **matriz;
    matriz = new double*[size];

    for(int i = 0; i < size; i++){
        matriz[i] = new double[size] ();
        for(int j = 0; j < size; j++)
            matriz[i][j] = -1.0;
    }
    return matriz;
}

/**
 * @brief Algoritmo de Prim para Minimum Spanning Tree
 * 
 */
void OPF::primsAlg(){
    priority_queue<iPar, vector<iPar>, greater<iPar>> Pq;

    double **nMatriz = novaMatriz();

    double cost[size]; // custo/chave dos vertices
    int pai[size], src = 0; // Guarda o valor dos vertices pai de cada vertice.
    bool inMST[size]; // Insere o vertice na MST

    // Inicializa os valores
    for(int i = 0; i < size; i++){
        cost[i] = INF;
        pai[i] = -1;
        inMST[i] = false;
    }
    cost[src] = 0.0;
    
    Pq.push(make_pair(0.0, src));

    // enquanto a fila de prioridades contiver algum vertice
    while(!Pq.empty()){
        int u = Pq.top().second;
        Pq.pop();

        // considerar apenas o menor peso dos vertices
        if(inMST[u]){
            continue;
        }

        // insere aresta ma matriz de adjacências 
        if(pai[u] != -1 && !inMST[u]){
            double value = matrizAdj[u][pai[u]];
            nMatriz[u][pai[u]] = nMatriz[pai[u]][u] = value;
        }
        inMST[u] = true;
        for(int i = 0; i < size; i++){
            if(i != u){
                //pega o indice do vertice e o peso da aresta que 
                int v = i;
                double weight = matrizAdj[u][i];
                if(!inMST[v] && cost[v] > weight){
                    cost[v] = weight;
                    Pq.push(make_pair(cost[v], v));
                    pai[v] = u;
                }
            }
        }
    }
    setMatrizAdj(nMatriz);
}

#endif