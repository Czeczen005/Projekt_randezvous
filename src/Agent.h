//
// Created by Patryk Zinowkin on 08/11/2025.
//

#ifndef AGENT_H
#define AGENT_H
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Wierzcholek.h"
#include <stack>

enum class AgnetStatus{
    SEEKING,
    PAIRED
};



class Agent {
protected:
    int id;
    sf::Color color = sf::Color::Red;
    Vertex_ current_vertex;
    Vertex_ start_vertex;
    AgnetStatus status;
public:
    Agent(int _id, const Vertex_& _current_vertex, const Vertex_& _start):id(_id), current_vertex(_current_vertex), start_vertex(_start) {
        status = AgnetStatus::SEEKING;
    }
    int getId() const { return this->id; }
    AgnetStatus getStatus() {return status;}
    void pairUp() {
        status = AgnetStatus::PAIRED;
        color = sf::Color::Green;
    }
    int getCurrentVertexID() { return current_vertex.getID(); }
    void target_vertex(const Vertex_& target_vertex) {
        current_vertex = target_vertex;
    }

    void getCurrentVertex() {current_vertex.Informacje();}
    void draw (sf::RenderWindow& window) {
        sf::RectangleShape rs;
        rs.setSize(sf::Vector2f(10.f, 10.f));
        rs.setFillColor(color);
        rs.setPosition(sf::Vector2f(current_vertex.getX() -5.f, current_vertex.getY() -5.f));
        window.draw(rs);

    }
    virtual void hardReset() {
        status = AgnetStatus::SEEKING;
        current_vertex = start_vertex;
    }
    virtual void move(vector<Vertex_>& graf) = 0;
    virtual ~Agent() = default;
};

class Agent_dfs : public Agent {
    std::stack<int> stack;
    vector<bool> visited ;
    int size;
    void reset() {
        while (!stack.empty()) {
            stack.pop();
        }
        visited.assign(size+1, false);
        visited[current_vertex.getID()] = true;
        stack.push(current_vertex.getID());
    }
public:
    Agent_dfs(int _id, const Vertex_& _current_vertex, const Vertex_& _start, int _size):Agent(_id, _current_vertex, _start), size(_size)  {
        visited.resize(size+1, false);
        visited[start_vertex.getID()] = true;
        stack.push(start_vertex.getID());
    }
    bool getVisitedAll() const {
        int count = std::count(visited.begin(), visited.end(), true);
        return count == size;
    }
    void move(vector<Vertex_>& graf) override;
    ~Agent_dfs() override{
        std::cout<<"Destroying Agent_dfs"<<std::endl;
    }
    void hardReset() override {
        Agent::hardReset();
        color = sf::Color::Red;
        reset();
    }
};


class Agent_random : public Agent {
    vector<bool> visited ;
    int size;
    void reset() {
        visited.resize(size+1, false);
        visited[current_vertex.getID()] = true;
    }
public:
    Agent_random(int _id, const Vertex_& _current_vertex, const Vertex_& _start, int _size):Agent(_id, _current_vertex, _start), size(_size) {
        visited.resize(size+1, false);
        visited[start_vertex.getID()] = true;
        color = sf::Color::Blue;
    }
    bool getVisitedAll() const {
        int count = std::count(visited.begin(), visited.end(), true);
        return count == size;
    }
    void move(vector<Vertex_>& graf) override;
    ~Agent_random() override {
        std::cout<<"Destroying Agend_random"<<std::endl;
    }
    void hardReset() override {
        Agent::hardReset();
        color = sf::Color::Blue;
        reset();
    }
};

#endif //AGENT_H