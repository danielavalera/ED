#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
using namespace std;
using CapituloEmitido = int;
using DiaEmision = int;

/* EXPLICACIÓN: VENTANA DESLIZANTE
* Día 0: 1  
* Día 1: 2  
* Día 2: 3
* Día 3: 4
* Día 4: 2  ← ¡Repetido! Ya se vio en el día 1
* Día 5: 5
* Día 6: 6

Veamos cómo se forma la ventana sin repeticiones más larga:
**Del día 0 al 3: capítulos 1 2 3 4 → todos distintos → tamaño 4
**Día 4: capítulo 2 ya se vio → hay que mover el inicio de la ventana justo después del anterior 2 (que fue en el día 1)
**Nueva ventana: desde el día 2 a 6 → capítulos 3 4 2 5 6 → tamaño 5

✅ Así que la ventana más larga de días con capítulos distintos tiene tamaño 5.
*/
void resuelveCaso() {
    // leer los datos de la entrada


    int numCapitulos, capEmitido;
    int maxDiasNoRepes = 0;
    int diasNoRepes = 0;
    unordered_map<CapituloEmitido, DiaEmision> capitulos;
    cin >> numCapitulos;

    for (int i = 0; i < numCapitulos; i++)
    {
        cin >> capEmitido;
        if (!capitulos.count(capEmitido)) 
            diasNoRepes++;
        else {
            if (i - diasNoRepes > capitulos[capEmitido]) 
                diasNoRepes++;
            else 
                diasNoRepes = i - capitulos[capEmitido];
        }

        capitulos[capEmitido] = i;
        maxDiasNoRepes = max(maxDiasNoRepes, diasNoRepes);
    }

    cout << maxDiasNoRepes << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("7.4.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}