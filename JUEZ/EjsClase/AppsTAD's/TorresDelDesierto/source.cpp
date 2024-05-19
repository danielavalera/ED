/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
  Utiliza las librerías de la STL en esta práctica.
  
  No te olvides del coste de las operaciones
*/
 
/*
  Manuel Montenegro Montes
*/


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <map>


using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream & operator>>(istream &is, Direccion &dir) {
  string palabra; is >> palabra;
  if (palabra == "Norte") dir = Direccion::Norte;
  else if (palabra == "Sur") dir = Direccion::Sur;
  else if (palabra == "Este") dir = Direccion::Este;
  else if (palabra == "Oeste") dir = Direccion::Oeste;
  else throw std::domain_error("Lectura de direccion incorrecta");
  return is;
}

class Desierto {
public:
  
  Desierto() { }
  

// O(log N), donde N es el número de ciudades

  void anyadir_torre(const string &nombre, int x, int y) {

    if (torres.count(nombre)) {
      throw std::domain_error("Torre ya existente");
    }
    if (por_eje_x.count(x) && por_eje_x.at(x).count(y)) { // O(log N)
      throw std::domain_error("Posicion ocupada");
    }
    torres.insert({nombre, InfoTorre(nombre, x, y)});
    por_eje_x[x][y] = nombre; // O(log N) 
    por_eje_y[y][x] = nombre; // O(log N)
    
  }
  

// O(log N), donde N es el número de ciudades

  void eliminar_torre(const string &nombre) {

    auto it = torres.find(nombre);
    if (it == torres.end()) {
      throw std::domain_error("Torre no existente");
    } else {
      por_eje_x[it->second.x].erase(it->second.y);                        // O(log N)
      if (por_eje_x[it->second.x].empty()) por_eje_x.erase(it->second.x); // O(log N)
      por_eje_y[it->second.y].erase(it->second.x);                        // O(log N)
      if (por_eje_y[it->second.y].empty()) por_eje_y.erase(it->second.y); // O(log N)
      torres.erase(it);
    }
    
  }
  

// O(log N), donde N es el número de ciudades

  pair<bool, string> torre_en_posicion(int x, int y) const {

    if (por_eje_x.count(x) && por_eje_x.at(x).count(y)) { // O(log N)
      return {true, por_eje_x.at(x).at(y)};               // O(log N)
    } else {
      return {false, ""};
    }

  }


// O(1)

  pair<int, int> posicion(const string &nombre) const {

    const InfoTorre &ic = buscar_torre(nombre);
    return {ic.x, ic.y};
    
  }
  

// O(log N), donde N es el número de ciudades

  string torre_mas_cercana(const string &nombre, const Direccion &dir) const {

    const InfoTorre &ic = buscar_torre(nombre);
    switch (dir) {
      case Direccion::Norte:
        return buscar_en_eje(por_eje_x, ic.x, ic.y, true);
      case Direccion::Sur:
        return buscar_en_eje(por_eje_x, ic.x, ic.y, false);
      case Direccion::Este:
        return buscar_en_eje(por_eje_y, ic.y, ic.x, true);
      case Direccion::Oeste:
        return buscar_en_eje(por_eje_y, ic.y, ic.x, false);
    }
    throw std::domain_error("No alcanzable");
    
  }


private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados

  struct InfoTorre {
    string nombre;
    int x, y;
    
    InfoTorre(const string &nombre, int x, int y)
      : nombre(nombre), x(x), y(y) { }
  };

  // Para cada torre, su posición
  unordered_map<string, InfoTorre> torres;
  
  // Para cada eje X, un diccionario que asocia cada coordenada Y
  // con la torre contenida en (X, Y)
  unordered_map<int, map<int, string>> por_eje_x;
  
  // Para cada eje Y, un diccionario que asocia cada coordenada X
  // con la torre contenida en (X, Y)
  unordered_map<int, map<int, string>> por_eje_y;

  // O(1)
  const InfoTorre &buscar_torre(const string &nombre) const {
    auto it = torres.find(nombre);
    if (it == torres.end()) {
      throw std::domain_error("Torre no existente");
    } else {
      return it->second;
    }
  }
  
  // Dados diccionarios anidados y una clave `pos1` del diccionario externo
  // y clave `pos2` del diccionario interno, obtiene la siguiente (si incr = true)
  // o anterior clave (si incr = false) a `pos2` en el diccionario interno. 
  // O(log N), donde N es el número de torres
  string buscar_en_eje(const unordered_map<int, map<int, string>> &m, 
                      int pos1, int pos2, bool incr) const {
    const map<int, string> &eje = m.at(pos1);
    auto it = eje.find(pos2);   // O(log N)
    if (incr) {
      ++it;
      if (it == eje.end()) throw std::domain_error("No hay torres en esa direccion");
    } else {
      if (it == eje.begin()) throw std::domain_error("No hay torres en esa direccion");
      --it;
    }
    return it->second;
  }

};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
  // Implementar.

  string instr;
  cin >> instr;
  
  if (cin.eof()) return false;
  
  Desierto des;
  
  while (instr != "FIN") {
    try {
      if (instr == "anyadir_torre") {
        string nombre;
        int x, y;
        cin >> nombre >> x >> y;
        des.anyadir_torre(nombre, x, y);
      } else if (instr == "eliminar_torre") {
        string nombre;
        cin >> nombre;
        des.eliminar_torre(nombre);        
      } else if (instr == "torre_en_posicion") {
        int x, y;
        cin >> x >> y;
        auto [esta, nombre] = des.torre_en_posicion(x, y);
        if (esta) {
          cout << "SI " << nombre << "\n";
        } else {
          cout << "NO\n";
        }
      } else if (instr == "posicion") {
        string nombre; cin >> nombre;
        auto [x, y] = des.posicion(nombre);
        cout << x << " " << y << "\n";
      } else if (instr == "torre_mas_cercana") {
        string nombre; Direccion dir;
        cin >> nombre >> dir;
        cout << des.torre_mas_cercana(nombre, dir) << "\n";
      }    
    } catch (std::exception &e) {
      cout << e.what() << "\n";
    }
  
    
    cin >> instr;
  }
  
  cout << "---\n";
  
  return true;

}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

