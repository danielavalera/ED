// Facundo y el undo
// -----------------
// Estructuras de datos
//-----------------------------------------------------------------------------------------------NO IMPRIME BIEN, está a medias

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
#include <iomanip>
#include <fstream>
#include <cassert>
#include <sstream>
#include <stack>
#include <deque>
/*#include <string> 

*/

using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    string linea;    
    getline(cin, linea);

    deque<string> cola;
    stack<string> palabras;


    istringstream ss(linea);
    string palabra;

    while (ss >> palabra) {
        if (palabra == "*") {
            if (!cola.empty()) {
                palabras.push(cola.back());
                cola.pop_back();
            }
        }
        else if (palabra == "+") {
            if (!palabras.empty()) {
                cola.push_back(palabras.top());
                palabras.pop();
            }
        }
        else {
            cola.push_back(palabra);
            while (!palabras.empty()) {
                palabras.pop();
            }
        }
    }



    while (!cola.empty()) {
        cout << cola.front() << " ";
        cola.pop_front();
    }
    cout << "\n";

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("X23.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    cin.ignore();
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}