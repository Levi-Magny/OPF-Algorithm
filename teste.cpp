#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    string x, y, z;
    int i = 0;
    ifstream file("Teste.txt");
    while (!file.eof()){
        file >> x >> y >> z;
        cout << stod(x) << " " << stod(y) << " " << stod(z) <<endl;
    }
}