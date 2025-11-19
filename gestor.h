#ifndef GESTOR_H
#define GESTOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include "structures.h"
#include "grafo.h"

class GestorContenido {
private:
    unordered_map<string,Rutina> rutinas;
    unordered_map<string,Creador> creadores;
    unordered_map<string,Network> networks;
    Grafo grafo;

    vector<string> split(string&, char);

    bool cargarRutinas();
    bool cargarCreadores();
    bool cargarNetworks();
    void montarGrafo();
public:
    bool cargarDatos();
    vector<Creador> obtCreadores_Nombre();
    vector<Creador> obtCreadores_Alcance();
    vector<Creador> obtCreadores_NRutinas();
    vector<string> buscarRelacionesBFS(string&);
    Rutina *getRutina(string&);
    Creador *getCreador(string&);
    Network *getNetwork(string&);
    void dsplCreador(Creador&);
    void dsplRelaciones(vector<string>&);
    bool añadirCreador(const std::string&, const std::string&,int,
        const std::vector<std::string>& rutinas_asociadas = {},
        const std::vector<std::string>& ntwks_asociadas = {});
    bool eliminarCreador(const std::string& id);
};


// *** IMPLEMENTANDO ***


// Separar una cadena en subgrupos delimitados por un caracter
vector<string> GestorContenido::split(string &s, char c) {
    vector<string> result;
    stringstream ss(s); // convirtiendo la cadena en un flujo de datos
    string item;

    while (getline(ss, item, c)) result.push_back(item);
    return result;
}

// Función de control, asegura que los archivos se carguen efectivamente
bool GestorContenido::cargarDatos() {
    if (!cargarRutinas() || !cargarCreadores() || !cargarNetworks()){
        return false;}
    montarGrafo(); return true;
}

// *** CARGA DE DATOS DESDE ARCHIVOS ***

bool GestorContenido::cargarRutinas() {
    ifstream file("rutinas.csv");

    if (!file.is_open()) {
        cout << "Error: No se pudo abrir rutinas.csv\n";
        return false;}

    string linea; getline(file, linea); // encabezado

    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string tp, pb, id, longitud_str;
        
        getline(ss, tp, ','); getline(ss, pb, ',');
        getline(ss, id, ','); getline(ss, longitud_str, ',');

        Rutina r = {tp, pb, id, stoi(longitud_str)};
        rutinas[id] = r;
    }

    file.close(); return true;
}

bool GestorContenido::cargarCreadores() {
    ifstream file("creadores.csv");
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir creadores.csv\n";
        return false;}

    string linea;
    getline(file, linea); // encabezado

    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nom, id, alc_str, ruts_str, nwks_str;

        getline(ss, nom, ',');
        getline(ss, id, ','); getline(ss, alc_str, ',');
        getline(ss, ruts_str, ','); getline(ss, nwks_str, ',');

        int alcance = stoi(alc_str);
        vector<string> lista_rutinas = split(ruts_str, ';');
        vector<string> lista_networks = split(nwks_str, ';');

        Creador c = {nom,id,alcance,lista_rutinas,lista_networks};
        creadores[id] = c;
    }
    file.close(); return true;
}

bool GestorContenido::cargarNetworks() {
    ifstream file("networks.csv");
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir networks.csv\n";
        return false;}

    string linea; getline(file, linea); // encabezado

    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string id, tem, desc, cre_str;

        getline(ss, id, ','); getline(ss, tem, ',');
        getline(ss, desc, ','); getline(ss, cre_str, ',');
        vector<string> lista_creadores = split(cre_str, ';');

        Network n = {id, tem, desc, lista_creadores};
        networks[id] = n;
    }
    file.close(); return true;
}

// Montando el grafo, creando relaciones entre entidades
void GestorContenido::montarGrafo() {
    /* DEscompongo los pares clave-valor de creadores y añado una
    arista entre la ID creador y las rutinas del creador */
    for (auto& [idC, creador] : creadores) {
        for (auto& idR : creador.rutinas) {
            grafo.agregarArista(idC, idR);
            grafo.agregarArista(idR, idC);
        }
    }

    // Así también con las networks
    for (auto& [idC, creador] : creadores) {
        for (auto& idN : creador.networks) {
            grafo.agregarArista(idC, idN);
            grafo.agregarArista(idN, idC);
        }
    }
}

// *** ENLISTADO DE CREADORES SEGÚN DISTINTOS CRITERIOS ***
vector<Creador> GestorContenido::obtCreadores_Nombre() {
    vector<Creador> lista;
    for (auto& [idC, creador]:creadores) lista.push_back(creador);
    sort(lista.begin(), lista.end(), [](Creador& a, Creador& b) {
        return a.nombre < b.nombre;
    });
    return lista;
}

vector<Creador> GestorContenido::obtCreadores_Alcance() {
    vector<Creador> lista;
    for (auto& [idC, creador]:creadores) lista.push_back(creador);
    sort(lista.begin(), lista.end(), [](Creador& a, Creador& b) {
        return a.alcance > b.alcance;
    });
    return lista;
}

vector<Creador> GestorContenido::obtCreadores_NRutinas() {
    vector<Creador> lista;
    for (auto& [idC, creador]:creadores) lista.push_back(creador);
    sort(lista.begin(), lista.end(), [](Creador& a, Creador& b) {
        return a.numRutinas()>b.numRutinas();
    });
    return lista;
}

