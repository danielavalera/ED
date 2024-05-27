/*
 * ¿Quién empieza?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

bool tratar_caso() {
    int num_ninyos;
    int salto;
    queue<int> cola;

    cin >> num_ninyos >> salto;
    if (num_ninyos == 0 && salto == 0) return false;

    for (int i = 1; i <= num_ninyos; i++) {
        cola.push(i);
    }

    while (num_ninyos > 1) {
        for (int i = 0; i < salto; i++) {
            cola.push(cola.front());
            cola.pop();
        }
        cola.pop();
        num_ninyos--;
    }

    cout << cola.front() << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("quienempieza.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (tratar_caso()) {}
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
