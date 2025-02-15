#include <iostream>
#include <cassert>
#include <string> 
#include <fstream>
#include <sstream>
#include <stack>


using namespace std;

// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
    string linea;
    stack<char> p;

    if (!getline(cin, linea))
        return false;

    int i = 0;
    bool equilibrado = true;
    while (i < linea.size() && equilibrado) {
        switch (linea[i]) {
        case '(':
        case '[':
        case '{':
            p.push(linea[i]);
            break;
        case ')':
            if (p.empty() || p.top() != '(')
                equilibrado = false;
            else
                p.pop();
            break;
        case ']':
            if (p.empty() || p.top() != '[')
                equilibrado = false;
            else
                p.pop();
            break;
        case '}':
            if (p.empty() || p.top() != '{')
                equilibrado = false;
            else
                p.pop();
            break;
        }
        i++;
    }

    if (equilibrado && !p.empty()) equilibrado = false;

    if (equilibrado) cout << "SI" << "\n";
    else cout << "NO" << "\n";

    return true;
}


int main() {
    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("4.1.txt");
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
