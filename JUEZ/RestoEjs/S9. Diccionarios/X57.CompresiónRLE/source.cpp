// Compresión RLE
// ---------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <cassert>
#include <fstream>
#include <map>
using namespace std;


// 
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (0 0), o true en caso contrario.
//

bool tratar_caso() {
    int W, H; cin >> W >> H;
    if (W == 0 && H == 0) return false;

    int N; cin >> N;
    map<int,map<int,string>> image;
    
    int current_pixel = 0;
    for (int i = 0; i < N; ++i) {
        int length;
        string color;
        cin >> length >> color;

        for (int j = 0; j < length; ++j) {
            int y = current_pixel % W + 1;
            int x = current_pixel / W + 1;
            image[x][y] = color;
            current_pixel++;
        }
    }

    int Q, X, Y; cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        cin >> X >> Y;
        cout << image[X][Y] << "\n";
    }

    cout << "---" << "\n";
    return true;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("X57.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (tratar_caso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
