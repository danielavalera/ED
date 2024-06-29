// Teclado estropeado
// ------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <list>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

void tratar_lista(list<char>& l) {
    auto it = l.begin();
    while (it != l.end()) {
        if (*it == '-') {
            it = l.erase(it);
            it = l.begin();
        }
        else if (*it == '+') {
            it = l.erase(it);
            it = l.end();
        }
        else if (*it == '*') {
            it = l.erase(it);
            it--;
        }
        else if (*it == '3') {
            it = l.erase(--it);
            it = l.erase(it);
        }
        else
            it++;
    }
}

bool tratar_caso() {
	// Escribe aquí el código para leer y tratar un caso de prueba.
	// La función debe devolver false si no se puede leer ningún caso de prueba
	// porque se ha llegado al fin de la entrada, o true en caso contrario.
    string linea;

    if (!getline(cin, linea)) {
        return false; // No se puede leer ningún caso de prueba (fin de entrada)
    }
    
    stringstream ss(linea);
    char letra;
    list<char> l;
    for (int i = 0; i < linea.size(); i++)
    {
        ss >> letra;
        l.push_back(letra);
    }

    tratar_lista(l);

    for (auto x : l) {
        cout << x;
    }
    cout << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("X28.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
    while (tratar_caso()) {}

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
