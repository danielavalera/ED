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
class AcademiaChino {
public:
	AcademiaChino() : grupos(7) {}

	// O(1)
	void nuevo_estudiante(const string& dni, const int& grupo) {
		if (alumnos.count(dni)) {
			throw domain_error("Estudiante existente");
		}
		if (grupo < 1 || grupo > 6) {
			throw domain_error("Grupo incorrecto");
		}
		grupos[grupo].push_front(dni);
		alumnos.insert({ dni, {grupo,false,grupos[grupo].begin()} });
	}

    
	// O(1)
	void promocionar(const string& dni) {
        InfoAlumno& info_alumno = buscar_alumno(dni);

        int& grupo_alumno = info_alumno.grupo;
        int grupo_antes = grupo_alumno;
        grupo_alumno++;

        list<string>& lista_antes = grupos[grupo_antes];
        lista_antes.erase(info_alumno.it_alumno);
        if (grupo_alumno > 6) {
            info_alumno.grupo = 0;
            info_alumno.graduado = true;
        }
        grupos[grupo_alumno].push_front(dni);
        info_alumno.it_alumno = grupos[grupo_alumno].begin();
	}

	// O(1)
	int grupo_estudiante(const string& dni) {
        auto it = buscar_alumno(dni);
		return it.grupo;
	}

	// O(1)
	vector<string> graduados() const {
		vector<string> ranking;

        for (auto s : grupos[0]) 
            ranking.push_back(s);
        sort(ranking.begin(), ranking.end());

		return ranking;
	}

	// O(1)
	string novato(const int& grupo) const {
        if (grupo < 1 || grupo > 6) {
            throw domain_error("Grupo incorrecto");
        }
        if (grupos[grupo].empty()) {
            throw domain_error("Grupo vacio");
        }
        return grupos[grupo].front();
	}


private:
	struct InfoAlumno {
		int grupo;
		bool graduado;
		list<string>::iterator it_alumno;
	};
	unordered_map<string, InfoAlumno> alumnos;
	vector<list<string>> grupos;
    //los graduados los almacenos en grupos[0]

    InfoAlumno& buscar_alumno(const string& dni) {
        auto it = alumnos.find(dni);
        if (it == alumnos.end()) {
            throw domain_error("Estudiante no existente");
        }
        else if (it->second.graduado == true) {
            throw domain_error("Estudiante ya graduado");
        }
        else {
            return it->second;
        }
    }
};


// Función para tratar un caso de prueba. Devuelve false si, en lugar de un
// caso de prueba, se ha encontrado con la marca de fin de entrada
// (EOF). Devuelve true en caso contrario.
bool tratar_caso() {
    AcademiaChino ac;
    string operacion;
    cin >> operacion;

    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "nuevo_estudiante") {
                string dni;
                int grupo;
                cin >> dni >> grupo;
                ac.nuevo_estudiante(dni, grupo);
            }
            else if (operacion == "promocionar") {
                string dni; cin >> dni;
                ac.promocionar(dni);
            }
            else if (operacion == "grupo_estudiante") {
                string dni; cin >> dni;
                int grupo = ac.grupo_estudiante(dni);
                cout << dni << " esta en el grupo " << grupo << "\n";
            }
            else if (operacion == "novato") {
                int grupo; cin >> grupo;
                string novato = ac.novato(grupo);
                cout << "Novato de " << grupo << ": " << novato << "\n";
            }
            else if (operacion == "graduados") {
                auto lista = ac.graduados();
                cout << "Lista de graduados: ";
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
    std::ifstream in("X69.txt");
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


