#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
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
        : head(copy_nodes(other.head)) { }

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

    void entramar(ListLinkedSingle& other);

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
    out << "]\n";
}

void ListLinkedSingle::entramar(ListLinkedSingle& other) {
    Node* curThis = head;
    Node* curOther = other.head;
    Node* nextThis = nullptr;
    Node* nextOther = nullptr;
    Node* lastNodeThis = nullptr;

    if (head != nullptr && other.head != nullptr) {
        nextThis = head->next;
        nextOther = other.head->next;

        while (curThis != nullptr && curOther != nullptr) {
            //actualizamos punteros de next
            nextThis = curThis->next;
            nextOther = curOther->next;

            //desenganchamos de la lista other
            other.head = curOther->next;
            curOther->next = nextThis;
            //enganchamos de other a this
            curThis->next = curOther;

            //actualizamos punteros de cur y lastNodeThis
            lastNodeThis = curThis->next;
            curThis = nextThis;
            curOther = nextOther;
        }
    }

    if (curOther != nullptr) {
        lastNodeThis->next = curOther;
        other.head = nullptr;
    }
    
}



void resuelvecaso() {
    ListLinkedSingle list1, list2;

    //this
    int n;
    cin >> n;
    vector<int> v1(n);
    for (int j = 0; j < n; ++j) cin >> v1[j];
    for (int j = 0; j < n; ++j) list1.push_front(v1[n - 1 - j]);


    //other
    int m;
    cin >> m;
    vector<int> v2(m);
    for (int j = 0; j < m; ++j) cin >> v2[j];
    for (int j = 0; j < m; ++j) list2.push_front(v2[m - 1 - j]);

    //entramar
    list1.entramar(list2);

    list1.display();
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("2.4.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelvecaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}