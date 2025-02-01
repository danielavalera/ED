/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*@ <answer>

  Nombre y apellidos:

  Da una explicación de la solución y justifica su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <list>
using namespace std;
#include <unordered_set>

// ----------------------------------------------------------------
//@ <answer>

template <typename T>
void eliminar_repetidos(list<T>& lista) {
    unordered_set<T> elems_repes;
    auto it = lista.begin();
    while (it != lista.end()) {
        if (elems_repes.find(*it) != elems_repes.end()) {
            it = lista.erase(it);
        }
        else {
            elems_repes.insert(*it);
            ++it;
        }
    }

}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

template <typename T>
void resuelve() {
    int N;
    cin >> N;
    list<T> lista;
    for (int i = 0; i < N; ++i) {
        T elem; cin >> elem;
        lista.push_back(elem);
    }
    eliminar_repetidos(lista);
    for (T elem : lista) {
        cout << elem << ' ';
    }
    cout << '\n';
}

bool tratar_caso() {
    char tipo;
    cin >> tipo;
    if (!cin)
        return false;
    if (tipo == 'N')
        resuelve<int>();
    else
        resuelve<string>();
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("eliminarepes.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif

    return 0;
}
