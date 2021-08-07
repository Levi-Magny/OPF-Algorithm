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
    double custo;
public:
    /**
     * @brief Construtor do objeto Vertice
     * 
     * @param xc Coordenada x do vertice
     * @param yc Coordenada y do vertice
     * @param classe Classe do vertice
     */
    Vertice(double xc, double yc, int classe = -1) {
        x = xc;
        y = yc;
        nClasse = classe;
        custo = -1.0;
    }

    /**
     * @brief Pega o custo
     * 
     * @return custo
     */
    double get_custo(){
        return custo;
    }

    /**
     * @brief Modifica o custo
     * 
     * @param valor Novo custo
     */
    void set_custo(double valor){
        custo = valor;
    }

    /**
     * @brief Pega o x
     * 
     * @return x
     */
    double get_x(){
        return x;
    }

    /**
     * @brief Pega o y
     * 
     * @return y
     */
    double get_y(){
        return y;
    }

    /**
     * @brief Pega a classe
     * 
     * @return classe
     */
    int get_class(){
        return nClasse;
    }

    /**
     * @brief Modifica a classe
     * 
     * @param valor Nova classe
     */
    void set_class(int valor){
        nClasse = valor;
    }
};

#endif