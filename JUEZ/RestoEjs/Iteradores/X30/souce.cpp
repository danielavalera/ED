// De postre, un chuletón
// ----------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <list>
#include <sstream>

using namespace std;


enum class Categoria { Primero, Segundo, Postre };

struct Plato {
    Categoria categoria;
    string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream& operator<<(ostream& out, const Plato& plato) {
    switch (plato.categoria) {
    case Categoria::Primero:
        out << "1";
        break;
    case Categoria::Segundo:
        out << "2";
        break;
    case Categoria::Postre:
        out << "P";
        break;
    }
    out << " " << plato.nombre;
    return out;
}


// Indica el coste en función del tamaño del parámetro de entrada
void ordenar_menu(list<Plato>& platos) {
    auto it = platos.begin();
    
    while (it != platos.end()) {
        auto it2 = ++platos.begin(); //está regu, igual tengo que actualizar los punteros en cada caso
        Plato plato; 
        if (it->categoria != Categoria::Primero) {
            if (it->categoria == Categoria::Segundo) {
                if (it2->categoria == Categoria::Primero) {
                    plato.categoria = it2->categoria;
                    plato.nombre = it2->nombre;
                    *it2 = *it;
                    it->categoria = plato.categoria;
                    it->nombre = plato.nombre;
                }
                else if (it2->categoria == Categoria::Postre) {
                    auto it3 = --platos.end();
                    //tengo que echarle un vistazo, y creo que general, porque no estoy controlando el orden en el que entran
                }
                else {
                    it++;
                }
            }
            else {
                it2 = --platos.end();
                plato.categoria = it2->categoria;
                plato.nombre = it2->nombre;
                *it2 = *it;
                it->categoria = plato.categoria;
                it->nombre = plato.nombre;
            }
        }
        else {
            it++;
        }
    }
}


bool tratar_caso() {
    // Introduce aquí el código para tratar un caso de prueba.
    // Devuelve false si ya no hay más casos de prueba que leer,
    // true en caso contrario.
    int n; cin >> n;
    
    if (n == 0) return false;

    char c;
    string p;
    Plato plato;
    list<Plato> platos;
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        switch (c) {
        case '1':
            plato.categoria = Categoria::Primero;
            break;
        case '2':
            plato.categoria = Categoria::Segundo;
            break;
        case 'P':
            plato.categoria = Categoria::Postre;
            break;
        }
        cin.ignore();
        getline(cin, p);
        plato.nombre = p;

        platos.push_back(plato);
    }
    
    ordenar_menu(platos);

    for (const auto & pl: platos)
    {
        cout << pl << "\n";
    }
    cout << "---" << "\n";
    return true;

}


int main() {
    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("X30.txt");
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

