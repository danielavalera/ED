//SIN ITERADORES

#include <iostream>
#include <cassert>
#include <string> 
#include <fstream>
#include <vector>
#include <deque>

using namespace std;


// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
    int n, e; cin >> n;
    if (n == 0) return false;

    vector<int> v;
    for (int i = 0; i < n; i++) {
        cin >> e; v.push_back(e);
    }

    deque<int> d;
    if (!v.empty()) {
        d.push_back(v[0]);
        for (int i = 1; i < v.size(); i++) {
            if (v[i] > 0)
                d.push_back(v[i]);
            else
                d.push_front(v[i]);
        }
        for (int i = 0; i < d.size(); i++) cout << d[i] << " ";
    }    
    cout << "\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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