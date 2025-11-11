#include <SFML/Graphics.hpp>
#include <vector>
#include "Wierzcholek.h"
#include "Agent.h"
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

int main()
{
    int number_of_agents = 10;
    srand(static_cast<unsigned int>(time(nullptr)));
    auto window = RenderWindow(VideoMode({450u, 450u}), "ProjectMapping.ver1");
    window.setFramerateLimit(144);
     vector<Vertex_> vertex;
     vector<RectangleShape> squares;
     vector<vector<Vertex>> line;
     create_map(vertex, squares, line);
    vector<Agent *> agents;
    vector<int> random_vertex_list;
    int random_index = rand() % vertex.size();
    for (int i = 0; i < number_of_agents; i++) {
        while (find(random_vertex_list.begin(), random_vertex_list.end(), random_index)!= random_vertex_list.end()) {
            random_index = rand() % vertex.size();
        }
        random_vertex_list.push_back(random_index);
        const Vertex_& start_vertex = vertex[random_index];
        if (rand() % 2 == 0) {
            agents.push_back(new Agent_dfs(i, start_vertex, start_vertex, vertex.size()));
        }
        else {
            agents.push_back(new Agent_random(i, start_vertex, start_vertex, vertex.size()));
        }
    }

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
            if (const auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->code == sf::Keyboard::Key::R) {
                    for (Vertex_& v : vertex) {
                        v.setBlocked(false);
                    }
                    for (Agent* agent : agents) {
                        agent ->hardReset();
                    }
                }
                if (keyEvent->code == sf::Keyboard::Key::Space)
                {
                    for (int i = 0; i<agents.size(); i++) {
                        Agent *agentA = agents[i];
                        if (agentA -> getStatus() == AgnetStatus::PAIRED) continue;
                        for (int j = i+1; j<agents.size(); j++) {
                            Agent *agentB = agents[j];
                            if (agentB -> getStatus() == AgnetStatus::PAIRED) continue;
                            int id_A = agentA->getCurrentVertexID();
                            int id_B = agentB->getCurrentVertexID();
                            if (id_A == id_B) {
                                agentA->pairUp();
                                agentB->pairUp();
                                vertex[id_A].setBlocked(true);
                                break;
                            }
                        }
                    }
                    for (int i = 0; i<agents.size(); i++) {
                        Agent *agentA = agents[i];
                        if (agentA -> getStatus() == AgnetStatus::PAIRED) continue;
                        for (int j = i+1; j<agents.size(); j++) {
                            Agent *agentB = agents[j];
                            if (agentB -> getStatus() == AgnetStatus::PAIRED) continue;
                            int id_A = agentA->getCurrentVertexID();
                            int id_B = agentB->getCurrentVertexID();
                            if (vertex[id_A].isNeighbour(id_B)) {
                                agentA->pairUp();
                                agentB->target_vertex(vertex[id_A]);
                                agentB->pairUp();
                                vertex[id_A].setBlocked(true);
                                break;
                            }
                        }
                    }
                    for (Agent * agent : agents) {
                        if (agent->getStatus() == AgnetStatus::SEEKING) {
                            agent->move(vertex);
                        }
                    }
                }
            }
        }
        window.clear();
        for (const auto & i : squares) {
            window.draw(i);
        }
        for (const auto& l : line) {
            window.draw(l.data(), l.size(), PrimitiveType::Lines);
        }
        for (const auto& i : agents) {
            i->draw(window);
        }
        window.display();
    }
    for (Agent *agent : agents) {
        delete agent;
    }
    agents.clear();
    return 0;

}