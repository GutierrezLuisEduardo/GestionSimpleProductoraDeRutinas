#ifndef RUTINA_H
#define RUTINA_H

#include <string>

using namespace std;

class Rutina {
private:
    string idRutina;
    string tipo;
    string publicoMeta;
    int cicloProduccion;

public:
    Rutina(string id, string t, string pm, int ciclo);
    string getIdRutina() const;
    string getTipo() const;
    string getPublicoMeta() const;
    int getCicloProduccion() const;
    void mostrar() const;
};

#endif