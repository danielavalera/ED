// --------------------------------------------
// Estructuras de datos
// --------------------------------------------
// Facundo y Alfredo
// --------------------------------------------

#include <iostream>
#include <stack>
#include <deque>

using namespace std;


// Coste: 
//
// Primer bucle: O(N), donde N es el número de elementos leídos de la entrada.
// Tenemos un bucle while que realiza tantas iteraciones como palabras
// leídas. Dentro del bucle se realizan operaciones de coste constante.
//
// Segundo bucle: O(M), donde M es el número de palabras que se imprimen.
//
// Total: O(N + M) = O(max{N, M}) = O(N), porque M < N.

void tratar_secuencia() {
	// Doble cola con el contenido del editor de texto (es decir, las palabras
	// que aparecen en pantalla)
	deque<string> texto;
	// Pila donde guardamos las palabras borradas para deshacerlas.
	stack<string> undo;

	string accion;
	cin >> accion;

	// Repetimos mientras la última acción leída sea distinta de '.'
	while (accion != ".") {
		if (accion == "<") {
			// Undo. Si el editor de texto tiene palabras, borramos la última
			// y la movemos a la pila de palabras borradas
			if (!texto.empty()) {
				undo.push(texto.back());
				texto.pop_back();
			}
		} else if (accion == ">") {
			// Redo. Si la pila de palabras borradas tiene elementos, quitamos
			// el último y lo movemos al editor de texto
			if (!undo.empty()) {
				texto.push_back(undo.top());
				undo.pop();
			}
		} else {
			// Palabra normal y corriente. La añadimos al editor de texto
			texto.push_back(accion);
			// La pila de palabras deshechas se borra.
			undo = {};
			// Esto equivale a:
			//
			// undo = stack<string>();
			// 
			// o bien
			//
			// stack<string> vacia;
			// undo = vacia;
		}
		cin >> accion;
	}

	// Imprimimos el resultado
	while (!texto.empty()) {
		cout << texto.front() << " ";
		texto.pop_front();
	}
	cout << "\n";
}


int main() {
	int num_secuencias;
	cin >> num_secuencias;

	for (int i = 0; i < num_secuencias; i++) {
		tratar_secuencia();
	}
}
