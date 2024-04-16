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
   Componente 1:
   Componente 2:
 */

#include <iostream>
#include <fstream>
#include <cassert>
 // Añade los include que necesites
#include <sstream>
#include <vector>

using namespace std;

bool tratar_caso() {
	int caso; cin >> caso;
	if (caso == 0) return false;

	string nombre;
	int casilla;
	vector<int> v;
	for (int i = 0; i < caso; i++){
		cin >> nombre >> casilla;
		while (casilla != 0) {
			v.push_back(casilla);
			cin >> casilla;
		}
	}

	
	
	
}

int main() {
	// Si estás ejecutando el programa en tu ordenador, las siguientes líneas
	// redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
	// útil para no tener que teclear los casos de prueba por teclado cada vez
	// que ejecutas el programa.
	//
	// Si prefieres teclear los casos de prueba por teclado en tu ordenador,
	// comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
	std::ifstream in("datosL10.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

	// Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
