#include <iostream>
#include <cassert>
#include <string> 
#include <queue>
#include <fstream>


using namespace std;


// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
    int n, r; cin >> n >> r;
    if (n == 0 && r == 0)return false;

    queue<int> cola;
    for (int i = 1; i <= n; i++) {
        cola.push(i);
    }

    while (n > 1) {
        for (int i = 0; i < r; i++) {
            cola.push(cola.front());
            cola.pop();
        }
        cola.pop();
        n--;
    }

    cout << cola.front() << "\n";
    return true;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("4.2.txt");
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