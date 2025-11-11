#include "Agent.h"
#include <stack>

void Agent_dfs::move(std::vector<Vertex_>& graf) {
    if (status == AgnetStatus::PAIRED) return;
    if (stack.empty()) {
        if (getVisitedAll()) reset();
        else {
            reset();
            return;
        }
    }
    int u_id = stack.top();
    current_vertex = graf[u_id];
    const std::vector<int>& neighbour = graf[u_id].getNeighbour();
    for (int sasiad_id : neighbour) {
        if (!visited[sasiad_id] && !graf[sasiad_id].getBlocked()) {
            visited[sasiad_id] = true;
            stack.push(sasiad_id);
            current_vertex = graf[sasiad_id];
            return;
        }
    }
    stack.pop();
    if (!stack.empty()) {
        int parent_id = stack.top();
        if (graf[parent_id].getBlocked()) {
            stack.push(u_id);
            return;
        }
        current_vertex = graf[parent_id];
    }
}


void Agent_random::move(vector<Vertex_>& graf) {
    if (status == AgnetStatus::PAIRED) return;
    if (getVisitedAll()) {
        reset();
    }else {
        vector<int> neighbour;
        vector<int> not_visited;
        for (int i : graf[current_vertex.getID()].getNeighbour()) {
            if (!graf[i].getBlocked())
                neighbour.push_back(i);
        }
        if (neighbour.empty())
            return;
        for (int i : neighbour) {
            if (!visited[i] && !graf[i].getBlocked()) {
                not_visited.push_back(i);
            }
        }
        if (not_visited.empty()) {
            current_vertex = graf[neighbour[rand() % neighbour.size()]];
        }
        else {
            current_vertex = graf[not_visited[rand() % not_visited.size()]];
        }
        visited[current_vertex.getID()] = true;
    }
}