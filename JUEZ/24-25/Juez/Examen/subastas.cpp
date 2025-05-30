#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
#include <list>
#include <queue>
#include <deque>
#include <fstream>
using namespace std;

using Objeto = string;
using Puja = int;
using Participante = string;
using Posicion = list<Participante>::iterator;
struct ParticipanteInfo{
    int saldo;
    unordered_map<Objeto,pair<Puja,Posicion>> pendientes; //Para cada puja del participante, no resuelta me guardo el valor de la puja y el iterador a la posición.
    set<Objeto> ganados; //Un conjunto ordenado alfabéticamente de los objetos ganados.
};

struct ObjetoInfo{
    Puja minimo;  
    bool vendido = false;
    map<Puja,list<Participante>> pujas; //Para cada valor, me guardo en orden cronologico los participantes que lo apostaron.
};

class CasaDePujas{

    
    public: 
        //O(1)
        void nuevo_participante(Participante part, int saldo_inicial){
            if(participantes.count(part) > 0) throw domain_error("Participante ya existente");
            if(saldo_inicial <= 0) throw domain_error("Saldo inicial no valido");
            participantes[part].saldo = saldo_inicial;
        }

	//O(1)
        void nueva_subasta(Objeto obj, int puja_minima){
            if(objetos.count(obj) > 0) throw domain_error("Objeto no valido");
            if(puja_minima <= 0) throw domain_error("Puja inicial no valida");
            objetos[obj].minimo = puja_minima;
        }

	//O(logP) donde P es el numero de participantes. => En el caso peor, todos los participantes podrían haber pujado por el objeto.
        void nueva_puja(Participante part, Objeto obj, int cantidad){
            if(participantes.count(part) == 0) throw domain_error("Participante no existente");
            if(objetos.count(obj) == 0 || objetos[obj].vendido) throw domain_error("Objeto no valido");
	    if(participantes[part].pendientes.count(obj) > 0) throw domain_error("Participante repetido");
            if(objetos[obj].minimo > cantidad || participantes[part].saldo < cantidad) throw domain_error("Cantidad no valida");
            objetos[obj].pujas[cantidad].push_back(part); //O(logP)
            participantes[part].pendientes[obj] = {cantidad, --objetos[obj].pujas[cantidad].end()};
            participantes[part].saldo -= cantidad;
        }
        
	//O(Obj), donde Obj es el numero de objetos. 
        list<Objeto> subastas_ganadas(Participante part) const {
            if(participantes.count(part) == 0) throw domain_error("Participante no existente");
            list<Objeto> objs;
            for(auto obj : participantes.at(part).ganados){
                objs.push_back(obj);
            }
            return objs;
        }

	//O(Obj*logP), Por cada objeto que tengo que eliminar hago un trabajo logP al acceder al mapa ordenado de pujas.
        void abandonar_casa(Participante part){
            if(participantes.count(part) == 0) throw domain_error("Participante no existente");
            for(auto [obj, pair] : participantes[part].pendientes){ //Obj veces. Una por cada objeto.
                Puja p = pair.first; 
                list<Participante>::iterator it = pair.second; //O(1)
                objetos[obj].pujas[p].erase(it); //O(logP)
                if(objetos[obj].pujas[p].empty()) objetos[obj].pujas.erase(p); //O(logP)
            }
            participantes.erase(part);
        }

	//O(logObj) + O(P)
        string cerrar_subasta(Objeto obj){
            if(objetos.count(obj) == 0 || objetos[obj].vendido) throw domain_error("Objeto no valido");
            if(objetos[obj].pujas.empty()) throw domain_error("Objeto no vendido");
            auto it = --objetos[obj].pujas.end();
            string ganador = it->second.front(); //El primero de la lista es el ganador       O(1)
            participantes[ganador].pendientes.erase(obj); //Eliminamos obj de pendientes.     O(1)
            participantes[ganador].ganados.insert(obj); //Insertamos obj como subasta ganada. O(logObj)
            it->second.pop_front(); //Lo eliminamos de la lista				      O(1)
            for(auto [puja, parts] : objetos[obj].pujas){//Para cada una de las pujas  Caso peor tantas como participantes
                for(string part : parts){              //y para cada uno de los participantes
                    participantes[part].saldo += puja; //Devolvemos el dinero a los perdedores.
                    participantes[part].pendientes.erase(obj); //Eliminimos obj como subasta pendiente.
                }
            }
            objetos[obj].pujas = {}; //Eliminamos las pujas anteriores. Esto da un poco igual
            objetos[obj].vendido = true; //Lo indicamos como vendido.
            return ganador;
        }
    
    private:
        unordered_map<Participante,ParticipanteInfo> participantes;
        unordered_map<Objeto, ObjetoInfo> objetos;
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string op;
    std::cin >> op;    
    if (!std::cin)
        return false;
    CasaDePujas casa;
    while (op != "FIN") {

        try {

            if (op == "nuevo_participante") {

                string nombre; int saldo;
                std::cin >> nombre >> saldo;

                casa.nuevo_participante(nombre,saldo);
                cout << "OK\n";
            }

            else if (op == "nueva_subasta") {

                string nombre; int minimo;
                std::cin >> nombre >> minimo;

                casa.nueva_subasta(nombre,minimo);
                cout << "OK\n";
            }

            else if (op == "nueva_puja") {

                string nombre, objeto; int minimo;
                std::cin >> nombre >> objeto >> minimo;

                casa.nueva_puja(nombre,objeto, minimo);
                cout << "OK\n";
            }
            else if (op == "abandonar_casa") {
                string nombre;
                std::cin >> nombre;
                casa.abandonar_casa(nombre);
                cout << "OK\n";

            }
            else if (op == "subastas_ganadas") {
                string nombre;
                std::cin >> nombre;
                list<string> v = casa.subastas_ganadas(nombre);
                cout << nombre << " ha ganado: "; 
                for (string el : v) {
                    cout << el << " ";
                }
                cout << "\n";
            }
            else if (op == "cerrar_subasta") {
                string nombre;
                std::cin >> nombre;
                string ganador = casa.cerrar_subasta(nombre);
                cout << nombre << " ha sido ganado por: " << ganador;
                cout << "\n";
            }
        }
        catch (std::domain_error& e) {

            std::cout << "ERROR: " << e.what() << "\n";
        }

        std::cin >> op;

    }

    std::cout << "---\n";

    return true;

}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
    while (resuelveCaso());//Resolvemos todos los casos
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
#endif
}
