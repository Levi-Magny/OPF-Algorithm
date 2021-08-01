#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertice.h"
#include "Banana.h"
#include "Spirals.h"

class Grafo {
private:
    int tamanho;
    vector<Vertice> vertices;
    int **matrizAdj;
public:
    Grafo(){
        buscarVertices("./files/banana.txt", "banana");
        buscarVertices("./files/spirals.txt", "spirals");
    }
    int getSize(){return vertices.size();}
    bool buscarVertices(string path, string classe);
};

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

using namespace std;

int main(){
   Grafo g;
   cout << "Quantidade de vertices: " << g.getSize();
}