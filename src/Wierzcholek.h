//
// Created by Patryk Zinowkin on 08/11/2025.
//

#ifndef WIERZCHOLEK_H
#define WIERZCHOLEK_H
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;


class Vertex_ {
    float x;
    float y;
    vector<int> neighbour;
    bool blocked = false;
    int id;
public:
    Vertex_(float _x, float _y, int _id, const vector<int>& _neighbour): x(_x), y(_y),id(_id) ,neighbour(_neighbour){};
    Vertex_(float _x, float _y, int _id): x(_x), y(_y), id(_id){};
    Vertex_(const Vertex_& a): x(a.x), y(a.y), id(a.id), neighbour(a.neighbour){};
    void setX(float _x){x = _x;}
    void setY(float _y){y = _y;}
    void addNeighbour(int _next) {neighbour.push_back(_next);}
    bool getBlocked() {return blocked;}
    void setBlocked(bool _b) {blocked = _b;}
    float getX(){return x;}
    float getY(){return y;}
    int getID(){return id;}
    bool isNeighbour(int _id)const {
        for (int i : neighbour) {
            if (_id == i) return true;
        }
        return false;
    }
    const vector<int>& getNeighbour() {return neighbour;}
    void Informacje() {
        cout<<"x = "<<x<<endl;
        cout<<"y = "<<y<<endl;
        cout<<"id = "<<id<<endl;
        cout<<"Neighbours = ";
        for (int n : neighbour) {
            cout<<n<<" ";
        }
        cout<<"---------------------------"<<endl;
    }
};

void Load_data(vector<int>& wierz, vector<float>& x, vector<float>& y, vector<vector<int>>& sasiad);
void create_map(vector<Vertex_>&  vertex, vector<RectangleShape>& kwadraty, vector<vector<Vertex>>& line);
#endif //WIERZCHOLEK_H
