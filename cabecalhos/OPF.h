#ifndef OPF_H
#define OPF_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <queue>
#include <algorithm>
#include "Vertice.h"
using namespace std;

/**
 * @brief O primeiro valor é o custo e o segundo e o indice do vertice
 * 
 */
typedef pair<double, int> iPar;

/**
 * @brief Grafo contendo o algoritmo de floresta de caminhos otimos
 * 
 */
class OPF {
private:
    int size;
    double **matrizAdj;
    double** novaMatriz();
    vector<int> prototipos;
    vector<Vertice> vertices;
    void primsAlg();
    void gerarOPF();
    void treinamento();
    void excluiMatrizAdj();
    void criarMatriz(int size);
    void setMatrizAdj(double** MAdj);
    bool buscarVertices(string path);
    double calcEuclDist(Vertice& a, Vertice& b);
    void gerarCustos(int v, bool *visitado, double maiorPeso);
    void DFS_EncontraPrototipo(int v, bool *visitado);
public:
    /**
     * @brief Construtor do objeto OPF
     * 
     * @param path Caminho (string) para o arquivo desejado
     */
    OPF(string path){
        buscarVertices(path);
        size = vertices.size();
        criarMatriz(size);
        cout << "\n########## Gerar Grafo ##########\n";
        gerarOPF();
        cout << "\n###### Iniciar Treinamento ######\n";
        treinamento();
    }
    ~OPF(){
        excluiMatrizAdj();
    }
    void Classificar(Vertice vertice);
};


/**
 * @brief Modifica a matrizAdj
 * 
 * @param MAdj Nova matriz
 */
void OPF::setMatrizAdj(double** MAdj){
    excluiMatrizAdj();
    matrizAdj = MAdj;
};

/**
 * @brief Metodo para desalocar a memoria alocada
 * 
 */
void OPF::excluiMatrizAdj(){
    for(int i = 0; i < size; i++){
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
}

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
                matrizAdj[i][j] = INF;
            } else if (matrizAdj[i][j] == 0){
                double dist = calcEuclDist(vertices[i], vertices[j]);
                matrizAdj[i][j] = dist;
                matrizAdj[j][i] = dist;
            }
        }
    }
}

/**
 * @brief Calcula a distancia euclidiana entre dois pontos
 * 
 * @param a Vertice a
 * @param b Vertice b
 * @return Distancia entre 2 pontos (em double)
 */
