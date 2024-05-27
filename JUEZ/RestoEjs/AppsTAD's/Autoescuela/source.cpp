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
#include <algorithm>

using namespace std;

/*
 * Implementación del TAD Autoescuela
 */


class Autoescuela {
private:
    // Coloca aquí los atributos y métodos privados de la clase.
    struct InfoAlumno {
        string profesor;
        int puntuacion;
    };

    unordered_map<string, InfoAlumno> alumnos;
    unordered_map<string, map<int, list<string>>> profesores;

    InfoAlumno& alumno_matriculado(const string& alumno){
        auto it = alumnos.find(alumno);
        if (it == alumnos.end()) {
            throw domain_error("El alumno " + alumno + " no esta matriculado");
        }
        else {
            return it->second;
        }
    }

    const InfoAlumno& alumno_matriculado(const string& alumno) const{
        auto it = alumnos.find(alumno);
        if (it == alumnos.end()) {
            throw domain_error("El alumno " + alumno + " no esta matriculado");
        }
        else {
            return it->second;
        }
    }

public:
    // Constructor: al comienzo ningún profesor tiene asignados alumnos.
    Autoescuela() {}
    // ¡No olvides el coste de las operaciones!
    void alta(const string& alumno, const string& profesor) {
        auto it = alumnos.find(alumno);
        if (it == alumnos.end()) { //si el alumno no existía
            alumnos[alumno] = {profesor,0};
            profesores[profesor][0].push_back(alumno);
        }
        else { //si existe, cambia de profesor
            string profesor_anterior = alumnos[alumno].profesor;
                    alumnos[alumno].profesor = profesor;
                    //actualizar la lista de alumnos del profesor antiguo
                    profesores[profesor_anterior][it->second.puntuacion].remove(alumno);
                    //darlo de alta en el nuevo profesor
                    profesores[profesor][it->second.puntuacion].push_back(alumno);
        }
    }

    // es_alumno(A, P): Comprueba si el alumno A está matriculado actualmente con el profesor P.
    bool es_alumno(const string& alumno, const string& profesor) const {
        auto it = alumnos.find(alumno);
        return (it != alumnos.end() && it->second.profesor == profesor);
    }
    // puntuacion(A): Devuelve los puntos que tiene el alumno A.
    int puntuacion(const string& alumno) const {
        InfoAlumno it = alumno_matriculado(alumno);
        return it.puntuacion;
    }
    
    // actualizar(A, N): Aumenta en una cantidad N la puntuación del alumno A.
    void actualizar(const string& alumno, int puntos) {
        InfoAlumno &it = alumno_matriculado(alumno);

        string profesor = it.profesor;
        int puntuacion_actual = it.puntuacion;
        int nueva_puntuacion = puntuacion_actual + puntos;

        // Eliminar de la lista de la puntuación actual
        profesores[profesor][puntuacion_actual].remove(alumno);
        if (profesores[profesor][puntuacion_actual].empty()) {
            profesores[profesor].erase(puntuacion_actual);
        }

        // Añadir a la lista de la nueva puntuación
        profesores[profesor][nueva_puntuacion].push_back(alumno);

        // Actualizar la puntuación del alumno
        it.puntuacion = nueva_puntuacion;

    }

    // examen(P, N): Obtiene una lista con los alumnos del profesor P que se presentarán a examen.
    vector<string> examen(const string& profesor, int puntos_minimos) const {
        vector<string> result;
        auto it_profesor = profesores.find(profesor);
        if (it_profesor != profesores.end()) {
            for (auto it = it_profesor->second.lower_bound(puntos_minimos); it != it_profesor->second.end(); ++it) {
                result.insert(result.end(), it->second.begin(), it->second.end());
            }
        }

        sort(result.begin(), result.end());
        return result;
    }

    // aprobar(A): El alumno A aprueba el examen y es borrado de la autoescuela.
    void aprobar(const string& alumno) {
        InfoAlumno it = alumno_matriculado(alumno);

        string profesor = it.profesor;
        int puntuacion = it.puntuacion;

        // Eliminar del profesor
        profesores[profesor][puntuacion].remove(alumno);
        if (profesores[profesor][puntuacion].empty()) {
            profesores[profesor].erase(puntuacion);
        }

        // Eliminar del mapa de alumnos
        alumnos.erase(alumno);
    }
    
};


//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------


// Función que trata un caso de prueba.
bool tratar_caso() {
    Autoescuela a;

    string operacion; cin >> operacion;

    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "alta") {
                string alumno, profesor; cin >> alumno >> profesor;
                a.alta(alumno, profesor);
            }
            else if (operacion == "es_alumno") {
                string alumno, profesor; cin >> alumno >> profesor;
                if (a.es_alumno(alumno, profesor)) 
                    cout << alumno << " es alumno de " << profesor << "\n";
                else 
                    cout << alumno << " no es alumno de " << profesor << "\n";
                
            }
            else if (operacion == "examen") {
                string profesor; int p; cin >> profesor >> p;
                auto lista = a.examen(profesor, p);
                cout << "Alumnos de " << profesor << " a examen:" << "\n";
                for (auto alumno : lista)
                    cout << alumno << "\n";
            }
            else if (operacion == "actualizar") {
                string alumno; int p; cin >> alumno >> p;
                a.actualizar(alumno, p);
            }
            else if (operacion == "puntuacion") {
                string alumno; cin >> alumno;
                int n = a.puntuacion(alumno);
                cout << "Puntuacion de " << alumno << ": " << n << "\n";
            }
            else if (operacion == "aprobar") {
                string alumno; cin >> alumno;
                a.aprobar(alumno);
            }
        }
        catch (exception& e) {
            cout << "ERROR" <<"\n";
        }

        cin >> operacion;
    }

    cout << "---\n";

    return true;
} // tratar_caso

int main() {
#ifndef DOMJUDGE
    std::ifstream in("X63.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}