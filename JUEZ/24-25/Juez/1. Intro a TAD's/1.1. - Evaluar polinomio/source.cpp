///*
// * ---------------------------------------------------
// *                ESTRUCTURAS DE DATOS
// * ---------------------------------------------------
// *              Facultad de Informática
// *         Universidad Complutense de Madrid
// * ---------------------------------------------------
// */
//
// /*
//  *  componentes del grupo:
//  *
//  * Estudiante 1: Daniela Valentina Valera Fuentes
//  *
//  */
//
#include <iostream>
#include <cassert>
#include <fstream>

const int GRADO_MAX = 10000;
class Polinomio {
public:
	Polinomio(); // constructora
	void anyadir_monomio(int coef, int exp); //modificadora
	long evaluar(int valor) const;//observadora
private:
	int coeficientes[GRADO_MAX + 1]{};//{} inicializa todo el array a 0;
	int gradoMayor;
};

//O(n) siendo n el numero de elementos del array
Polinomio::Polinomio() {
	this->gradoMayor = 0;
}

//O(1)
void Polinomio::anyadir_monomio(int coef, int exp) {
	assert(exp <= GRADO_MAX && exp >= 0);
	this->coeficientes[exp] += coef;
}

//O(n) siendo n el grado mayor que hay en el array
long Polinomio::evaluar(int valor) const {
	long result = 0;
	long exp = valor;
	for (int i = 0; i < GRADO_MAX; i++) {
		if (coeficientes[i] != 0) {
			if (i == 0) result += coeficientes[i];
			else result += coeficientes[i] * exp;
		}
		if (i > 0) 
			exp *= valor;
	}
	return result;
}

bool tratar_caso() {

	int monomios, valor;
	std::cin >> monomios >> valor;
	if (monomios == 0 && valor == 0) return false;

	int i = 0, coef, exp;
	Polinomio poli;
	while (i < monomios) {
		std::cin >> coef >> exp;
		poli.anyadir_monomio(coef, exp);
		++i;
	}
	std::cout << poli.evaluar(valor) << '\n';
	return true;

}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("1.1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//	system("PAUSE");
#endif
	return 0;
}