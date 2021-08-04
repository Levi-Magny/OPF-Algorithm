#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
using namespace std;

/**
 * @brief Classe geral para um vertice do grafo
 * 
 */
class Vertice {
private:
    double x;
    double y;
    int nClasse;
public:
    /**
     * @brief Construct a new Vertice object
     * 
     * @param xc Coordenada x do vertice
     * @param yc Coordenada y do vertice
     * @param classe classe do vertice
     */
    Vertice(double xc, double yc, int classe){
        x = xc;
        y = yc;
        nClasse = classe;
    }
    double get_x(){
        return x;
    }
    double get_y(){
        return y;
    }
    int get_class(){
        return nClasse;
    }
    void set_class(int valor){
        nClasse = valor;
    }
};

#endif