//-------------------------------------------------------
// Problema ED. Facultad de inform�tica (UCM)
//


#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <cctype>
using namespace std;


//O(n) en el número de lineas.
int comprueba_indentacion(const list<pair<int, char>> lineas) {

    auto it = lineas.begin(); //Comenzamos a recorrer la lista desde la primera linea.

    stack<int> indentacion; //Debemos usar una pila de int, porque tenemos que ir recordando la indentacion de los '{' encontrados, siguiendo un orden LIFO.
                            //hasta que lo desapilemos. 
    indentacion.push(0); //Ademas la primera indentacion a considerar hasta encontrar algun '{' debe ser 0.


    int linea_actual = 1; //Para saber la linea actual, comenzando en 1. 

    while (it != lineas.end()) {
        auto [indent, primera_letra] = *it;
        if ( primera_letra == '{') {  //Si la primera letra de la linea es {, la indentación debe ser superior a la actual. 
            if (indent <= indentacion.top()) { //Si la indentacion es menor o igual a la actual
                return linea_actual;           //entonces hemos encontrado un error en esta linea.
            }
            indentacion.push(indent); //Abrimos un nuevo bloque con {, por lo tanto guardamos 
                                      //la nueva indentación requerida en las siguientes lineas hasta encontrar }.
        }
        else { //Si no es {, la indentación debe ser igual a la actual.
            if (indent != indentacion.top()) { //Si es distinta,
                return linea_actual;           //hemos encontrado un error en esta linea.
            }
            if (primera_letra== '}') { //Si es }, estamos cerrando el bloque actual:
                indentacion.pop(); //Por lo tanto, recuperamos la indentación anterior. 
            }
        }
        ++it; //avanzamos el iterador.
        ++linea_actual; //aumentamos la linea actual
    }
    //Si el bucle termina, no se ha encontrado ningun error.
    return -1;
}

bool tratar_caso() {
    int num_lineas;
    cin >> num_lineas;

    if (num_lineas == 0) return false;

    list<pair<int, char>> lineas;
    cin.ignore(10, '\n');
    for (int i = 0; i < num_lineas; i++) {
        string l;
        getline(cin, l);
        int indent = 0;
        while (isspace(l[indent])) {
            indent++;
        }
        lineas.push_back({ indent, l[indent] });
    }

    int result = comprueba_indentacion(lineas);

    if (result == -1) {
        cout << "CORRECTO\n";
    }
    else {
        cout << result << "\n";
    }

    return true;
}

int main() {
    while (tratar_caso()){}

    return 0;
}
