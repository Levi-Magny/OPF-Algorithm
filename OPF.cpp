#include "./cabecalhos/OPF.h"

int main(){
   Vertice v = Vertice(1.554976, -0.1531518);

   // "./files/banana.txt"
   // "./files/spirals.txt"
   // "./files/teste.txt"
   OPF g("./files/spirals.txt");

   g.Classificar(v);
}