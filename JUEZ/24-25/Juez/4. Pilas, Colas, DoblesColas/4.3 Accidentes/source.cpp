#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
using namespace std;

struct accidente {
    string fecha;
    int cantidad;
};
bool resuelveCaso() {
    // leer los datos de la entrada
    int N; cin >> N;
    if (!std::cin)
        return false;

    stack<accidente> accidentes;
    string fechaAux;
    int quantityAux;
    int i = 0;
    while (i < N) {
        cin >> fechaAux >> quantityAux;

        while (!accidentes.empty() && accidentes.top().cantidad <= quantityAux) 
            accidentes.pop();

        if (accidentes.empty()) cout << "NO HAY\n";
        else cout << accidentes.top().fecha << "\n";
        
        accidentes.push({ fechaAux,quantityAux });
        i++;
    }
    cout << "---\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("4.3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}