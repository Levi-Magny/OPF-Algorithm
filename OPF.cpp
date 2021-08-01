#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "Vertice.h"
#include "Banana.h"
#include "Spirals.h"

using namespace std;

class Grafo {
private:
    int tamanho;
    vector<Vertice> vertices;
    double **matrizAdj;
    int size;
    void criarMatriz(int size);
    bool buscarVertices(string path, string classe);
public:
    Grafo(){
        buscarVertices("./files/banana.txt", "banana");
        buscarVertices("./files/spirals.txt", "spirals");
        size = vertices.size();
        criarMatriz(size);
    }
    int getSize(){return vertices.size();}
};

void Grafo::criarMatriz(int size){
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
bool Grafo::buscarVertices(string path, string classe){
    ifstream file(path);
    if(file.is_open()){
        string str;
        while (getline(file, str)){
            double coord[3];
            int i = 0;
            string word = "";
            for(auto s:str){
                if(s == ' ' || s == '\n'){
                    coord[i] = stod(word);
                    i++;
                    word = "";
                }
                else{
                    word += s;
                }
            }
            if(classe == "banana"){
                Banana nv = Banana(coord[0], coord[1], coord[2]);
                vertices.push_back(nv);
            } else {
                Spirals nv = Spirals(coord[0], coord[1], coord[2]);
                vertices.push_back(nv);
            }
        }
        file.close();
        return true;
    }
    return false;
}

int main(){
   Grafo g;
}