#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
using namespace std;

/**
 * @brief Classe geral para um vertice do grafo
 * 
 * ...Provavelmente vou mudar pra usar apenas essa classe
 */
class Vertice {
protected:
    double x;
    double y;
    double z;
    string classe;
public:
    /**
     * @brief Construct a new Vertice object
     * 
     * @param xc Coordenada x do vertice
     * @param yc Coordenada y do vertice
     * @param zc Coordenada z do vertice
     */
    Vertice(double xc, double yc, double zc){
        x = xc;
        y = yc;
        z = zc;
    }
    double get_x(){
        return x;
    }
    double get_y(){
        return y;
    }
    double get_z(){
        return z;
    }
    string get_class(){
        return classe;
    }
    void set_class(string valor){
        classe = valor;
    }
};

#endif