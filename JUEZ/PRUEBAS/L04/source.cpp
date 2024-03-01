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
    Componente 1: Sánchez Guerra, Sara
    Componente 2: Valera Fuentes, Daniela
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

int personasPendientes(const deque<char>& exs, queue<char>& conds, int m, int t) {
    vector<int> repetidos(m, 0); // vector para llevar el recuento de suspensos por conductor

    for (int dia = 0; dia < t; dia++) {
        for (size_t hora = 0; hora < exs.size(); hora++){
            char condAux = conds.front();
            int indexRepetidos = hora % m;

            if (exs[hora] == 'A') {
                if (condAux == 'M') {
                    conds.pop();
                    conds.push(condAux);
                    repetidos[indexRepetidos]++;
                }
                else {
                    conds.pop();
                }
            }
            else if (exs[hora] == 'B') {
                if (repetidos[indexRepetidos] < 2) {
                    if (condAux == 'M') {
                        conds.pop();
                        conds.push(condAux);
                        repetidos[indexRepetidos]++;
                    }
                    else {
                        conds.pop();
                    }
                }
                else {
                    conds.pop();
                }
            }
            else {
                conds.pop();
                conds.push(condAux);
                repetidos[indexRepetidos]++;
            }
        }
        
    }

    return conds.size();
}

// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.
bool tratar_caso() {
    int n, m, t; cin >> n >> m >> t;

    if (!cin) return false;

    char conductor;
    deque<char> examinadores(n); //porq nos interesa iterar siempre en la misma lista
    queue<char> conductores;

    for (int i = 0; i < n; i++)
    {
        cin >> examinadores[i];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> conductor;
        conductores.push(conductor);
    }

    cout << personasPendientes(examinadores, conductores, m, t) << "\n";

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
