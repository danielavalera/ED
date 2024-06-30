// iPud
// ----
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iterator>
#include <algorithm>


using namespace std;


class iPud {
public:
    iPud() { }

    void addSong(const string& name, const string& artist, int duration) {
        if (canciones.count(name)) {
            throw domain_error("cancion existente");
        }

        canciones.insert({ name, {artist, duration} });
    }

    void addToPlaylist(const string& name) {
        if (canciones.find(name) == canciones.end()) {
            throw domain_error("Cancion no encontrada");
        }
        if (listaReproduccion.find(name) == listaReproduccion.end()) {
            lista.push_back(name);
            listaReproduccion[name] = --lista.end();
        }
    }

    string current() const {
        if (lista.empty()) {
            throw domain_error("Lista de reproduccion vacia");
        }
        return lista.front();
    }

    void play() {
        if (!lista.empty()) {
            string song = lista.front();
            lista.pop_front();
            listaReproduccion.erase(song);

            if (cancionesReproducidas.find(song) != cancionesReproducidas.end()) {
                listaReproducidas.erase(cancionesReproducidas[song]);
            }
            listaReproducidas.push_front(song);
            cancionesReproducidas[song] = listaReproducidas.begin();
        }
    }

    int totalTime() const {
        int total = 0;
        for (const auto& song : lista) {
            total += canciones.at(song).duracion;
        }
        return total;
    }

    list<string> recent(int n) const {
        list<string> result;
        int count = 0;
        for (const auto& song : listaReproducidas) {
            if (count < n) 
                result.push_back(song);
            count++;
        }
        return result;
    }

    void deleteSong(const string& song) {
        if (canciones.find(song) != canciones.end()) {
            canciones.erase(song);

            if (listaReproduccion.find(song) != listaReproduccion.end()) {
                lista.erase(listaReproduccion[song]);
                listaReproduccion.erase(song);
            }

            if (cancionesReproducidas.find(song) != cancionesReproducidas.end()) {
                listaReproducidas.erase(cancionesReproducidas[song]);
                cancionesReproducidas.erase(song);
            }
        }
    }


private:

    struct InfoCancion {
        string artista;
        int duracion;
    };

    unordered_map<string, InfoCancion> canciones;
    list<string> lista;
    unordered_map<string, list<string>::iterator> listaReproduccion;
    list<string> listaReproducidas;
    unordered_map<string, list<string>::iterator> cancionesReproducidas;
};



bool tratar_caso() {
    string comando;
    cin >> comando;
    if (cin.eof()) {
        return false;
    }

    iPud ipud;

    while (comando != "FIN") {
        try {
            if (comando == "addSong") {
                string nombre, artista;
                int duracion;
                cin >> nombre >> artista >> duracion;
                ipud.addSong(nombre, artista, duracion);
            }
            else if (comando == "addToPlaylist") {
                string nombre;
                cin >> nombre;
                ipud.addToPlaylist(nombre);
            }
            else if (comando == "current") {
                ipud.current();
            }
            else if (comando == "play") {
                try {
                    string cancion = ipud.current();
                    ipud.play();
                    cout << "Sonando " << cancion << "\n";
                }
                catch (exception& e) {
                    cout << "No hay canciones en la lista\n";
                }
            }
            else if (comando == "totalTime") {
                int tiempo = ipud.totalTime();
                cout << "Tiempo total " << tiempo << "\n";
            }
            else if (comando == "recent") {
                int n;
                cin >> n;
                list<string> canciones = ipud.recent(n);
                if (!canciones.empty()) {
                    cout << "Las " << canciones.size() << " mas recientes\n";
                    for (const string& s : canciones) {
                        cout << "    " << s << "\n";
                    }
                }
                else {
                    cout << "No hay canciones recientes\n";
                }
            }
            else if (comando == "deleteSong") {
                string nombre;
                cin >> nombre;
                ipud.deleteSong(nombre);
            }
        }
        catch (exception& e) {
            cout << "ERROR " << comando << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("X72.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}