#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <string>
#include <vector>
// *** Entidades de mi sistema, como structs ***

struct Rutina {
    std::string tipo, publico, id;
    int longitud;
};

struct Network {
    std::string id, tematica, descripcion;
    std::vector<std::string> creadores;
};

struct Creador {
    std::string nombre, id;
    int alcance;
    std::vector<std::string> rutinas, networks;
    int numRutinas() { return rutinas.size(); }
};
#endif