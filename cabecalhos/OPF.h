#ifndef OPF_H
#define OPF_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <math.h>
#include "Vertice.h"

using namespace std;

/**
 * @brief Grafo contendo o algoritmo de floresta de caminhos otimos
 * 
 */
class OPF {
private:
    int tamanho;
    vector<Vertice> vertices; // polimorfismo: qualquer classe filha de 'Vertice' é um Vertice
    double **matrizAdj;
    int size;
    void criarMatriz(int size);
    bool buscarVertices(string path, string classe);
    double calcEuclDist(Vertice& a, Vertice& b);
public:
    OPF(){
        buscarVertices("./files/banana.txt", "banana");
        buscarVertices("./files/spirals.txt", "spirals");
        size = vertices.size();
        criarMatriz(size);
        gerarOPF();
    }
    int getSize(){return vertices.size();}
    void gerarOPF();
    double matrizValue(int i, int j){return matrizAdj[i][j];}
};
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
                matrizAdj[i][j] = numeric_limits<int>::max();
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
    return sqrt(pow((b.get_x() - a.get_x()),2) + pow((b.get_y() - a.get_y()),2) + pow((b.get_z() - a.get_z()),2));
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
bool OPF::buscarVertices(string path, string classe){
    ifstream file(path);
    string firstLine;
    getline(file, firstLine);
    if(file.is_open()){
        while (!file.eof()){
            string x, y, z;
            file >> x >> y >> z;

            Vertice nv = Vertice(stod(x), stod(y), stod(z));
            nv.set_class(classe);
            vertices.push_back(nv);
        }
        file.close();
        return true;
    }
    return false;
}

#endif