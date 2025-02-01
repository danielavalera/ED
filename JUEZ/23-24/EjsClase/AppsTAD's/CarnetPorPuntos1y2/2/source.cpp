#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

constexpr int MAX_PUNTOS = 15;

class CarnetPuntos {
public:
	// O(1)
	CarnetPuntos(): conductores_por_puntos(MAX_PUNTOS + 1) { }

	// O(1)
	void nuevo(const string &dni) {
		if (conductores.count(dni)) {
			throw domain_error("Conductor duplicado");
		}
		conductores_por_puntos[15].push_front(dni);
		conductores.insert({dni, {15, conductores_por_puntos[15].begin()}});
	}

	// O(1)
	void quitar(const string &dni, int puntos) {
		cambiar_puntos(dni, -puntos);
	}

	// O(1)
	void recuperar(const string &dni, int puntos) {
		cambiar_puntos(dni, puntos);
	}

	// O(1)
	int consultar(const string &dni) const {
		return buscar_conductor(dni).numero_puntos;
	}

	// O(1)
	int cuantos_con_puntos(int puntos) const {
		if (puntos < 0 || puntos > 15) {
			throw domain_error("Puntos no validos");
		}
		return conductores_por_puntos[puntos].size();
	}

	// O(N), donde N es el número de personas que tienen la cantidad de puntos
	// pasada como parámetro.
	vector<string> lista_por_puntos(int puntos) {
		if (puntos < 0 || puntos > 15) {
			throw domain_error("Puntos no validos");
		}
		vector<string> result(conductores_por_puntos[puntos].begin(), conductores_por_puntos[puntos].end());
		return result;
	}
private:
	struct InfoConductor {
		int numero_puntos;
		list<string>::iterator it_conductores;
	};
	unordered_map<string, InfoConductor> conductores;
	vector<list<string>> conductores_por_puntos;

	// O(1)
	void cambiar_puntos(const string &dni, int puntos) {
		InfoConductor &info_conductor = buscar_conductor(dni);
		int &puntos_conductor = info_conductor.numero_puntos;
		int puntos_antes = puntos_conductor;
		puntos_conductor += puntos;
		if (puntos_conductor < 0) puntos_conductor = 0;
		if (puntos_conductor > 15) puntos_conductor = 15;

		if (puntos_antes != puntos_conductor) {
			list<string> &lista_antes = conductores_por_puntos[puntos_antes];
			lista_antes.erase(info_conductor.it_conductores);
			conductores_por_puntos[puntos_conductor].push_front(dni);
		}
	}

	// O(1)
	InfoConductor &buscar_conductor(const string &dni) {
		auto it = conductores.find(dni);
		if (it == conductores.end()) {
			throw domain_error("Conductor inexistente");
		}
		return it->second;
	}

	// O(1)
	const InfoConductor &buscar_conductor(const string &dni) const {
		auto it = conductores.find(dni);
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
			} else if (operacion == "recuperar") {
				string dni; cin >> dni;
				int num; cin >> num;
				cp.recuperar(dni, num);
			} else if (operacion == "consultar") {
				string dni; cin >> dni;
				int result = cp.consultar(dni);
				cout << "Puntos de " << dni << ": " << result << endl;
			} else if (operacion == "cuantos_con_puntos") {
				int p; cin >> p;
				int result = cp.cuantos_con_puntos(p);
				cout << "Con " << p << " puntos hay " << result << endl;
			} else if (operacion == "lista_por_puntos") {
				int p; cin >> p;
				vector<string> result = cp.lista_por_puntos(p);
				cout << "Tienen " << p << " puntos:";
				for (const string &s : result) { cout << " " << s; }
				cout << endl;
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

