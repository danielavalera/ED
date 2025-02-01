/*
 * ---------------------------------------------------------------
 *                 ESTRUCTURAS DE DATOS - EXAMEN FINAL
 * ---------------------------------------------------------------
 *                            Ejercicio 3
 * ---------------------------------------------------------------
 *
 * IMPORTANTE: Para realizar este ejercicio solo es necesario
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas no se
 * tendrá en cuenta para la corrección.
 *
 * ---------------------------------------------------------------
 */


 //@ <answer>

 // Nombre y apellidos: DANIELA VALENTINA VALERA FUENTES  

 //@ </answer>


 //@ <answer>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
// Añade los #include que necesites
#include <map>
#include <unordered_map>
#include <iterator>
//@ </answer>


using namespace std;

//@ <answer>

// Implementa los métodos pedidos dentro de la clase.
// No te olvides del coste de cada método.

class Ferrovistan {
public:
    //O(1)
    void nueva_linea(const string& nombre) {
        if (lineas.count(nombre)) //O(1)
            throw domain_error("Linea existente");

        lineas.insert({ nombre, {} }); //O(1)
    }

    //O(log m + log n)
    //donde m = nº de lineas donde la estación está presente
    //y n = nº de estaciones en la linea
    void nueva_estacion(const string& linea, const string& nombre, int posicion) {
        InfoLinea& info_linea = buscar_linea(linea); //O(1)
        
        //si la estacion existe y si la linea existe en la estacion
        if (estaciones.count(nombre) && estaciones.at(nombre).count(linea)) //O(1) + O(log m)
            throw domain_error("Estacion duplicada en linea");

        if (info_linea.count(posicion)) //O(log n)
            throw domain_error("Posicion ocupada");

        info_linea[posicion] = nombre; //O(log n)
        estaciones[nombre][linea] = posicion; //O(log m)
    }

    //O(m*log n)
    void eliminar_estacion(const string& estacion) {
        const InfoEstacion& info_estacion = buscar_estacion(estacion); //O(1)

        for (auto& pair : info_estacion) { //O(m)
            InfoLinea& info_linea = lineas[pair.first];
            info_linea.erase(pair.second); //O(log n)
        }

        estaciones.erase(estacion); //O(1)
    }
    //O(m)
    vector<string> lineas_de(const string& estacion) const {
        vector<string> lista_lineas;
        const InfoEstacion& info_estacion = buscar_estacion(estacion); //O(1)

        for (const auto& pair: info_estacion) //O(m)
            lista_lineas.push_back(pair.first); //O(1)
        
        return lista_lineas;
    }

    //O(1)
    string proxima_estacion(const string& linea, const string& estacion) const {
        const InfoLinea& info_linea = buscar_linea(linea); //O(1)
        const InfoEstacion& info_estacion = buscar_estacion(estacion); //O(1)
        
        auto l = info_estacion.find(linea);//O(1)
        if (l == info_estacion.end()) //O(1)
            throw domain_error("Estacion no existente");
        int posicion = l->second;
        // Comprobamos que la estación no sea la última
        auto m = info_linea.find(posicion);
        if (next(m) == info_linea.end())  //O(1)
            throw domain_error("Fin de trayecto");

        // Obtenemos el valor del iterador
        const auto& next_station = *next(m); //O(1)

        return next_station.second;
    }

private:
    // Implementación privada
    using InfoLinea = map<int, string>;
    using InfoEstacion = map<string, int>;

    // para cada línea almacenamos un diccionario con la posicion de cada estacion
    unordered_map<string, InfoLinea> lineas;
    // para cada estación almacenamos un diccionario con su posición en cada linea
    unordered_map<string, InfoEstacion> estaciones;

    //O(1)
    InfoLinea& buscar_linea(const string& nombre) {
        auto it = lineas.find(nombre); // O(1)
        if (it == lineas.end()) {  // O(1)
            throw domain_error("Linea no existente");
        }
        else {
            return it->second; // O(1)
        }
    }

    //O(1)
    const InfoLinea& buscar_linea(const string& nombre) const{
        auto it = lineas.find(nombre); // O(1)
        if (it == lineas.end()) { // O(1)
            throw domain_error("Linea no existente");
        }
        else {
            return it->second; // O(1)
        }
    }

    //O(1)
    InfoEstacion& buscar_estacion(const string& nombre) {
        auto it = estaciones.find(nombre); // O(1)
        if (it == estaciones.end()) { // O(1)
            throw domain_error("Estacion no existente");
        }
        else {
            return it->second; // O(1)
        }
    }

    //O(1)
    const InfoEstacion& buscar_estacion(const string& nombre) const {
        auto it = estaciones.find(nombre); // O(1)
        if (it == estaciones.end()) { // O(1)
            throw domain_error("Estacion no existente");
        }
        else {
            return it->second; // O(1)
        }
    }
};



//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>

bool tratar_caso() {
    Ferrovistan f;
    string operacion;
    cin >> operacion;

    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "nueva_linea") {
                string nombre; cin >> nombre;
                f.nueva_linea(nombre);
            }
            else if (operacion == "nueva_estacion") {
                string linea; cin >> linea;
                string nombre; cin >> nombre;
                int posicion; cin >> posicion;
                f.nueva_estacion(linea, nombre, posicion);
            }
            else if (operacion == "eliminar_estacion") {
                string estacion; cin >> estacion;
                f.eliminar_estacion(estacion);
            }
            else if (operacion == "lineas_de") {
                string estacion; cin >> estacion;
                vector<string> lineas = f.lineas_de(estacion);
                cout << "Lineas de " << estacion << ":";
                for (const string& linea : lineas) {
                    cout << " " << linea;
                }
                cout << "\n";
            }
            else if (operacion == "proxima_estacion") {
                string linea; cin >> linea;
                string estacion; cin >> estacion;
                string proxima = f.proxima_estacion(linea, estacion);
                cout << proxima << "\n";
            }
        }
        catch (exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("ferrovistan.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}
