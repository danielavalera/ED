#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>

using namespace std;

class Urgencias {
public:

    Urgencias() : lista_espera(3) { }; // O(1)

    void nuevo_paciente(const string& paciente, int gravedad) {
        if (pacientes.count(paciente))  // O(1)
            throw domain_error("Paciente repetido");
        if (gravedad < 1 || gravedad > 3) 
            throw domain_error("Gravedad incorrecta");

        auto it = lista_espera[gravedad - 1].insert(lista_espera[gravedad - 1].end(), paciente);  // O(1)
        pacientes[paciente] = { gravedad, it }; // O(1)
    }

    int gravedad_actual(const string& paciente) const {
        return buscar_paciente(paciente).gravedad;  // O(1)
    }

    string siguiente() {

        for (int i = 2; i >= 0; i--) {  // O(1) o lineal??
            if (!lista_espera[i].empty()) {
                string paciente = lista_espera[i].front(); // O(1)

                lista_espera[i].pop_front(); // O(1) //aplicas la mejora directamente
                pacientes.erase(paciente); // O(1)

                return paciente;
            }
        }

        throw domain_error("No hay pacientes");
    }

    void mejora(const string& paciente) {
        InfoPaciente& info = buscar_paciente(paciente); // O(1)

        if (info.gravedad == 1) {
            lista_espera[info.gravedad - 1].erase(info.it); // O(1) //eliminas A lo que apunta el iterador -> info.it se queda vacío
            pacientes.erase(paciente); // O(1)
            recuperados_.insert(paciente); // O(log n)
        }
        else {
            lista_espera[info.gravedad - 1].erase(info.it); // O(1) //eliminas A lo que apunta el iterador -> info.it se queda vacío
            info.gravedad--;
            info.it = lista_espera[info.gravedad - 1].insert(lista_espera[info.gravedad - 1].begin(), paciente); // O(1)  //le das el nuevo valor al iterador
        }
    }

    list<string> recuperados() {
        list<string> lista;

        for (auto paciente : recuperados_) // O(n)
            lista.push_back(paciente); // O(1)

        return lista;
    }

private:

    struct InfoPaciente {
        int gravedad;
        list<string>::iterator it;
    };

    unordered_map<string, InfoPaciente> pacientes;
    vector<list<string>> lista_espera;
    set<string> recuperados_;

    const InfoPaciente& buscar_paciente(const string& paciente) const {
        auto it = pacientes.find(paciente); // O(1)
        if (it == pacientes.end())  // O(1)
            throw domain_error("Paciente inexistente");

        return it->second;
    }

    InfoPaciente& buscar_paciente(const string& paciente) {
        auto it = pacientes.find(paciente); // O(1)
        if (it == pacientes.end())  // O(1)
            throw domain_error("Paciente inexistente");

        return it->second;
    }
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    Urgencias urgencias;
    string paciente;
    while (opcion != "FIN") {
        try {
            if (opcion == "nuevo_paciente") {
                int gravedad;
                cin >> paciente >> gravedad;
                urgencias.nuevo_paciente(paciente, gravedad);
            }
            else if (opcion == "gravedad_actual") {
                cin >> paciente;
                int gravedad = urgencias.gravedad_actual(paciente);

                cout << "La gravedad de " << paciente << " es " << gravedad << "\n";
            }
            else if (opcion == "siguiente") {
                string siguiente = urgencias.siguiente();

                cout << "Siguiente paciente: " << siguiente << "\n";
            }
            else if (opcion == "mejora") {
                cin >> paciente;
                urgencias.mejora(paciente);
            }
            else if (opcion == "recuperados") {
                list<string> sanos = urgencias.recuperados();

                cout << "Lista de recuperados: ";
                for (auto paciente : sanos) cout << paciente << " ";
                cout << "\n";
            }
        }
        catch (domain_error& exception) {
            cout << "ERROR: " << exception.what() << "\n";
        }
        cin >> opcion;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("8.2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
   system("PAUSE");
#endif
    return 0;
}