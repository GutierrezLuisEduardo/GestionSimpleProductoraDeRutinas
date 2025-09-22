#ifndef CREADOR_H
#define CREADOR_H

#include <string>
#include <vector>
#include "Rutina.h"

using namespace std;

class Creador {
private:
    string idCreador;
    string nombre;
    string alcance;
    vector<Rutina*> rutinas;
    vector<string> networks;

public:
    Creador(string n, string id, string a);
    string getIdCreador() const;
    string getNombre() const;
    string getAlcance() const;
    int getNumRutinas() const;
    int getNumNetworks() const;
    void addRutina(Rutina* r);
    void addNetwork(const string& netId);
    void mostrar() const;
};

#endif