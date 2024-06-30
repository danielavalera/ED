// Me pilló el toro
// ----------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <sstream>
#include <map>
using namespace std;


// 
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (0 0), o true en caso contrario.
//

bool tratar_caso() {
    int N; cin >> N;
    cin.ignore();
    if (N == 0) return false;

    string nombres, nombre, calif;
    char letraNombre;
    map<string, int> alumnos;
    for (int i = 0; i < N; i++)
    {
        getline(cin, nombres);
        size_t pos = nombres.find_last_of(' ');
        string nombre = nombres.substr(0, pos);
        if (nombre.size() < nombres.size()) {
            nombre += nombres.substr(pos);
        }
        alumnos.insert({ nombre, 0 });
        cin >> calif;
        if (calif == "INCORRECTO")
            alumnos[nombre] -= 1;
        else
            alumnos[nombre] += 1;
        cin.ignore();
        nombre = "";
    }

    for (auto a : alumnos) {
        if (a.second != 0)
            cout << a.first << ", " << a.second << "\n";
    }

    cout << "---" << "\n";
    return true;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("X52.txt");
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
