// El alumno afortunado
// --------------------
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
#include <queue>


using namespace std;



// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de entrada (0 0). Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
    int n,r; cin >> n >> r;
    if(n==0 && r == 0)return false;

    queue<int> cola;
    for(int i=1; i <= n; i++){
        cola.push(i);
    }

    while(n > 1){
        for(int i=0; i < r; i++){
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
  // Ejecutamos tratar_caso() hasta que nos devuelva `false`
  while (tratar_caso()) { }

  return 0;
}
