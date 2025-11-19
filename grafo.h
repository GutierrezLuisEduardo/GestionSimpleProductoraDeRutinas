#ifndef GRAFO_H
#define GRAFO_H
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void auxIt(const string &s, const string &s2, std::unordered_map<std::string, std::vector<std::string>> adj) {
    auto it = adj.find(s);
    if (it != adj.end()) {
        auto& vecinos= it->second;
        vecinos.erase(
        remove(vecinos.begin(), vecinos.end(), s2),
        vecinos.end()
        );
    }
}

class Grafo {
private:
    unordered_map<string, vector<string>> adyacencia;
public:
    void agregarArista(const string&, const string&);
    vector<string> getVecinos(string&);
    vector<string> BFS(string&);
    void eliminarArista(const string&, const string&);
};


// *** IMPLEMENTANDO ***
vector<string> Grafo::getVecinos(string &nodo) {
    auto it = adyacencia.find(nodo);
    return it != adyacencia.end() ? it->second : vector<string>();
}

void Grafo::agregarArista(const string &origen, const string &destino) {
    adyacencia[origen].push_back(destino);
    adyacencia[destino]; // asegurar que exista
}

// Elimina aristas, tmb inversa pq es no dirigido
void Grafo::eliminarArista(const string &origen, const string &destino) {
    auxIt(origen, destino, adyacencia);
    auxIt(destino, origen, adyacencia);
}
    
// Búsqueda en amplitud (BFS), ideal para relaciones cercanas
vector<string> Grafo::BFS(string &inicio) {
    vector<string> resultado;
    unordered_set<string> visitado;

    // Añadir y quitar en la cola, O(1)
    queue<string> cola;

    cola.push(inicio);
    visitado.insert(inicio);

    while (!cola.empty()) {
        string actual = cola.front(); cola.pop();
        resultado.push_back(actual);

        for (auto &vecino : getVecinos(actual)) {
            if (visitado.find(vecino)==visitado.end()) {
                visitado.insert(vecino);
                cola.push(vecino);
            }
        }
    }
    return resultado;
}
#endif