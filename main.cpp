#include <iostream>
#include <string>
#include "grafo.h"
#include "gestor.h"

using namespace std;

// === MENÚ INTERACTIVO ===
void mostrarMenu() {
cout << string(42, '=') << "\n";
cout << "PRODUCTORA DE CONTENIDO, SISTEMA DE GESTIÓN\n";
cout << string(42, '=') << "\n";
cout << "1. Listar creadores ordenados por nombre\n";
cout << "2. Listar creadores ordenados por alcance\n";
cout << "3. Listar creadores ordenados por número de rutinas\n";
cout << "4. Buscar relaciones desde un ID (BFS)\n";
cout << "5. Ver detalles de un creador\n";
cout << "6. Ver detalles de una rutina\n";
cout << "7. Ver detalles de una network\n";
cout << "8. Añadir nuevo creador\n";
cout << "9. Eliminar creador\n";
cout << "0. Salir\n";
cout << "Opción: ";
}

int main() {
    GestorContenido gestor;

    cout << "Cargando datos desde 'rutinas.csv', 'networks.csv', 'creadores.csv'\n";

    if (!gestor.cargarDatos()) {
        cout << "Error al cargar los datos..\n";
        return 1; }
    cout << "Datos cargados exitosamente.\n";

    int opcion; string id;

    do {
    mostrarMenu(); cin >> opcion; cin.ignore();

    switch (opcion) {
    case 1: {
        cout << "\nCreadores ordenados por nombre:\n";
        auto lista = gestor.obtCreadores_Nombre();
        for (auto &c : lista) gestor.dsplCreador(c);
        break;
    }
    case 2: {
        cout << "\nCreadores ordenados por alcance:\n";
        auto lista = gestor.obtCreadores_Alcance();
        for (auto &c : lista) gestor.dsplCreador(c);
        break;
    }
    case 3: {
        cout << "\nCreadores ordenados por número de rutinas:\n";
        auto lista = gestor.obtCreadores_NRutinas();
        for (auto &c : lista) gestor.dsplCreador(c);
        break;
    }
    case 4: {
        cout << "Ingrese ID de Creador, Network o Rutina: ";
        getline(cin, id);
        cout << "\nBFS desde " << id << ":\n";
        auto relaciones = gestor.buscarRelacionesBFS(id);
        gestor.dsplRelaciones(relaciones);
        break;
    }
    case 5: {
        cout << "Ingrese ID de creador: ";
        getline(cin, id);
        auto c = gestor.getCreador(id);
        if (c) {
            cout << "\n--- Detalles del creador ---\n";
            cout << "Nombre: " << c->nombre << "\n";
            cout << "ID: " << c->id << "\n";
            cout << "Alcance: " << c->alcance << "\n";
            cout << "Rutinas: ";
            for (size_t i = 0; i < c->rutinas.size(); ++i) {
                cout << c->rutinas[i] << (i < c->rutinas.size()-1 ? ", " : "\n");
            }
            cout << "Networks: ";
            for (size_t i = 0; i < c->networks.size(); ++i) {
                cout << c->networks[i] << (i < c->networks.size()-1 ? ", " : "\n");
            }
        } else cout << "Creador no encontrado.\n";
        break;
    }
    case 6: {
        cout << "Ingresa ID de rutina: ";
        getline(cin, id);
        auto r = gestor.getRutina(id);
        if (r) {
            cout << "\n--- Detalles de la rutina ---\n";
            cout << "Tipo: " << r->tipo << "\n";
            cout << "Público: " << r->publico << "\n";
            cout << "ID: " << r->id << "\n";
            cout << "Longitud ciclo: " << r->longitud << " meses\n";
        } else cout << "Rutina no encontrada.\n";
        break;
    }
    case 7: {
        cout << "Ingresa ID de network: ";
        getline(cin, id);
        auto n = gestor.getNetwork(id);
        if (n) {
            cout << "\n--- Detalles de la network ---\n";
            cout << "ID: " << n->id << "\n";
            cout << "Temática: " << n->tematica << "\n";
            cout << "Descripción: " << n->descripcion << "\n";
            cout << "Creadores: ";
            for (size_t i = 0; i < n->creadores.size(); ++i) {
                cout << n->creadores[i] << (i < n->creadores.size()-1 ? ", " : "\n");
            }
        } else cout << "Network no encontrada.\n";
        break;
    }
    case 8: {
        string nom, id, entrada; int alc;
        vector<string> rtns, nwks;

        cout << "\n=== AÑADIR NUEVO CREADOR ===\n";
        cout << "Nombre: "; getline(cin, nom);
        cout << "ID único: "; getline(cin, id);
        cout << "Alcance (número): "; cin >> alc; cin.ignore();
        cout << "IDs de rutinas (separadas por coma): ";

        getline(cin, entrada);
        if (!entrada.empty()) {
            stringstream ss(entrada); string item;
            while (getline(ss, item, ',')) {
                if (!item.empty()) rtns.push_back(item);
            }
        }

        cout << "IDs de networks (separadas por coma): ";

        getline(cin, entrada);
        if (!entrada.empty()) {
            stringstream ss(entrada);
            string item;
            while (getline(ss, item, ',')) {
                if (!item.empty()) nwks.push_back(item);
            }
        }

        if (gestor.añadirCreador(nom,id,alc,rtns,nwks)){
            cout<<"Creador añadido correctamente.\n";}
        else cout<<"Error: ID OCUPADA'" << id << "'.\n";
        break;
    }
    case 9: {
        cout << "\n=== ELIMINAR CREADOR ===\n";
        cout << "ID del creador a eliminar: ";
        getline(cin, id);

        if (gestor.eliminarCreador(id)) cout<<"Creador eliminado.\n";
        else cout << "Creador no existente'" << id << "'.\n";
        break;
    }
    case 0:
        cout << "Saliendo del sistema...\n";
        break;
    default: cout << "Opción no válida.\n";
    }
} while (opcion != 0);
    return 0;
}