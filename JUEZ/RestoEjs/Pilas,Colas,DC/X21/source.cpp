// Reordenando la cola
// -------------------
// Estructuras de datos


/*
  En este ejercicio solamente pueden utilizarse las colecciones vistas durante
  esta semana: pilas, colas, o dobles colas.

  En lugar de utilizar las implementaciones vistas en clase, utilizad las que
  vienen implementadas en la biblioteca estándar de C++, que son las
  siguientes:

  - queue, definida en el fichero de cabecera <queue>
    Documentación: https://en.cppreference.com/w/cpp/container/queue

  - stack, definida en el fichero de cabecera <stack>
    Documentación: https://en.cppreference.com/w/cpp/container/stack

  - deque, definida en el fichero de cabecera <deque>
    Documentación: https://en.cppreference.com/w/cpp/container/deque

  Añade los #include con los ficheros de cabecera del TAD o los TADs que
  vais a utilizar.
*/


#include <iostream>
#include <cassert>
#include <string> 
#include <fstream>
#include <vector>
#include <deque>
#include <iterator>

using namespace std;



// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de entrada (0). Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
    int n; cin >> n;
    if (n == 0)return false;

    vector<int> v;
    int e;
    for (int i = 0; i < n; i++) {
        cin >> e;
        v.push_back(e);
    }

    deque<int> d;
    d.push_back(v[0]);
    auto it1 = d.begin();
    auto it2 = d.begin();
    while (it2 != d.end()) {
        for (int i = 1; i < v.size(); i++) {
            if (v[i] >= *it2) {
                d.push_back(v[i]);
                it1 = d.begin();
                it2 = --d.end();
            }
            else if (v[i] <= *it1) {
                d.push_front(v[i]);
                it1 = d.begin();
                it2 = --d.end();
            }
        }
        it2 = d.end();
    }


    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << " ";
    }
    cout << "\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("X21.txt");
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