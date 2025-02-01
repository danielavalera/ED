/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1:
   Componente 2:
 */


 // Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

// En este ejercicio utilizamos la clase `map` de la librería estándar de C++, 
// en lugar de la clase MapTree vista en clase. La interfaz de `map` es casi
// la misma que la de `MapTree`. Consulta el FAQ de la práctica para ver las
// diferencias principales.

// También puedes ver la documentación de la clase `map` en:
// https://en.cppreference.com/w/cpp/container/map



// Define un tipo para representar los programas
using programa = map<int, pair<string, string>>;

// Define un tipo para almacenar el valor de cada variable del programa
using memoria = map<string, int>;


// Función para ejecutar un programa.
//
// Recibe:
//    - El programa `p` a ejecutar
//    - Máximo número de instrucciones a ejecutar. Si se intenta ejecutar un número mayor
//      de instrucciones, se detiene la ejecución y se devuelve la memoria correspondiente
//      al estado del programa en el momento de detenerse.
//
// Devuelve un par con dos componentes:
//    - El estado de la memoria tras la ejecución del programa, bien sea porque se haya
//      ejecutado la última instrucción, o bien porque se haya alcanzado el límite de
//      instrucciones ejecutadas indicado por el parámetro `max_pasos`.  
//    - Un booleano que indique si se ha producido un error en la ejecución del programa
//      Devuelve `true` si se ha encontrado ejecutar una instrucción "GOTO n", donde n
//      es un número de instrucción que no se encuentra en el programa. Devuelve `false`
//      en caso contrario. Si el valor de esta componente es `true`, la primera componente
//      del par es irrelevante.

// Indica el coste, en el caso peor, de la función `ejecutar`, en función del tamaño
// del programa `p` y de `num_pasos`


//El coste de la funcion ejecutar seria O(min(n,num_pasos) siendo n el numero de instrucciones contenidas en el programa p
//y num_pasos el numero maximo de instrucciones a ejecutar. En el caso en que num_pasos sea menor a n se iterara num_pasos veces, en el 
//caso contario se iterará n veces.

pair<memoria, bool> ejecutar(const programa& p, int max_pasos) { 

    memoria mem;
    int pasos = 0;
    bool error = false;

    auto it = p.begin(); 

    while (it != p.end() && pasos < max_pasos) {
        
        int clave = it->first;
        string instr = it->second.first;
        string arg = it->second.second;

        if (instr == "GOTO") {
            int num = stoi(arg);

            it = p.find(num);     // si no encuentra esa clave it = end  
            if (it == p.end()) {
                error = true;
            }
          
        }
        else if (instr == "INCR") {
            if (mem.count(arg) == 0) {
                mem[arg] = 0; 
            }
            mem[arg]++;
            it++; //solo actualizo aqui para que las instrucciones GOTO funcionen correctamente
        }
        pasos++;
        
    }

    return { mem, error };
}


// Introduce el código para tratar un caso de prueba. Devuelve true
// si se ha encontrado un caso de prueba en la entrada, o false si,
// en su lugar, se ha encontrado la marca de fin de fichero (EOF).
bool tratar_caso() {
    programa prog; // Definición del programa
    string linea;

    while (getline(cin, linea)) {

        stringstream ss(linea);
        string primera_palabra;
        ss >> primera_palabra;

        if (primera_palabra == "BYE") {
            // Si encontramos la marca de fin del caso, devolvemos true
            cout << "---" << endl;
            return true;
        }
        else {
            int num;
            string instr, arg;

            if (primera_palabra == "RUN") {
                ss >> num; //max_pasos
                auto resultado = ejecutar(prog, num); //pair<memoria, bool>

                if (resultado.second) {
                    cout << "ERROR" << endl;
                }
                else {
                    for (const auto& res : resultado.first) {                       
                        cout << res.first << " = " << res.second << endl;                     
                    }
                    cout << "OK" << endl;
                }
            }
            else {

                int num;
                string instr, arg;
                num = stoi(primera_palabra); //para poder hacer prog[num] num debe ser int

                ss >> instr >> arg;
               /* if (instr == "INCR") {
                    mem[arg] = 0; //inicializar las variables a 0
                }
                */
                prog[num] = { instr, arg };
            }
        }
    }

    // Si llegamos aquí, significa que se ha alcanzado el final del fichero (EOF)
    return false;
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
    std::ifstream in("sample.in");
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