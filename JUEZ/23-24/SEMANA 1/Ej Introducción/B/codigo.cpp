#include <iostream>
#include <vector>
using namespace std;
using Duracion = int;

Duracion sumar_duracion(const Duracion& t1, const Duracion& t2) {
	return t1 + t2;
}
bool duracion_menor_que(const Duracion& t1, const Duracion& t2) {
	return t1 < t2;
}
Duracion duracion_cero() {
	return 0;
}
bool caben_todas(const vector<Duracion>& duracion_actividades,
	const Duracion& duracion_congreso) {
	Duracion actual = duracion_cero();
	for (int i = 0; i < duracion_actividades.size(); i++) {
		actual = sumar_duracion(actual, duracion_actividades[i]);
	}
	return duracion_menor_que(actual, duracion_congreso);
}