// *** BÚSQUEDA ***
vector<string> GestorContenido::buscarRelacionesBFS(string &id){
    return grafo.BFS(id);}

// *** ACCESO RÁPIDO ***
// Búsqueda de rutina en el unordered map O(1)
Rutina* GestorContenido::getRutina(string &id) {
    auto it = rutinas.find(id);
    return it!=rutinas.end() ? &it->second : nullptr;
}
// Búsqueda de creador en el unordered map O(1)
Creador* GestorContenido::getCreador(string &id) {
    auto it = creadores.find(id);
    return it!=creadores.end() ? &it->second : nullptr;
}
// Búsqueda de network en el unordered map O(1)
Network* GestorContenido::getNetwork(string &id) {
    auto it = networks.find(id);
    return it!=networks.end() ? &it->second : nullptr;
}

// *** DESPLEGAR EN CONSOLA ***
void GestorContenido::dsplCreador(Creador &c) {
    cout<<"  "<<c.nombre<<" ("<<c.id<<") - Alcance: "<<c.alcance<<
    " - Rutinas: "<<c.numRutinas()<<"\n";
}

void GestorContenido::dsplRelaciones(vector<string> &nodos) {
    cout<<"  Relaciones encontradas ("<<nodos.size()<<" nodos):\n";
    for (auto &id : nodos) {
        if (creadores.count(id)) {
            cout<<"  |Creador| "<<creadores.at(id).nombre<<": "<<id<<"\n";
        } else if (rutinas.count(id)) {
            auto &r = rutinas.at(id);
            cout<<"  |Rutina| " <<r.tipo<<" - "<<r.publico<<": "<<id<<"\n";
        } else if (networks.count(id)) {
            auto &n = networks.at(id);
            cout<<"  |Network| "<<n.tematica<<": "<<id<<"\n";
        }
    }
}

// *** AÑADIR Y QUITAR **
// Añade un nuevo creador al sistema
// Devuelve true si se añadió correctamente, false si ya existía ID
bool GestorContenido::añadirCreador(const string& nombre,
    const string& id, int alcance,  
    const vector<string> &rut_As,
    const vector<string>& ntwks_asociadas) {
    
    if (creadores.count(id)) return false;

    // Añadir en memoria
    Creador nuevo = {nombre, id, alcance, rut_As, ntwks_asociadas};
    creadores[id] = nuevo;

    // Actualizar grafo
    for (const auto& r : rut_As) {
        grafo.agregarArista(id, r); grafo.agregarArista(r, id);}
    for (const auto& n : ntwks_asociadas) {
        grafo.agregarArista(id, n); grafo.agregarArista(n, id);
        // Añadir a la network si existe
        if (networks.count(n)) networks[n].creadores.push_back(id);
    }

    // Guardar en CSV
    auto joinV = [](const vector<string>& v){
        string s;
        for (size_t i=0;i<v.size();++i){ if(i)s+=';'; s+=v[i]; }
        return s;
    };

    // Guardar creadores.csv
    ofstream f("creadores.csv");
    f << "nombre,id,alcance,rutinas,networks\n";
    for (auto& [idC, c] : creadores) {
        f << c.nombre << "," << c.id << "," << c.alcance << ","
        << joinV(c.rutinas) << "," << joinV(c.networks) << "\n";}

    // Guardar networks.csv
    ofstream f2("networks.csv");
    f2<< "id,tematica,descripcion,creadores\n";
    for (auto& [idN, n] : networks) {
        f2<< n.id << "," << n.tematica << "," << n.descripcion<<",";
        f2<< joinV(n.creadores) << "\n";}

    return true;
}


/* Elimina un creador del sistema (y limpia todas sus relaciones)
Devuelve true si se eliminó, false si no existía */
bool GestorContenido::eliminarCreador(const string& id){
    if (!creadores.count(id)) return false;

    Creador& c = creadores[id];

    // Eliminar relaciones del grafo
    for (auto& r : c.rutinas) {
        grafo.eliminarArista(id, r); grafo.eliminarArista(r, id);}
    for (auto& n : c.networks) {
        grafo.eliminarArista(id, n); grafo.eliminarArista(n, id);}

    // Eliminarlo de networks
    for (auto& n : c.networks) {
        if (networks.count(n)) {
            auto& lista = networks[n].creadores;
            lista.erase(remove(lista.begin(), lista.end(), id),
            lista.end());}
    }

    // Eliminar creador del mapa
    creadores.erase(id);
    // Guardar cambios en CSV
    auto joinV = [](const vector<string>& v){
        string s; 
        for (size_t i=0;i<v.size();++i) {if(i)s+=';'; s+=v[i];}
        return s;
    };

    // Guardar creadores.csv
    ofstream f("creadores.csv");
    f << "nombre,id,alcance,rutinas,networks\n";
    for (auto& [idC, c] : creadores) {
        f << c.nombre << "," << c.id << "," << c.alcance << ","
        << joinV(c.rutinas) << "," << joinV(c.networks) << "\n";}

    // Guardar networks.csv
    ofstream f2("networks.csv");
    f2 << "id,tematica,descripcion,creadores\n";
    for (auto& [idN, n] : networks) {
        f2<<n.id<<","<<n.tematica<<","<<n.descripcion<<",";
        f2<<joinV(n.creadores) << "\n";}

   return true;
}
#endif