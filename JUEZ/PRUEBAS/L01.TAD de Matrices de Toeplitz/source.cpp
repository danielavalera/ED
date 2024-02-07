/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1: Sara Sánchez Guerra
   Componente 2: Daniela Valentina Valera Fuentes
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>


using namespace std;

// Define aquí la clase ToeplitzMatrix e implementa sus métodos.
class ToeplitzMatrix {
	int n, m, v, posVector;
	vector<int> matriz;

	int calculaDiagonal(int i, int j) {
		return j - i + (n - 1);
	}

public:
	ToeplitzMatrix (int n, int m, int v){
		this->n = n;
		this->m = m;
		this->v = v;
		posVector = 0;
		for (int i = 0; i < n + m; i++) {   //Coste O(n + m), donde n corresponde al número de filas de la matriz y m al número de columnas 
			matriz.push_back(v);
		}
	}
	
	//Operaciones de asignacion
	int get(int i, int j) { // Coste constante: O(1) ya que accedemos sólo al valor de la posición que queremos
		if(i >= 0 && i < n && j >= 0 && j < m) {
			posVector = calculaDiagonal(i,j); 
			return matriz[posVector];
		}
	}
	
	void set(int i, int j, int valor) { // Coste constante: O(1) ya que accedemos sólo a la posición que queremos
		if(i >= 0 && i < n && j >= 0 && j < m) {
			posVector = calculaDiagonal(i, j);
			matriz[posVector] = valor;
		}
	}
};
// No te olvides de indicar y justificar el coste del constructor y el coste de cada método.


bool tratar_caso() {
	// Implementa el código para tratar un caso de prueba.
	int n, m, v; 
	cin >> n >> m >> v;
	// Esta función debe devolver `false` si, en lugar de un caso de prueba,
	// se ha encontrado con la marca de fin de entrada (0 0 0).
	if (n == 0 && m == 0 && v == 0)
		return false;
	// En caso contrario, debe procesar el caso de prueba y devolver `true`.
	ToeplitzMatrix tm(n, m, v);

	string metodo; 
	int i, j, valor;

	while (cin >> metodo && metodo != "FIN"){
		cin >> i >> j;

		if (metodo == "set") {
			cin >> valor;
			tm.set(i, j, valor);
		}
		if (metodo == "get") {
			cout << tm.get(i, j) << "\n";
		}
	}

	cout << "---" << "\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
