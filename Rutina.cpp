#include "Rutina.h"
#include <iostream>

using namespace std;

Rutina::Rutina(string id, string t, string pm, int ciclo)
    : idRutina(id), tipo(t), publicoMeta(pm), cicloProduccion(ciclo) {}

// Getters
string Rutina::getIdRutina() const { return idRutina; }
string Rutina::getTipo() const { return tipo; }
string Rutina::getPublicoMeta() const { return publicoMeta; }
int Rutina::getCicloProduccion() const { return cicloProduccion; }

// Mostrar info en CLi
void Rutina::mostrar() const {
    cout << "ID Rutina: " << idRutina
        << " | Tipo: " << tipo
        << " | Público Meta: " << publicoMeta
        << " | Duración de ciclo de producción (semanas): " << cicloProduccion << endl;
}