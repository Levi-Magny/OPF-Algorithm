#include "./cabecalhos/OPF.h"

/**
 * @brief Menu para escolher arquivo
 * 
 * @return String para o arquivo desejado
 */
string menu_arquivo() {
   int escolha;
   cout << "Escolha um arquivo para ser utilizado" << endl;
   cout << "1: banana.txt" << endl;
   cout << "2: spirals.txt" << endl;
   cout << "Escolha: ";
   cin >> escolha;

   if(escolha == 1)
      return "./files/banana.txt";
   else if(escolha == 2)
      return "./files/spirals.txt";
   else {
      cout << endl << "Essa opcao nao existe" << endl << endl;
      return menu_arquivo();
   }
}

/**
 * @brief Menu para criar vertice
 * 
 * @return Vertice com X e Y definidos pelo usuário
 */
Vertice menu_vertice() {
   double x, y;
   cout << endl << "Escolha as coordenadas para o ponto" << endl;
   cout << "X: ";
   cin >> x;
   cout << "Y: ";
   cin >> y;
   return Vertice(x,y);
}

int main() {

   // Cria g com os dados do arquivo escolhido
   OPF g(menu_arquivo());

   // Classifica o vertice escolhido
   g.Classificar(menu_vertice());
}