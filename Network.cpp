#include "Network.h"
#include <iostream>

using namespace std;

Network::Network(string id, string t) : idNetwork(id), tematica(t) {}

// Getters
string Network::getIdNetwork() const {return idNetwork;}
string Network::getTematica() const {return tematica;}
int Network::getNumCreadores() const {return creadores.size();}

// Asociar creador
void Network::addCreador(const string& id) {creadores.push_back(id);}

// Mostrar info en CLi
void Network::mostrar() const {
    cout << "ID Network: " << idNetwork
        << " | Temática: " << tematica
         << " | Creadores: " << creadores.size() << endl;
}