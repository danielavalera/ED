// Actualización de un diccionario
// -------------------------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <map>
#include <set>


using namespace std;


// 
// Implementa a continuación la función que trata un caso de prueba.
//

void tratar_caso() {
    string clave, linea; 
    int valor;
    map<string, int> diccionario1, diccionario2;

    getline(cin, linea);
    stringstream ss(linea);
    for (int i = 0; i < linea.size(); i++)
    {
        ss >> clave >> valor;
        diccionario1.insert({ clave,valor });
        i += 3;
    }
    linea = "";
    getline(cin, linea);
    stringstream ss1(linea);
    for (int i = 0; i < linea.size(); i++)
    {
        ss1 >> clave >> valor;
        diccionario2.insert({ clave,valor });
        i += 3;
    }
    
    set<string> nuevas_claves, eliminadas_claves, modificadas_claves;
    for (auto x : diccionario2) {
        auto clave = x.first;
        auto valor = x.second;
        auto it = diccionario1.find(clave);

        if(it == diccionario1.end())
            nuevas_claves.insert(clave);
        else if(it->second != valor)
            modificadas_claves.insert(clave);
    }

    for (auto x : diccionario1) {
        auto clave = x.first;
        if (diccionario2.find(clave) == diccionario2.end()) 
            eliminadas_claves.insert(clave);
    }
    
    if (nuevas_claves.empty() && eliminadas_claves.empty() && modificadas_claves.empty()) {
        cout << "Sin cambios\n";
    }
    else {
        if (!nuevas_claves.empty()) {
            cout << "+";
            for (const auto& clave : nuevas_claves) {
                cout << " " << clave;
            }
            cout << "\n";
        }
        if (!eliminadas_claves.empty()) {
            cout << "-";
            for (const auto& clave : eliminadas_claves) {
                cout << " " << clave;
            }
            cout << "\n";
        }
        if (!modificadas_claves.empty()) {
            cout << "*";
            for (const auto& clave : modificadas_claves) {
                cout << " " << clave;
            }
            cout << "\n";
        }
    }
    cout << "---\n";
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("X54.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;
    cin.ignore(); // Leemos todos los caracteres hasta el fin de línea

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
