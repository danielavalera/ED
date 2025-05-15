
#include <iostream>
#include <fstream>
#include <vector>

#include <list>
#include <map>
#include <unordered_map>


using namespace std;
using entrenador = string;
using pokemon =string;
using nivel = int;

class CentroPokemon {
public:

    //O(log P) siendo P nº de Pokemons
    void capturar_pokemon(entrenador const& e, pokemon const& p, nivel n) {
        auto& entrenador = entrenadores[e]; //O(1)
        if (entrenador.t_pokemon.count(p)) //O(1)
            throw invalid_argument("Pokemon repetido");
        if (entrenador.t_niveles.count(n)) //O(1)
            throw invalid_argument("Nivel repetido");

        entrenador.listaPokemon.push_back(p); //O(1)
        entrenador.t_niveles[n] = p; //O(log P)
        entrenador.t_pokemon[p] = { n, --entrenador.listaPokemon.end() };  //O(1)
    }

    //O(1)
    pair<pokemon, nivel> vencer_pokemon(entrenador const& e, nivel n) {
        if (!entrenadores.count(e)) //O(1)
            throw invalid_argument("Entrenador no existente");
        if (entrenadores[e].listaPokemon.empty()) //O(1)
            throw invalid_argument("No tiene pokemons");
        
        auto it = --entrenadores[e].t_niveles.end(); //O(1)
        if (it->first < n)
            throw invalid_argument("El pokemon no puede ser vencido");

        return {it->second, it->first};
    }

    //O(E * log P) siendo E los entrenadores
    int dia_de_liberacion(pokemon const& p) {
        int count = 0;

        for (auto entrenador = entrenadores.begin(); entrenador != entrenadores.end(); entrenador++){  //O(E)
            if (entrenador->second.t_pokemon.count(p)) {  //O(1)
                auto pair_tPokemon = entrenador->second.t_pokemon[p];
                auto pair_tPokemon_it = pair_tPokemon.second; //valor a lo que apunta el iterador (pokemon de la listaPokemon)
                
                entrenador->second.listaPokemon.erase(pair_tPokemon_it);  //O(1)
                entrenador->second.t_niveles.erase(pair_tPokemon.first);  //O(log P)
                entrenador->second.t_pokemon.erase(p);  //O(1)
                count++;
            }
        }

        return count;
    }

    pokemon gimnasio(entrenador const& e) {
        if (!entrenadores.count(e)) //O(1)
            throw invalid_argument("Entrenador no existente");
        if (entrenadores[e].listaPokemon.empty()) //O(1)
            throw invalid_argument("No tiene pokemons");

        pokemon p = entrenadores[e].listaPokemon.front(); //O(1)
        nivel n = entrenadores[e].t_pokemon[p].first;

        entrenadores[e].t_pokemon.erase(p); //O(1)
        entrenadores[e].t_niveles.erase(n); //O(log P)
        entrenadores[e].listaPokemon.pop_front(); //O(1)

        return p;
    }
private:
    struct info {
        list<pokemon> listaPokemon; //Necesario para mantener el orden de captura de los pokemons.
        map<nivel, pokemon> t_niveles; //Necesario para mantener en orden los niveles de los pokemons capturados.
        unordered_map<pokemon, pair<nivel, list<pokemon>::iterator>> t_pokemon;
        //Necesario para poder eliminar eficientemente de t_niveles y de listaPokemon cuando hay que liberar un pokemon.
    };
    unordered_map<entrenador, info> entrenadores;
};



bool resuelveCaso() {
    // leer los datos de la entrada

    string op;
    cin >> op;
    if (!std::cin)
        return false;

    CentroPokemon centro;

    while (op != "FIN") {

        try {

            if (op == "capturar_pokemon") {

                entrenador e; pokemon p; nivel n;
                std::cin >> e >> p >> n;

                centro.capturar_pokemon(e, p, n);

            }

            else if (op == "vencer_pokemon") {

                entrenador e; int n;
                std::cin >> e >> n;

                std::pair<pokemon, nivel> p = centro.vencer_pokemon(e, n);
                std::cout << e << " utiliza el pokemon " << p.first << " con nivel " << p.second << " para vencer a un nivel " << n << '\n';
            }

            else if (op == "dia_de_liberacion") {
                pokemon p;
                std::cin >> p;
                int n = centro.dia_de_liberacion(p);
                std::cout << "Liberados " << n << " pokemon " << p << '\n';
            }

            if (op == "gimnasio") {
                entrenador e;
                std::cin >> e;
                pokemon p = centro.gimnasio(e);
                std::cout << e << " deja el pokemon " << p << " en un gimnasio\n";
            }
        }
        catch (std::invalid_argument& e) {

            std::cout << "ERROR: " << e.what() << "\n";
        }

        cin >> op;

    }

    cout << "---\n";

    return true;

}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("8.4.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}