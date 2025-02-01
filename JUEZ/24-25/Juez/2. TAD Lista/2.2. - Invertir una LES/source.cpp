#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
using namespace std;
class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) {}
    ListLinkedSingle(vector<int> v) {
        if (v.size() > 0) {
            Node* node = new Node;
            Node* next_node = new Node;
            node->value = v[0];
            this->head = node;
            for (int i = 1; i < v.size(); i++) {
                next_node = new Node;
                next_node->value = v[i];
                node->next = next_node;
                node = next_node;
            }
            node->next = nullptr; // para el ultimo elemento
        }
        else {
            this->head = nullptr;
        }
    }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) {
    }

    void duplicate();
    void reverse();
    //void intersect(const ListLinkedSingle& other);

    void push_front(const int& elem) {
        Node* new_node = new Node;
        new_node->value = elem;
        new_node->next = head;
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    //void invertir(Node* node, Node* next);
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
    void display() const {
        display(std::cout);
    }
    Node* head;

private:
    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node;
        result->value = start_node->value;
        result->next = copy_nodes(start_node->next);
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
    Node* new_node = new Node;
    new_node->value = elem;
    new_node->next = nullptr;
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

void ListLinkedSingle::duplicate() {
    Node* current = head;
    while (current != nullptr) {
        Node* aux = new Node;
        aux->value = current->value;
        aux->next = current->next;
        current->next = aux;
        current = current->next->next;
    }
}

void ListLinkedSingle::reverse() {
    Node* cur = this->head;
    Node* prev = nullptr;

    while (cur != nullptr) {
        Node* sig = cur->next;
        cur->next = prev;
        prev = cur;
        cur = sig;
    }
    this->head = prev;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    ListLinkedSingle xs;
    int elem; cin >> elem;
    while (elem != 0) {
        xs.push_back(elem);
        cin >> elem;
    }

    xs.reverse();
    xs.display();
    cout << "\n";

}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("2.2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    // La entrada comienza con el número de casos de prueba.
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
