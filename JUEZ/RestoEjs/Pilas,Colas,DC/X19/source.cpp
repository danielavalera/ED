// Paréntesis equilibrados
// -----------------------
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
#include <sstream>
#include <stack>


using namespace std;



// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
    string linea;
    stack<char> p;

    if (!getline(cin, linea))
        return false;

    int i = 0;
    bool equilibrado = true;
    while (i < linea.size() && equilibrado) {
        switch (linea[i]){
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
    std::ifstream in("X19.txt");
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