double OPF::calcEuclDist(Vertice& a, Vertice& b){
    return sqrt(pow((b.get_x() - a.get_x()),2) + pow((b.get_y() - a.get_y()),2));
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
 * @brief Busca as coordenadas dos vertices dentro dos seus respectivos arquivos.
 * 
 * @param path Caminho do arquivo contendo os vértices.
 * @return True se conseguir abrir o arquivo. False se nao conseguir abrir o arquivo.
 */
bool OPF::buscarVertices(string path){
    ifstream file(path);
    string qtdV, algo;
    int qtdC;
    file >> qtdV >> algo >> qtdC;
    if(file.is_open()){
        while (!file.eof()){
            string x, y, classe;
            file >> x >> y >> classe;

            Vertice nv = Vertice(stod(x), stod(y), classe);
            nv.set_class(classe);
            vertices.push_back(nv);
        }
        file.close();
        return true;
    }
    return false;
}

/**
 * @brief Aloca memoria para uma nova matriz de adjacencias
 * 
 * @return double** retorna a matriz
 */
double** OPF::novaMatriz(){
    double **matriz;
    matriz = new double*[size];

    for(int i = 0; i < size; i++){
        matriz[i] = new double[size] ();
        for(int j = 0; j < size; j++)
            matriz[i][j] = -1.0;
    }
    return matriz;
}

/**
 * @brief Etapa de treinamento
 * 
 */
void OPF::treinamento(){
    // Gerando MST
    primsAlg();

    // encontrando prototipos
    bool *visitado = new bool[size];
    DFS_EncontraPrototipo(0, visitado);
    delete[] visitado;

    // percorre as arvores atribuindo o custo a cada um dos vertices, partindo do prototipo
    visitado = new bool[size];
    for(int c : prototipos)
        gerarCustos(c, visitado, 0);
}

/**
 * @brief Algoritmo de Prim para Minimum Spanning Tree (MST)
 * 
 */
void OPF::primsAlg(){
    priority_queue<iPar, vector<iPar>, greater<iPar>> Pq;

    double **nMatriz = novaMatriz();

    double cost[size]; // custo/chave dos vertices
    int pai[size], src = 0; // Guarda o valor dos vertices pai de cada vertice.
    bool inMST[size]; // Insere o vertice na MST

    // Inicializa os valores
    for(int i = 0; i < size; i++){
        cost[i] = INF;
        pai[i] = -1;
        inMST[i] = false;
    }
    cost[src] = 0.0;
    
    Pq.push(make_pair(0.0, src));

    // enquanto a fila de prioridades contiver algum vertice
    while(!Pq.empty()){
        int u = Pq.top().second;
        Pq.pop();

        // considerar apenas o menor peso dos vertices
        if(inMST[u]){
            continue;
        }

        // insere aresta ma matriz de adjacências 
        if(pai[u] != -1 && !inMST[u]){
            double value = matrizAdj[u][pai[u]];
            nMatriz[u][pai[u]] = nMatriz[pai[u]][u] = value;
        }
        inMST[u] = true;
        for(int i = 0; i < size; i++){
            if(i != u){
                //pega o indice do vertice e o peso da aresta que 
                int v = i;
                double weight = matrizAdj[u][i];
                if(!inMST[v] && cost[v] > weight){
                    cost[v] = weight;
                    Pq.push(make_pair(cost[v], v));
                    pai[v] = u;
                }
            }
        }
    }
    setMatrizAdj(nMatriz);
}

/**
 * @brief Método que realiza uma "busca por profundidade" no grafo
 * para encontrar os protótipos.
 * 
 * @param v Vértice atual 
 * @param visitado Vetor que guarda o estado atual dos vértices quanto a busca.
 * @param jaEncontrado Verifica se os protótipos já foram encontrados
 */
void OPF::DFS_EncontraPrototipo(int v, bool *visitado) {
    if(!visitado[v]){
        visitado[v] = true;
        for(int i = 0; i < size; i++) {
            if(matrizAdj[v][i] != -1){
                if(vertices.at(i).get_class() != vertices.at(v).get_class()) {
                    prototipos.push_back(v);
                    prototipos.push_back(i);
                    matrizAdj[v][i] = matrizAdj[i][v] = -1;
                    return;
                }
                DFS_EncontraPrototipo(i, visitado); 
            }
        }
    }
}

/**
 * @brief Método que gera os custos dos vértices
 * 
 * @param v Vértice atual 
 * @param visitado Vetor que guarda o estado atual dos vértices quanto a busca.
 * @param maiorPeso Maior peso encontrado até o momento
 */
void OPF::gerarCustos(int v, bool *visitado, double maiorPeso) {
    double MP;
    if(!visitado[v]){
        if(vertices[v].get_custo() > maiorPeso)
            vertices[v].set_custo(maiorPeso);
        visitado[v] = true;
        for(int i = 0; i < size; i++) {
            if(matrizAdj[v][i] != -1){
                MP = matrizAdj[v][i] > maiorPeso ? matrizAdj[v][i] : maiorPeso;
                gerarCustos(i, visitado, MP);
            }
        }
    }
}

/**
<<<<<<< HEAD
 * @brief Algoritmo utilizado para a classificação de novas amostras.
=======
 * @brief Classifica o vertice escolhido
>>>>>>> f8fee801a59d611e26a1397483157792ec3387b1
 * 
 * @param vertice Vértice escolhido para ser verificado
 */
void OPF::Classificar(Vertice vertice) {
    double dist, maior;
    iPar menorEclasse;
    menorEclasse.first = INF;
    for(int i = 0; i < size; i++) {
        dist = calcEuclDist(vertices.at(i), vertice);
        maior = dist > vertices.at(i).get_custo() ? dist : vertices.at(i).get_custo();
        if (menorEclasse.first > maior){
            menorEclasse.first = maior;
            menorEclasse.second = i;
        }
    }
    cout << endl << "O vertice tem custo: " << menorEclasse.first << ". Pertence a classe: " 
    << vertices.at(menorEclasse.second).get_class() << endl;
}

#endif