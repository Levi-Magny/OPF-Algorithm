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
 * @brief Menu para o usuário escolher um ponto
 * 
 * @param g Referência do do objeto OPF criado no main
 */
void menu_vertice(OPF &g) {
   double x, y;
   int escolha = 1;
   do {
      cout << endl << "Escolha as coordenadas para o ponto" << endl;
      cout << "X: ";
      cin >> x;
      cout << "Y: ";
      cin >> y;
      g.Classificar(Vertice(x,y));

      cout << endl << "Deseja classificar outro ponto ? [1 = Sim] [0 = Nao]";
      cout << "Escolha: ";
      cin >> escolha;
   } while(escolha != 0);
}

int main() {

   // Cria g com os dados do arquivo escolhido
   OPF g(menu_arquivo());

   // 
   menu_vertice(g);
}