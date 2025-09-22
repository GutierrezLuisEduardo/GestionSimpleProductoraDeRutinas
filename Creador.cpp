#include "Creador.h"
#include <iostream>

using namespace std;

Creador::Creador(string n, string id, string a)
    : idCreador(id), nombre(n), alcance(a) {}

// GEtters
string Creador::getIdCreador() const { return idCreador; }
string Creador::getNombre() const { return nombre; }
string Creador::getAlcance() const { return alcance; }
int Creador::getNumRutinas() const { return rutinas.size(); }
int Creador::getNumNetworks() const { return networks.size(); }

// Asociar otras entidade
void Creador::addRutina(Rutina* r) { rutinas.push_back(r); }
void Creador::addNetwork(const string& netId) { networks.push_back(netId); }

// Mostrar info en CLi
void Creador::mostrar() const {
    cout << "ID Creador: " << idCreador
        << " | Nombre: " << nombre
        << " | Alcance (en miles): " << alcance
        << " | Rutinas: " << rutinas.size()
        << " | Networks: " << networks.size() << endl;
}