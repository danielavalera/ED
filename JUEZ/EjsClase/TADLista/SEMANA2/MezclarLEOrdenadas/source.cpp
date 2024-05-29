// Mezclar dos listas enlazadas
// ----------------------------
// Estructuras de datos

#include <iostream>
#include <cassert>
#include <fstream>

/*
 * Implementación del TAD Lista mediante listas enlazadas simples.
 */

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() {
        head = new Node;
        head->next = nullptr;
    }

    ~ListLinkedSingle() { delete_list(head); }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) {}

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next };
        head->next = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head->next != nullptr);
        Node* old_head = head->next;
        head->next = head->next->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const { return head->next == nullptr; };

    const int& front() const {
        assert(head->next != nullptr);
        return head->next->value;
    }

    int& front() {
        assert(head->next != nullptr);
        return head->next->value;
    }

    const int& back() const { return last_node()->value; }

    int& back() { return last_node()->value; }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    void merge(ListLinkedSingle& other);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;
};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    last_node()->next = new_node;
}

void ListLinkedSingle::pop_back() {
    assert(head->next != nullptr);
    Node* previous = head;
    Node* current = head->next;

    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    delete current;
    previous->next = nullptr;
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head->next;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}

ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head->next != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}


// Implementa aquí la función pedida
void ListLinkedSingle::merge(ListLinkedSingle& l2) {
    // prev = Ultimo nodo de la lista ya mezclada
    // cur = Primer nodo de la lista this que aun no ha sido mezclado
    // other = Primer nodo de la lista l2 que aun no ha sido mezclado
    Node* prev, * cur = head->next, * other = l2.head->next;
    if (head->next == nullptr) {
        // Si la lista this es vacia, enlazamos this.head con l2, de modo
        // que todos los nodos de l2 pasan a formar parte de this.
        head->next = l2.head->next;
        head = head->next;
        // La lista l2 se queda sin nodos.
        l2.head->next = nullptr;
    }
    else if (l2.head->next == nullptr) {
        // Si la lista l2 es vacia, no hacemos nada. La lista this se queda
        // con sus nodos (que ya estaban ordenados inicialmente), y la lista
        // l2 se sigue quedando vacia
        head = head->next;
    }
    else {
        // Si ambas listas no son vacias, inicializamos prev, cur y other
        if (head->next->value <= l2.head->next->value) {
            prev = head->next;
            cur = head->next->next;
            other = l2.head->next;
            head = head->next;
        }
        else {
            prev = l2.head->next;
            cur = head->next;
            other = l2.head->next->next;
            head = l2.head->next;
        }
        // Bucle que va construyendo la lista
        while (cur != nullptr && other != nullptr) {
            if (cur->value <= other->value) {
                prev->next = cur;
                prev = cur;
                cur = cur->next;
            }
            else {
                prev->next = other;
                prev = other;
                other = other->next;
            }
        }
        // Cuando salimos del bucle anterior, uno de los dos
        // punteros (cur u other) es nulo. Tenemos que enganchar
        // prev con aquel que NO sea nulo.
        if (cur == nullptr) {
            prev->next = other;
        }
        else {
            prev->next = cur;
        }
        // La lista l2 se queda sin nodos, porque todos han pasado
        // a formar parte de this
        l2.head->next = nullptr;
    }
}


using namespace std;


// Función para tratar un caso de prueba
void tratar_caso() {
    ListLinkedSingle l1,l2;
    int n; cin >> n;

    while (n != 0) {
        l1.push_back(n);
        cin >> n;
    }
    cin >> n;
    while (n != 0) {
        l2.push_back(n);
        cin >> n;
    }
    
    l1.merge(l2);
    l1.display();
    cout << "\n";
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("X11.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}