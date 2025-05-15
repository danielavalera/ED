#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;


using Estudiante = std::string;
using Curso = std::string;

class Academia {
public:

    //O(1)
    void anyadir_curso(const std::string& nombre, int numero_plazas) {
        // Implementar
        if (cursos.find(nombre) != cursos.end()) //O(1)
            throw std::domain_error("CURSO DUPLICADO");
        //cursos.find(nombre) == cursos.end();
        InfoCurso info;
        info.num_plazas = numero_plazas;
        info.alumnos_matriculados = {};
        //cursos.insert({ nombre, info });
        //cursos[nombre] = info;
        cursos[nombre] = { numero_plazas, {} }; //O(1)

    }

    //O(1)
    void anyadir_estudiante(const Estudiante& id_est, const string& apellidos) {
        if (estudiantes.find(id_est) != estudiantes.end())
            throw std::domain_error("ESTUDIANTE PRESENTE EN LA BASE DE DATOS");
        estudiantes[id_est] = { apellidos, {} };
    }

    //O(E*logC)
    void eliminar_curso(const Curso& curso) {
        // Implementar
        if (cursos.find(curso) == cursos.end())
            throw std::domain_error("CURSO NO ENCONTRADO");
        for (Estudiante est : cursos[curso].alumnos_matriculados) {//E vueltas
            estudiantes[est].cursos_matriculados.erase(curso);//O(logC)
        }
        cursos.erase(curso);
    }

    //O(1)
    int plazas_libres(const Curso& curso) const {
        if (cursos.find(curso) == cursos.end())
            throw std::domain_error("CURSO NO ENCONTRADO");
        InfoCurso info = cursos.at(curso);
        return info.num_plazas - info.alumnos_matriculados.size();
    }

    //O(logE + logC)
    void matricular_en_curso(const Estudiante& est, const Curso& curso) {
        if (cursos.find(curso) == cursos.end()) //O(1)
            throw std::domain_error("CURSO NO ENCONTRADO");
        if (cursos[curso].alumnos_matriculados.find(est) !=  //O(logE)
            cursos[curso].alumnos_matriculados.end())
            throw std::domain_error("ALUMNO YA MATRICULADO");
        if (plazas_libres(curso) <= 0) { //O(1)
            cursos[curso].lista_de_espera.push_back(est);//O(1)
            estudiantes[est].cursos_en_espera.insert(curso); //O(1)
        }
        cursos[curso].alumnos_matriculados.insert(est); //O(logE)
        estudiantes[est].cursos_matriculados.insert(curso); //O(logC)
    }

    //O(E)
    std::vector<Estudiante> estudiantes_matriculados(const Curso& curso) const {

        if (cursos.find(curso) == cursos.end())
            throw std::domain_error("CURSO NO ENCONTRADO");
        InfoCurso info = cursos.at(curso);
        vector<Estudiante> estudiantes(info.alumnos_matriculados.size());
        for (auto est : info.alumnos_matriculados) { //E vueltas
            estudiantes.push_back(est); //O(1)
        }
        /*InfoCurso info = cursos.at(curso);
        for (auto p = info.alumnos_matriculados.begin(); p != info.alumnos_matriculados.end(); p++) {
            estudiantes.push_back(*p);
        }*/
        return estudiantes;
    }

    //De forma alfabetica. O(C)
    std::vector<Curso> cursos_estudiante(const Estudiante& id_est) {
        if (estudiantes.find(id_est) == estudiantes.end())
            throw std::domain_error("ESTUDIANTE NO EXISTENTE");
        std::vector<Curso> cursos(estudiantes[id_est].cursos_matriculados.size());
        for (Curso c : estudiantes[id_est].cursos_matriculados) {//C vueltas
            cursos.push_back(c); //O(1)
        }
        return cursos;
    }

    //O(logE + logC)
    void dar_de_baja_en_curso(const Estudiante& est_id, const std::string& curso) {
        if (cursos.find(curso) == cursos.end())
            throw std::domain_error("CURSO NO ENCONTRADO");
        if (estudiantes.find(est_id) == estudiantes.end() ||
            estudiantes[est_id].cursos_matriculados.find(curso) 
                  == estudiantes[est_id].cursos_matriculados.end())
            throw std::domain_error("ESTUDIANTE NO MATRICULADO");
        cursos[curso].alumnos_matriculados.erase(est_id);//O(logE)
        estudiantes[est_id].cursos_matriculados.erase(curso);//O(logC)

        if (!cursos[curso].lista_de_espera.empty()) {
            Estudiante nuevo = cursos[curso].lista_de_espera.front();
            cursos[curso].lista_de_espera.pop_front();
            cursos[curso].alumnos_matriculados.insert(nuevo);
            estudiantes[nuevo].cursos_en_espera.erase(curso);
            estudiantes[nuevo].cursos_matriculados.insert(curso);
        }
    }

    void alumno_se_cansa_de_esperar(const Estudiante& cansado) {
        if (estudiantes.find(cansado) == estudiantes.end())
            throw std::domain_error("ALUMNO NO EXISTENTE");
        for (Curso c : estudiantes[cansado].cursos_en_espera) {// C vueltas
            cursos[c].lista_de_espera.remove(cansado); //O(E)
        }
        estudiantes[cansado].cursos_en_espera = {};
    }


private:
    // Añadir los atributos y métodos auxiliares necesarios
    struct InfoCurso {
        int num_plazas;
        set<Estudiante> alumnos_matriculados;
        list<Estudiante> lista_de_espera;
    };

    struct InfoEstudiante {
        string apellidos;
        set<Curso> cursos_matriculados;
        unordered_set<Curso> cursos_en_espera;
    };

    unordered_map<Curso, InfoCurso> cursos; 
    unordered_map<Estudiante, InfoEstudiante> estudiantes;
};


using namespace std;

int main() {
    Academia ac;

    ac.anyadir_curso("Introducción a la rubismática", 20);
    ac.anyadir_curso("Fundamentos de pastificio", 2);
    ac.matricular_en_curso("Genaro Pérez", "Introducción a la rubismática");
    ac.matricular_en_curso("Santiago Carvajal", "Introducción a la rubismática");
    ac.matricular_en_curso("Mireia Casado", "Introducción a la rubismática");

    ac.matricular_en_curso("Genaro Pérez", "Fundamentos de pastificio");

    cout << ac.plazas_libres("Introducción a la rubismática") << endl;
    for (const Estudiante& e : ac.estudiantes_matriculados("Introducción a la rubismática")) {
        cout << e << endl;
    }

    return 0;
}