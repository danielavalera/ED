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
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

//no se pide el coste
bool tratar_caso() {
	int caso; cin >> caso;
	if (caso == 0) return false;

	unordered_map<int, vector<string>> carton;
	unordered_map<string, int> player_count;
	vector<string> winners;

	for (int i = 0; i < caso; i++){
		string name; cin >> name;
		//player_count[name] = 0; // inicializo el contador para ese jugador
		int num;
		while (cin >> num && num != 0) {
			carton[num].push_back(name);
			player_count[name]++;
		}
	}

	int num;
	while (cin >> num && num != 0) {
		if (carton.find(num) != carton.end(num)) { // si find() devuelve end() significa que no está el número, find() va con end()
			for (const auto& player: carton[num]){ // itero sobre el vector de nombres
				player_count[player]--;
				if (player_count[player] == 0) {
					winners.push_back(player);
				}
			}
		}
	}
	
	sort(winners.begin(), winners.end());
	for (const auto& winner:winners){
		cout << winner << " ";
	}
	cout << "\n";
	
	
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
