#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

constexpr int MAX_PUNTOS = 15;

class CarnetPuntos {
public:
	// Inicializamos el vector `conductores_por_puntos`, de longitud MAX_PUNTOS + 1
	// y cada posición inicializada a 0.
	CarnetPuntos(): conductores_por_puntos(MAX_PUNTOS + 1, 0) { }

	void nuevo(const string &dni) {
		if (conductores.count(dni)) {
			throw domain_error("Conductor duplicado");
		}
		conductores.insert({dni, 15});
		conductores_por_puntos[15]++;
	}


	void quitar(const string &dni, int puntos) {
		int &puntos_conductor = buscar_conductor(dni);
		conductores_por_puntos[puntos_conductor]--;
		puntos_conductor -= puntos;						
		if (puntos_conductor < 0) puntos_conductor = 0;	
		conductores_por_puntos[puntos_conductor]++;
	}


	int consultar(const string &dni) const {
		return buscar_conductor(dni);
	}


	int cuantos_con_puntos(int puntos) const {
		if (puntos < 0 || puntos > 15) {
			throw domain_error("Puntos no validos");
		}
		return conductores_por_puntos[puntos];
	}

	
private:
	// Diccionario que indica, para cada conductor, el número de puntos
	// que tiene
	unordered_map<string, int> conductores;

	// Diccionario que indica, para cada cantidad de puntos (entre 0 y 15),
	// el número de conductores que tienen esa cantidad de puntos.
	vector<int> conductores_por_puntos;



	int &buscar_conductor(const string &dni) {
		unordered_map<string, int>::iterator it = conductores.find(dni);
		if (it == conductores.end()) {
			throw domain_error("Conductor inexistente");
		}
		return it->second;
	}


	int buscar_conductor(const string &dni) const {
		unordered_map<string, int>::const_iterator it = conductores.find(dni);
		if (it == conductores.end()) {
			throw domain_error("Conductor inexistente");
		}
		return it->second;
	}
};

bool tratar_caso() {
	CarnetPuntos cp;
	string operacion;
	cin >> operacion;

	if (cin.eof()) return false;

	while (operacion != "FIN") {
		try {
			if (operacion == "nuevo") {
				string dni; cin >> dni;
				cp.nuevo(dni);
			} else if (operacion == "quitar") {
				string dni; cin >> dni;
				int num; cin >> num;
				cp.quitar(dni, num);
			} else if (operacion == "consultar") {
				string dni; cin >> dni;
				int result = cp.consultar(dni);
				cout << "Puntos de " << dni << ": " << result << endl;
			} else if (operacion == "cuantos_con_puntos") {
				int p; cin >> p;
				int result = cp.cuantos_con_puntos(p);
				cout << "Con " << p << " puntos hay " << result << endl;
			}
		} catch (exception &e) {
			cout << "ERROR: " << e.what() << endl;
		}
		cin >> operacion;
	}

	cout << "---\n";

	return true;
}

int main() {
	while (tratar_caso()) { }
	return 0;
}

