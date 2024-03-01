/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  //@ <answer>
  /*
    Indica el nombre y apellidos de los componentes del grupo
    ---------------------------------------------------------
    Componente 1:
    Componente 2:
  */
  //@ </answer>

  /*
    En este ejercicio solamente pueden utilizarse las colecciones vistas durante
    esta semana: pilas, colas, o dobles colas.

    En lugar de utilizar las implemtaciones vistas en clase, utilizad las que
    vienen implementadas en la biblioteca estándar de C++, que son las
    siguientes:

    - queue, definida en el fichero de cabecera <queue>
      Documentación: https://en.cppreference.com/w/cpp/container/queue

    - stack, definida en el fichero de cabecera <stack>
      Documentación: https://en.cppreference.com/w/cpp/container/stack

    - deque, definida en el fichero de cabecera <deque>
      Documentación: https://en.cppreference.com/w/cpp/container/deque

    Añade los #include con los ficheros de cabecera del TAD o los TADs que
    vais a utilizar, aunque estén fuera de las etiquetas <answer>...</answer>.
  */


#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <utility>
#include <queue>
#include <deque>


using namespace std;



//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------


// Añade los tipos de datos auxiliares y funciones que necesites

int personasPendientes(deque<char>& exs, queue<char>& conds, int t) {
    int countPerPendientes = 0;

    for (int i = 0; i < t; i++) //según los días (t)
    {
        while (!exs.empty()) {
            char exAux = exs.front();
            char condAux = conds.front();
            exs.pop_front();

            if (exAux == 'A') {
                if (condAux == 'M') {
                    conds.pop();
                    conds.push(condAux);
                }
                else {
                    conds.pop();
                }

            }
            /*else if (exAux == 'B') {

            }*/
            else {
                conds.pop();
                conds.push(condAux);
            }
        }
    }

    /*while (!conds.empty()) {
        countPerPendientes++;
        conds.pop();
    }*/

    return countPerPendientes;
}

// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.
bool tratar_caso() {
    int n, m, t; cin >> n >> m >> t;

    if (!cin) return false;

    char examinador, conductor;
    deque<char> examinadores; //porq nos interesa iterar siempre en la misma lista
    queue<char> conductores;

    for (int i = 0; i < n; i++)
    {
        cin >> examinador;
        examinadores.push_back(examinador);
    }

    for (int i = 0; i < m; i++)
    {
        cin >> conductor;
        conductores.push(conductor);
    }

    cout << personasPendientes(examinadores, conductores, t) << "\n";

    return true;
}

// ----------------------------------------------
// No modificar a partir de la línea
// ----------------------------------------------
//@ </answer>


int main() {
    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("datosL04.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Ejecutamos tratar_caso() hasta que nos devuelva `false`
    while (tratar_caso()) {}

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
