#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>

using namespace std;

class Network {
private:
    string idNetwork;
    string tematica;
    vector<string> creadores;

public:
    Network(string id, string t);
    string getIdNetwork() const;
    string getTematica() const;
    int getNumCreadores() const;
    void addCreador(const string& id);
    void mostrar() const;
};

#endif