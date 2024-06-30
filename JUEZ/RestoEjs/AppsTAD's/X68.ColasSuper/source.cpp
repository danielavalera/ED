#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;


//--------------------------------------------------------------------------
// Modificar a partir de aquí
//--------------------------------------------------------------------------
//@ <answer>
class ColasSupermercado {
public:
    ColasSupermercado(const int &ncajas): cajas(ncajas){}

    void nuevo_cliente(const string& dni, const int& caja) {
        caja_en_rango(caja);
        if (clientes.count(dni)) {
            throw domain_error("Cliente duplicado");
        }
        cajas[caja].push_back({caja, dni});
        clientes.insert({dni, --cajas[caja].end()});
    }

    int consultar_cliente(const string &dni) {
        cliente_existente(dni);
        auto it = clientes[dni];
        return it->caja;
    }

    int cuantos_en_cola(const int& caja) {
        caja_en_rango(caja);
        return cajas[caja].size();
    }

    vector<string> clientes_en_cola(const int& caja) {
        caja_en_rango(caja);

        vector<string> ranking;
        auto lista = cajas[caja];
        if (!lista.empty()) {
            for (auto i = --lista.end(); i != lista.begin(); i--) {
                ranking.push_back(i->dni);
            }
            ranking.push_back(lista.front().dni);
        }
        return ranking;
    }

    void cambiar_cola(const string& dni, const int& caja) {
        caja_en_rango(caja);
        cliente_existente(dni);

        auto it = clientes[dni];
        int caja_actual = it->caja;
        if (caja_actual != caja) {
            cajas[caja].push_back({caja, dni});
            cajas[caja_actual].erase(it);
            clientes[dni] = --cajas[caja].end();
        }
    }
   
private:
    struct InfoCliente {
        int caja;
        string dni;
    };
    vector<list<InfoCliente>> cajas;
    unordered_map<string, list<InfoCliente>::iterator> clientes;

    void caja_en_rango(const int& caja) {
        if (caja < 0 || caja >= cajas.size())
            throw domain_error("Cola inexistente");
    }

    void cliente_existente(const string& dni) {
        if (!clientes.count(dni))
            throw domain_error("Cliente inexistente");
    }
};


// Función para tratar un caso de prueba. Devuelve false si, en lugar de un
// caso de prueba, se ha encontrado con la marca de fin de entrada
// (EOF). Devuelve true en caso contrario.
bool tratar_caso() {
    string operacion;
    int ncajas;
    cin >> ncajas >> operacion;
    ColasSupermercado cs(ncajas);

    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "nuevo_cliente") {
                string dni;
                int caja;
                cin >> dni >> caja;
                cs.nuevo_cliente(dni, caja);
            }
            else if (operacion == "cambiar_cola") {
                string dni;
                int caja;
                cin >> dni >> caja;
                cs.cambiar_cola(dni, caja);
            }
            else if (operacion == "consultar_cliente") {
                string dni; cin >> dni;
                int cola = cs.consultar_cliente(dni);
                cout << "El cliente "<< dni << " esta en la cola "<< cola << "\n";
            }
            else if (operacion == "cuantos_en_cola") {
                int caja; cin >> caja;
                int clientes = cs.cuantos_en_cola(caja);
                cout << "En la cola " << caja << " hay " << clientes << " clientes"<< "\n";
            }
            else if (operacion == "clientes_en_cola") {
                int caja; cin >> caja;
                auto lista = cs.clientes_en_cola(caja);
                cout << "En la cola " << caja << " estan: ";
                for (auto q : lista)
                    cout << q << " ";
                cout << "\n";
            }
        }
        catch (exception& e) {
            cout << "ERROR: " << e.what() << endl;
        }
        cin >> operacion;
    }

    cout << "---\n";

    return true;
}


//@ </answer>
//--------------------------------------------------------------------------
// No modificar a partir de aquí
//--------------------------------------------------------------------------


int main() {
    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("X68.txt");
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


