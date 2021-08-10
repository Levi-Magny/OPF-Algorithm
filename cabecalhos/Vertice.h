#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
#include <limits>
using namespace std;

/**
 * @brief Definindo limite do double como infinito
 * 
 */
const double INF = numeric_limits<double>::max();

/**
 * @brief Classe geral para um vertice do grafo
 * 
 */
class Vertice {
private:
    double x;
    double y;
    string nClasse;
    double custo;
public:
    /**
     * @brief Construtor do objeto Vertice
     * 
     * @param xc Coordenada x do vertice
     * @param yc Coordenada y do vertice
     * @param classe Classe do vertice
     */
    Vertice(double xc, double yc, string classe = "null") {
        x = xc;
        y = yc;
        nClasse = classe;
        custo = INF;
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
    string get_class(){
        return nClasse;
    }

    /**
     * @brief Modifica a classe
     * 
     * @param valor Nova classe
     */
    void set_class(string valor){
        nClasse = valor;
    }
};

#endif