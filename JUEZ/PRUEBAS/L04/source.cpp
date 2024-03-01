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
    Componente 1:
    Componente 2:
  */
  //@ </answer>

  /*
    En este ejercicio solamente pueden utilizarse las colecciones vistas durante
    esta semana: pilas, colas, o dobles colas.

    En lugar de utilizar las implemtaciones vistas en clase, utilizad las que
    vienen implementadas en la biblioteca estándar de C++, que son las
    siguientes:

    - queue, definida en el fichero de cabecera <queue>
      Documentación: https://en.cppreference.com/w/cpp/container/queue

    - stack, definida en el fichero de cabecera <stack>
      Documentación: https://en.cppreference.com/w/cpp/container/stack

    - deque, definida en el fichero de cabecera <deque>
      Documentación: https://en.cppreference.com/w/cpp/container/deque

    Añade los #include con los ficheros de cabecera del TAD o los TADs que
    vais a utilizar, aunque estén fuera de las etiquetas <answer>...</answer>.
  */


#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <utility>


using namespace std;



//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------


// Añade los tipos de datos auxiliares y funciones que necesites

/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementación del TAD Cola mediante listas enlazadas.
  */

#ifndef __QUEUE_LINKEDLIST_H
#define __QUEUE_LINKEDLIST_H

#include <cassert>
#include <iostream>

template <typename T> class QueueLinkedList {
public:
    QueueLinkedList() : front_node(nullptr), back_node(nullptr) {}
    QueueLinkedList(const QueueLinkedList& other) {
        copy_nodes_from(other.front_node);
    }

    ~QueueLinkedList() { free_nodes_from(front_node); }

    QueueLinkedList& operator=(const QueueLinkedList& other) {
        if (this != &other) {
            free_nodes_from(front_node);
            copy_nodes_from(other.front_node);
        }
        return *this;
    }

    void push(const T& elem) {
        Node* new_node = new Node{ elem, nullptr };
        if (back_node == nullptr) {
            back_node = new_node;
            front_node = new_node;
        }
        else {
            back_node->next = new_node;
            back_node = new_node;
        }
    }

    void pop() {
        assert(front_node != nullptr);
        Node* target = front_node;
        front_node = front_node->next;
        if (back_node == target) {
            back_node = nullptr;
        }
        delete target;
    }

    T& front() {
        assert(front_node != nullptr);
        return front_node->value;
    }

    const T& front() const {
        assert(front_node != nullptr);
        return front_node->elem;
    }

    bool empty() const { return (front_node == nullptr); }

private:
    struct Node {
        T value;
        Node* next;
    };

    void copy_nodes_from(Node* other);
    void free_nodes_from(Node* other);

    Node* front_node;
    Node* back_node;
};

template <typename T> void QueueLinkedList<T>::copy_nodes_from(Node* other) {
    if (other == nullptr) {
        front_node = nullptr;
        back_node = nullptr;
    }
    else {
        front_node = new Node{ other->value, nullptr };
        back_node = front_node;
        Node* current = other->next;
        while (current != nullptr) {
            Node* new_node = new Node{ current->value, nullptr };
            back_node->next = new_node;
            current = current->next;
            back_node = new_node;
        }
    }
}

template <typename T> void QueueLinkedList<T>::free_nodes_from(Node* other) {
    Node* current = other;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}


/*
 * Implementación del TAD Doble Cola utilizando una lista
 * doblemente enlazada con nodo fantasma.
 */

template <typename Elem> class Dequeue {
private:
    struct Node {
        Elem value;
        Node* next;
        Node* prev;
    };

public:
    Dequeue() {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    Dequeue(const Dequeue& other) : Dequeue() { copy_nodes_from(other); }

    ~Dequeue() { delete_nodes(); }

    void push_front(const Elem& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
    }

    void push_back(const Elem& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
    }

    void pop_front() {
        assert(head->next != head);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
    }

    void pop_back() {
        assert(head->next != head);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
    }

    bool empty() const { return head->next == head; };

    const Elem& front() const {
        assert(head->next != head);
        return head->next->value;
    }

    Elem& front() {
        assert(head->next != head);
        return head->next->value;
    }

    const Elem& back() const {
        assert(head->next != head);
        return head->prev->value;
    }

    Elem& back() {
        assert(head->next != head);
        return head->prev->value;
    }

    Dequeue& operator=(const Dequeue& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
        }
        return *this;
    }

private:
    Node* head;

    void delete_nodes();
    void copy_nodes_from(const Dequeue& other);
};

template <typename Elem> void Dequeue<Elem>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename Elem>
void Dequeue<Elem>::copy_nodes_from(const Dequeue& other) {
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

#endif



// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.

int personasPendientes(Dequeue<char>& exs, QueueLinkedList<char>& conds, int t) {
    int countPerPendientes = 0;
    Dequeue<char>::Node* current = exs.head->next;

    for (int i = 0; i < t; i++) //según los días (t)
    {
        while (current->value == 'G' || current->value == 'B' || current->value == 'A') {
            char exAux = exs.front();
            char condAux = conds.front();
            exs.pop_front();

            if (exAux == 'A') {
                if (condAux == 'M') {
                    conds.pop();
                    conds.push(condAux);
                }
                else {
                    conds.pop();
                }
                    
            }
            /*else if (exAux == 'B') {

            }*/
            else {
                conds.pop();
                conds.push(condAux);
            }
        }
    }

    /*while (!conds.empty()) {
        countPerPendientes++;
        conds.pop();
    }*/

    return countPerPendientes;
}

bool tratar_caso() {
    int n, m, t; cin >> n >> m >> t;

    if (!cin) return false;

    char examinador, conductor;
    Dequeue<char> examinadores; //porq nos interesa iterar siempre en la misma lista
    QueueLinkedList<char> conductores;

    for (int i = 0; i < n; i++)
    {
        cin >> examinador;
        examinadores.push_back(examinador);
    }

    for (int i = 0; i < m; i++)
    {
        cin >> conductor;
        conductores.push(conductor);
    }

    cout << personasPendientes(examinadores, conductores, t) << "\n";

    return true;
}

// ----------------------------------------------
// No modificar a partir de la línea
// ----------------------------------------------
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
    std::ifstream in("datosL04.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Ejecutamos tratar_caso() hasta que nos devuelva `false`
    while (tratar_caso()) {}

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
