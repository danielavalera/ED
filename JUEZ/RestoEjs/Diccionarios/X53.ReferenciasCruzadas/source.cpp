// Referencias cruzadas
// --------------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <map>
#include <set>

using namespace std;


// 
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (0), o true en caso contrario.
//

bool tratar_caso() {
    
    int N; cin >> N;
    cin.ignore();
    if (N == 0) return false;

    string linea, palabra;
    map<string, set<int>> palabras;
    for (int i = 1; i <= N; i++)
    {
        getline(cin, linea);
        stringstream ss(linea);
        for (int j = 0; j < linea.size(); j++)
        {
            ss >> palabra;
            if (palabra.size() > 2) {
                transform(palabra.begin(), palabra.end(), palabra.begin(), [](unsigned char c) { return tolower(c); });
                palabras[palabra].insert({ i });
            }
            j += palabra.size();
        }
    }

    for (auto x : palabras) {
        cout << x.first << " ";
        for (auto y : x.second) {
            cout << y << " ";
        }
        cout << "\n";
    }
    cout << "---" << "\n";
    return true;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("X53.txt");
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
