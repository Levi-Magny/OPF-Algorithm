#ifndef SPIRALS_H
#define SPIRALS_H

#include <iostream>
#include "Vertice.h"
using namespace std;

/**
 * @brief Classe do tipo Spirals
 * 
 */
class Spirals : public Vertice {
private:
    string classe = "spirals";
public:
    Spirals(double xc, double yc, double zc) : Vertice(xc, yc, zc){
        x = xc;
        y = yc;
        z = zc;
    }
    string get_classe(){
        return classe;
    }
};

#endif