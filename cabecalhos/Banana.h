#ifndef BANANA_H
#define BANANA_H

#include <iostream>
#include "Vertice.h"
using namespace std;

/**
 * @brief classe que herda da classe grafo
 * 
 */
class Banana : public Vertice {
private:
    string classe = "banana";
public:
    /**
     * @brief Constroi um novo vertice do tipo Banana
     * 
     * @param xc Coordenada x
     * @param yc Coordenada y
     * @param zc Coordenada z
     */
    Banana(double xc, double yc, double zc) : Vertice(xc, yc, zc){
        x = xc;
        y = yc;
        z = zc;
    }
    string get_classe(){
        return classe;
    }
};

#endif