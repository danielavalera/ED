// Oficinas de empleo
// ------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include <unordered_map>
#include <set>
#include <iterator>


using namespace std;


class OficinaEmpleo {
public:
    //O(log n), el resto O(1)
    void altaOficina(const string& nombre, const string& empleo) {
        if (!personas.count(nombre)) {//si no existe la persona
            personas[nombre] = set<string>(); //la inicializas
        }

        if (!personas[nombre].count(empleo)) { //como no tiene el empleo O(log m)
            personas[nombre].insert(empleo);//le das el valor O(log m)
            if (!empleos.count(empleo)) { //si no existe el empleo en los empleos
                empleos[empleo] = list<string>(); //lo inicializas
            }
            empleos[empleo].push_back(nombre);//le das el valor
            iteradores[empleo][nombre] = --empleos[empleo].end(); //asignas los iteradores
        }
    }
    //O(n)
    string ofertaEmpleo(string empleo) {
        string persona = "";
        if (!empleos.count(empleo)) {
            throw domain_error("No existen personas apuntadas a este empleo");
        }
        persona = empleos[empleo].front();
        for (auto& emp : personas[persona]) {
            auto& emp_list = empleos[emp];
            emp_list.erase(iteradores[emp][persona]);
            iteradores[emp].erase(persona);
            if (emp_list.empty()) {
                empleos.erase(emp);
            }
            if (iteradores[emp].empty()) {
                iteradores.erase(emp);
            }
        }

        personas.erase(persona);

        return persona;

    }
    //O(m)
    vector<string> listadoEmpleos(string persona) {
        if (!personas.count(persona)) {
            throw domain_error("Persona inexistente");
        }
        vector<string> lista(personas.at(persona).begin(), personas.at(persona).end());
        return lista;
    }

private:
    unordered_map<string, list<string>> empleos; // Mapea empleo a lista de personas
    unordered_map<string, set<string>> personas; // Mapea persona a conjunto de empleos
    unordered_map<string, unordered_map<string, list<string>::iterator>> iteradores; // Mapea (empleo, persona) a iterador en lista
};



bool tratar_caso() {
    OficinaEmpleo oe;
    string comando;
    cin >> comando;

    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "altaOficina") {
                string nombre, empleo;
                cin >> nombre >> empleo;
                oe.altaOficina(nombre, empleo);
            }
            else if (comando == "ofertaEmpleo") {
                string empleo;
                cin >> empleo;
                string persona = oe.ofertaEmpleo(empleo);
                cout << empleo << ": " << persona << "\n";
            }
            else if (comando == "listadoEmpleos") {
                string persona;
                cin >> persona;
                vector<string> empleos = oe.listadoEmpleos(persona);
                cout << persona << ":";
                for (const string& e : empleos) {
                    cout << " " << e;
                }
                cout << "\n";
            }
        }
        catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> comando;
    }
    cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("X71.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}