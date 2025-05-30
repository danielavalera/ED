#include <cassert>
#include <iostream>
#include <vector>
#include<fstream>
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
    void mezclar(ListLinkedSingle& other);

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

void ListLinkedSingle::mezclar(ListLinkedSingle& other) {
    Node* prev = head;
    Node* prev_other = nullptr;

    Node* curr = head;
    Node* curr_other = other.head;


    while (curr != nullptr && curr_other != nullptr) {
        if (curr->value < curr_other->value) {
            prev = curr;
            curr = curr->next;
        }
        else if (curr->value > curr_other->value) {
            if (curr == head) {
                head = curr_other;
            }
            else {
                prev->next = curr_other;
            }

            prev = curr_other;
            if (curr_other == other.head)
                other.head = curr_other->next;
            curr_other = curr_other->next;
            prev->next = curr;
        }
        else {
            if (prev_other != nullptr) {
                prev_other->next = curr_other;
            }
            prev_other = curr_other;

            curr_other = curr_other->next;
            prev = curr;
            curr = curr->next;
        }
    }

    if (curr_other != nullptr) {
        if (head == nullptr) 
            head = curr_other;
        else
            prev->next = curr_other;
        if (prev_other != nullptr) {
            prev_other->next = nullptr;
        }
        else {
            other.head = nullptr;
        }
    }
}




void resuelveCaso() {
    ListLinkedSingle list1, list2;

    //this
    int n;
    vector<int> v1;
    while (cin >> n && n != 0) v1.push_back(n);
    for (int j = 0; j < v1.size(); ++j) list1.push_front(v1[v1.size() - 1 - j]);


    //other
    vector<int> v2;
    while (cin >> n && n != 0) v2.push_back(n);
    for (int j = 0; j < v2.size(); ++j) list2.push_front(v2[v2.size() - 1 - j]);

    //entramar
    list1.mezclar(list2);
    if (!list1.empty()) list1.display(); else std::cout << "[]";
    std::cout << std::endl;
    if (!list2.empty()) list2.display(); else std::cout << "[]";
    std::cout << std::endl;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("control.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}