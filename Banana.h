#ifndef BANANA_H
#define BANANA_H

#include <iostream>
#include "Vertice.h"
using namespace std;

class Banana : public Vertice {
private:
    string classe = "banana";
public:
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