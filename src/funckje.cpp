//
// Created by Patryk Zinowkin on 08/11/2025.
//
//
// Created by ProgramistaCzeczen on 25.10.2025.
//

#include "Wierzcholek.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
void Load_data(vector<int>& wierz, vector<float>& x, vector<float>& y, vector<vector<int>>& sasiad) {
    fstream plik;
    plik.open("GrafStandartVer.txt");
    cout << endl;
    if (!plik.is_open()) {
        cout<<"Can't open GrafStandartVer.txt"<<endl;
    }
    else {
        string line;
        float _x, _y;
        int _wierz;
        int sus;
        while (getline(plik, line)) {
            stringstream ss(line);
            if (ss >> _wierz >> _x >> _y) {
                x.push_back(_x);
                y.push_back(_y);
                wierz.push_back(_wierz);
                sasiad.emplace_back();
                while (ss >> sus) {
                    sasiad.back().push_back(sus);
                }
            }
        }
        plik.close();
    }
}
void create_map(vector<Vertex_>&  vertex, vector<RectangleShape>& kwadraty, vector<vector<Vertex>>& line) {
    vector<int> wierz; vector<float> x, y;
    vector<vector<int>> sasiad;
    Load_data(wierz, x, y, sasiad);
    for (int i = 0; i < wierz.size(); i++) {
        cout << wierz[i] << endl;
        Vertex_ w(x[i], y[i],wierz[i] ,sasiad[i]);
        vertex.push_back(w);
    }

    for (int i = 0; i < wierz.size(); i++) {
        RectangleShape rs;
        rs.setSize(Vector2f(10.f, 10.f));
        rs.setFillColor(Color::White);
        rs.setPosition(Vector2f(vertex[i].getX() - 5.f, vertex[i].getY()- 5.f));
        kwadraty.push_back(rs);
        for (int j = 0; j < vertex[i].getNeighbour().size(); j++) {
            vector<Vertex> l = {
                Vertex{Vector2f(vertex[i].getX(), vertex[i].getY())},
                Vertex{Vector2f(vertex[vertex[i].getNeighbour()[j]].getX(), vertex[vertex[i].getNeighbour()[j]].getY())}
            };
            line.push_back(l);
        }
    }
}