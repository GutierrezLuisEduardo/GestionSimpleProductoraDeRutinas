#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Rutina.h"
#include "Creador.h"
#include "Network.h"

using namespace std;

// Divide cadenas usando un separador
vector<string> split(const string& linea, char sep) {
    vector<string> partes;
    string parte;
    stringstream ss(linea);
    while (getline(ss, parte, sep)) { // Mientras haya partes
        // Si no está vacío, añade al vector
        if (!parte.empty()) partes.push_back(parte);
    }
    return partes;
}

// Carga de Rutinas
void cargarRutinas(const string& archivo, vector<Rutina>& rutinas) {
    ifstream file(archivo);
    string linea;
    getline(file, linea); // Omite encabezado
    while (getline(file, linea)) { // Mientras haya lineas
        vector<string> campos = split(linea, ',');
        if (campos.size() >= 4) {
            // Genera la rutina dentro del vector, a diferencia de push_back
            rutinas.emplace_back(campos[2], campos[0], campos[1], stoi(campos[3]));
        }
    }
}

// Carga de Creadores
void cargarCreadores(const string& archivo, vector<Creador>& creadores,
                     vector<Rutina>& rutinas, vector<Network>& networks) {
    ifstream file(archivo);
    string linea;
    getline(file, linea); // Omite encabezado
    while (getline(file, linea)) { // Mientras haya lineas
        vector<string> campos = split(linea, ',');
        if (campos.size() >= 5) {
            string nombre = campos[0];
            string id = campos[1];
            string alcance = campos[2];
            string rutinasStr = campos[3];
            string networksStr = campos[4];

            Creador creador(nombre, id, alcance);

            // Rutinas y Networks asociadas (separadas por ;)
            vector<string> rutinasIds = split(rutinasStr, ';');
            for (auto& rId : rutinasIds) { // iterando sobre ids de rutinas
                // Buscando entre las rutinas al que cumplla con la condición
                auto it = find_if(rutinas.begin(), rutinas.end(),
                    // lambda de condición    
                    [&](Rutina& r){
                        // c/vez que el identificador actual coincida con el de rutina
                        return r.getIdRutina() == rId; });
                // Verificar si existra la rutina
                if (it != rutinas.end()) {
                    creador.addRutina(&(*it));
                }
            }

            vector<string> networksIds = split(networksStr, ';');
            for (auto& netId : networksIds) {
                creador.addNetwork(netId);
                auto it = find_if(networks.begin(), networks.end(),
                                  [&](Network& n){ return n.getIdNetwork() == netId; });
                if (it != networks.end()) {
                    it->addCreador(id);
                }
            }

            creadores.push_back(creador);
        }
    }
}

// Carga de Networks
void cargarNetworks(const string& archivo, vector<Network>& networks) {
    ifstream file(archivo);
    string linea;
    getline(file, linea);
    while (getline(file, linea)) {
        vector<string> campos = split(linea, ',');
        if (campos.size() >= 2) {
            // Crea la network dentro del vector, a dif. de push_back
            networks.emplace_back(campos[0], campos[1]);
        }
    }
}

// Selección de tipo de orden a mostrar para info del Creador
void ordenarCreadores(vector<Creador>& creadores) {
    cout << "Ordenar creadores por: \n1. Nombre\n2. Alcance (en miles)\n3. Rutinas\n";
    int op; cin >> op;

    /* funciones lambda usadas como comparador p/sorts
     [capturas]: vacío en estos casos
     (parámetros): referencias a creadores
     {cuerpo de función}: comparaciones
    */
    switch(op) {
        case 1:
            sort(creadores.begin(), creadores.end(),
                [](const Creador& a, const Creador& b) {
                    return a.getNombre() < b.getNombre();
                });
            break;
        case 2:
            sort(creadores.begin(), creadores.end(),
                [](const Creador& a, const Creador& b) {
                    return a.getAlcance() > b.getAlcance();
                });
            break;
        case 3:
            sort(creadores.begin(), creadores.end(),
                [](const Creador& a, const Creador& b) {
                    return a.getNumRutinas() > b.getNumRutinas();
                });
            break;
    }
}

// Menú principal
void mostrarMenu() {
    cout << "\n===== MENÚ PRINCIPAL =====" << endl;
    cout << "1. Ver Creadores" << endl;
    cout << "2. Ver Rutinas" << endl;
    cout << "3. Ver Networks" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opción: ";
}

// Programa principal
int main() {
    vector<Rutina> rutinas;
    vector<Creador> creadores;
    vector<Network> networks;

    cargarRutinas("rutinas.csv", rutinas);
    cargarNetworks("networks.csv", networks);
    cargarCreadores("creadores.csv", creadores, rutinas, networks);

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
        case 1:
            // Sólo se permite seleccionar orden de Creadores
            ordenarCreadores(creadores);
            for (const auto& c : creadores) c.mostrar();
            break;
        case 2:
            for (const auto& r : rutinas) r.mostrar();
            break;
        case 3:
            for (const auto& n : networks) n.mostrar();
            break;
        case 0:
            cout << "Programa finalizado." << endl;
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 0);

    return 0;
}