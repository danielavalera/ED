#include <vector>;
#include <iostream>;
using namespace std;

struct Duracion {
	int dias, horas, minutos, segundos;
};

void normalizar_duracion(Duracion& t) {
	if (t.segundos >= 60) {
		t.minutos++;
		t.segundos -= 60;
	}
	if (t.minutos >= 60) {
		t.horas++;
		t.minutos -= 60;
	}
	if (t.horas >= 24) {
		t.dias++;
		t.horas -= 24;
	}
}
Duracion sumar_duracion(const Duracion& t1, const Duracion& t2) {
	Duracion result;
	result.segundos = t1.segundos + t2.segundos;
	result.minutos = t1.minutos + t2.minutos;
	result.horas = t1.horas + t2.horas;
	result.dias = t1.dias + t2.dias;
	normalizar_duracion(result);
	return result;
}


bool duracion_menor_que(const Duracion& t1, const Duracion& t2) {
	return (t1.dias < t2.dias) ||
		t1.dias == t2.dias && (
			t1.horas < t2.horas ||
			t1.horas == t2.horas && (
				t1.minutos < t2.minutos ||
				t1.minutos == t2.minutos && t1.segundos < t2.segundos
				)
			);
}
Duracion duracion_cero() {
	return { 0, 0, 0, 0 };
}

bool caben_todas(const vector<Duracion> &duracion_actividades, const Duracion & duracion_congreso){

	Duracion actual = duracion_cero();
	for (int i = 0; i < duracion_actividades.size(); i++) {
		actual = sumar_duracion(actual, duracion_actividades[i]);
	}
	return duracion_menor_que(actual, duracion_congreso);


	
};








