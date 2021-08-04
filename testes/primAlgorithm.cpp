#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
const double INF = numeric_limits<double>::max();
typedef pair<double, int> iPar;

class Grafo {
private:
    int tamanho;
    vector<int> vertices; // polimorfismo: qualquer classe filha de 'Vertice' é um Vertice
    double matrizAdj[5][5];
    int *MST;
    int size;
    void criarMatriz(int size);
    bool buscarVertices(string path, string classe);
public:
    Grafo(){
        double matrizAdj[5][5] {
            {INF, 5.0, 4.0, 6.0, 9.0},
            {5.0, INF, 1.0, 2.0, 3.0},
            {4.0, 1.0, INF, 2.0, 1.0},
            {6.0, 2.0, 2.0, INF, 7.0},
            {9.0, 3.0, 1.0, 7.0, INF}
        };
        size = 5;
    }
    int getSize(){return size;}
    double matrizValue(int i, int j){return matrizAdj[i][j];}
    void primsAlg();
};

void Grafo::primsAlg(){
    priority_queue<iPar, vector<iPar>, greater<iPar>> Pq;

    double cost[size];
    int pai[size], src = 0;
    bool inMST[size];
    for(int i = 0; i < size; i++){
        cost[i] = INF;
        pai[i] = -1;
        inMST[i] = false;
    }
    cost[src] = 0.0;
    pai[src] = 0.0;
    Pq.push(make_pair(0.0, src));

    while(!Pq.empty()){
        int u = Pq.top().second;
        cout << u << " -\n";
        Pq.pop();
        // considerar apenas o menor peso dos vertices
        if(inMST[u]){
            continue;
        }
        inMST[u] = true;
        for(int i = 0; i < size; i++){
            if(i != u){
                //pega o indice do vertice e o peso da aresta que 
                int v = i;
                double weight = matrizAdj[u][i];
                if(!inMST[v] && cost[v] > weight){
                    // cout << "got here\n";
                    cost[v] = weight;
                    Pq.push(make_pair(cost[v], v));
                    pai[v] = u;
                }
            }
        }
    }
    for(int i = 0; i < size; i++){
        cout << i << " " << pai[i] << endl;
    }
}

int main(){
    Grafo g;
    g.primsAlg();
}