#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>
#include <algorithm>
#include <string>

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}

using namespace std;

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

bool esPrimo(int n) {
    int i = 2;

    while (i < n) {
        if (n % i == 0) return false;
        i++;
    }

    return true;
}

bool esMultiplo(int n) {
    return (n % 7 == 0 && n != 7);
}

/*
  Primera componente: Elemento del nodo
  Segunda componente: Profundidad en el arbol de la primera componente
*/
pair<int, int> barreraPrimos(const BinTree<int>& arbol) {
    if (arbol.empty()) return { -1, 0 };
    if (esMultiplo(arbol.root())) return { arbol.root(), 1 }; //si el nodo actual es múltiplo de 7, devolvemos su valor y profundidad 1
    if (esPrimo(arbol.root())) return { -1, 0 }; //si el nodo actual es primo, no puede haber nodos accesibles más abajo asiq cortamos aquí

    auto izq = barreraPrimos(arbol.left());
    auto der = barreraPrimos(arbol.right());

    if (izq.first == -1) return { der.first, der.second + 1 }; // Si uno de los dos no encontró nada (-1), devolvemos el otro sumando 1 a la profundidad (porque estamos subiendo un nivel)
    if (der.first == -1) return { izq.first, izq.second + 1 };

    if (der.second < izq.second) return { der.first, der.second + 1 };

    return { izq.first, izq.second + 1 };
}


// Función que trata un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    auto primo = barreraPrimos(t);

    if (primo.first == -1)
        cout << "NO HAY";
    else
        cout << primo.first << " " << primo.second;
    cout << endl;

}


//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
    std::ifstream in("6.6.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int numCasos;
    cin >> numCasos;

    while (numCasos--)
        tratar_caso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    system("PAUSE");
#endif
    return 0;
}
