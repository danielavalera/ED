/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  //@ <answer>
  /*
    Indica el nombre y apellidos de los componentes del grupo
    ---------------------------------------------------------
    Componente 1: Sánchez Guerra, Sara
    Componente 2: Valera Fuentes, Daniela Valentina
  */
  //@ </answer>

#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 


/*
  Implementación de listas doblemente enlazadas circulares

  https://github.com/manuelmontenegro/ED/blob/main/lineales/list_linked_double_v4/list_linked_double.h

*/

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    // Implementa este método más abajo
    void sort_and_dedup();

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);

    // Métodos privados. Impleméntalos más abajo
    Node* minimum(Node* begin, Node* end) const;
    void detach(Node* n);
    void attach(Node* n, Node* position);
};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

//El coste es lineal, O(n), donde n es nº de nodos contenidos entre begin() y end()
ListLinkedDouble::Node* ListLinkedDouble::minimum(Node* begin, Node* end) const {
    Node* curr = begin;
    Node* min = begin;

    while (curr != end->next) {
        if (curr->value <= min->value) {
            min = curr;
        }
        curr = curr->next;
    };
    return min;
}

//El coste es constante, O(1), ya que solo cambiamos los punteros del nodo que se pasa por parámetro, sin acceder a más nodos
void ListLinkedDouble::detach(Node* n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    num_elems--;
}

//El coste es constante, O(1), ya que solo cambiamos los punteros del nodo n (nodo que queremos añadir) y del nodo position (nodo al que se lo queremos añadir) sin recorrer la lista
void ListLinkedDouble::attach(Node* n, Node* position) {
    n->next = position->prev->next;
    n->prev = position->prev;
    position->prev->next = n;
    position->prev = n;
    num_elems++;
}

//El coste es cuadrático, O(n^2), ya que tiene que recorrer la lista (O(n)) y por cada iteración volver a recorrer la lista con el método minimun (O(m)),
//además de las operaciones detach() y attach().
void ListLinkedDouble::sort_and_dedup() {
    Node* current = head->next;

    while (current != head) { //O(n), donde n es el número de elementos de la lista
        Node* min = minimum(current, nth_node(size() - 1)); //O(m), donde m es el tamaño del rango de la lista

        if (min == current) {
            current = current->next;
        }
        else {
            if (current->prev->value == min->value || current->value == min->value) {
                detach(min); //O(1)
                delete min; //O(1)
            }else {
                detach(min); //O(1)
                attach(min, current); //O(1)
            } 
        }
    }
    display();
    std::cout << '\n';
}

using namespace std;

// Implementa aquí la función para tratar UN caso de prueba. La función `main`
// llamará a esta función `tratar_caso` tantas veces como casos de prueba hay
// en la entrada.

void tratar_caso() {
    int n; cin >> n;
    ListLinkedDouble ls;

    while (n != -1) {
        ls.push_back(n);
        cin >> n;
    }

    ls.sort_and_dedup();
}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {

    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("datosL03.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // La entrada comienza con el número de casos de prueba.
    int num_casos;
    cin >> num_casos;

    // Llamamos tantas veces a `tratar_caso` como nos diga el número.
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}