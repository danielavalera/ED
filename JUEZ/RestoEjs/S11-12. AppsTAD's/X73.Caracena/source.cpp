/*
 * ---------------------------------------------------------------
 *                 ESTRUCTURAS DE DATOS - EXAMEN FINAL
 *                   CONVOCATORIA EXTRAORDINARIA
 * ---------------------------------------------------------------
 *                            Ejercicio 3
 * ---------------------------------------------------------------
 */


 // Nombre y apellidos: ________________________________________  

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <utility>
// Añade los #include que necesites
#include <map>
#include <deque>
#include <list>
#include <iterator>
#include <unordered_map>

using namespace std;

/*
 * Implementación del TAD Restaurante
 */


class Restaurante {
private:
    // Coloca aquí los atributos y métodos privados de la clase.
    struct Pedido {
        int mesa;
        string producto;
    };

    struct InfoMesa {
        map<string, deque<list<Pedido>::iterator>> pendientes_recibir;
    };

    list<Pedido> pedidos_pendientes;
    unordered_map<int, InfoMesa> mesas;

    InfoMesa& buscar_mesa(int mesa) {
        auto it = mesas.find(mesa);
        if (it == mesas.end()) {
            throw domain_error("Mesa vacia");
        }
        else {
            return it->second;
        }
    }


    const InfoMesa& buscar_mesa(int mesa) const{
        auto it = mesas.find(mesa);
        if (it == mesas.end()) {
            throw domain_error("Mesa vacia");
        }
        else {
            return it->second;
        }
    }
public:
    // ¡No olvides el coste de las operaciones!

    //O(1)
    void nueva_mesa(int num) {
        if (mesas.count(num)) 
            throw domain_error("Mesa ocupada");
        
        mesas.insert({ num,{} });
    }

    //O(1)
    void nuevo_pedido(int mesa, string plato) {
        buscar_mesa(mesa);
        pedidos_pendientes.push_back({mesa, plato});
        auto it = --pedidos_pendientes.end(); //iterador al último elemento recien añadido (--)
        mesas[mesa].pendientes_recibir[plato].push_back(it);
    }

    //O(1)
    pair<int, string> servir() {
        if (pedidos_pendientes.empty()) 
            throw domain_error("No hay pedidos pendientes");
        
        Pedido pedido = pedidos_pendientes.front(); //obtenemos el primer pedido de la lista
        pedidos_pendientes.pop_front(); //lo eliminamos

        auto& pendientes = mesas[pedido.mesa].pendientes_recibir[pedido.producto]; //obtenemos la cola de iteradores del producto de la mesa
        pendientes.pop_front(); //eliminamos el primer elemento

        if (pendientes.empty())  //si la cola de iteradores del producto de la mesa se queda vacía
            mesas[pedido.mesa].pendientes_recibir.erase(pedido.producto); //eliminamos el producto de la mesa
        
        return { pedido.mesa, pedido.producto};
    }

    //O(n)
    vector<string> que_falta(int mesa) const {
        vector<string> platos;
        const InfoMesa& info_mesa = buscar_mesa(mesa);//O(1)

        for(const auto &par : info_mesa.pendientes_recibir){ //O(n) donde n = nº de platos
            if (!par.second.empty()) //O(1)
                platos.push_back(par.first);//O(1)
        }

        return platos;
    }

    //O(1)
    void cancelar_pedido(int mesa, const string& plato) {
        InfoMesa& info_mesa = buscar_mesa(mesa);
        auto it = info_mesa.pendientes_recibir.find(plato); //obtenemos el plato de la mesa

        //si no se ha pedido
        if (it == info_mesa.pendientes_recibir.end() || it->second.empty())  // si no se ha encontrado el plato o si lo has encontrado pero su cola de iteradores está vacia
            throw domain_error("Producto no pedido por la mesa");
        
        //si sí se ha pedido
        auto pedido_it = it->second.back(); //obtenemos el último elemento de la cola de iteradores del producto
        pedidos_pendientes.erase(pedido_it); //lo eliminamos de pedidos pendientes
        it->second.pop_back(); //eliminamos el iterador del producto de la mesa
        if (it->second.empty()) { //si la cola de iteradores está vacia
            info_mesa.pendientes_recibir.erase(it); //eliminamos el producto
        }
    }
};


//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------


// Función que trata un caso de prueba.
bool tratar_caso() {
    Restaurante r;

    string operacion;
    cin >> operacion;

    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "nueva_mesa") {
                int n; cin >> n;
                r.nueva_mesa(n);
            }
            else if (operacion == "nuevo_pedido") {
                int n; cin >> n;
                string p; cin >> p;
                r.nuevo_pedido(n, p);
            }
            else if (operacion == "cancelar_pedido") {
                int n; cin >> n;
                string p; cin >> p;
                r.cancelar_pedido(n, p);
            }
            else if (operacion == "servir") {
                pair<int, string> par = r.servir();
                cout << par.second << " " << par.first << "\n";
            }
            else if (operacion == "que_falta") {
                int n; cin >> n;
                vector<string> platos = r.que_falta(n);
                cout << "En la mesa " << n << " falta:\n";
                for (const string& p : platos) {
                    cout << "  " << p << "\n";
                }
            }
        }
        catch (exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }

        cin >> operacion;
    }

    cout << "---\n";

    return true;
} // tratar_caso

int main() {
#ifndef DOMJUDGE
    std::ifstream in("caracena.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}