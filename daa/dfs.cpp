#include <cstdlib>
#include <iostream>

#include "utils/graphutils.hpp"

void dfs(Graph *G, int start, bool visited[])
{
    visited[start] = true;
    std::cout << start << ' ';

    for (Node *curr = G->adj_list[start].head; curr != nullptr; curr = curr->next) {
        if (!visited[curr->vertex]) {
            dfs(G, curr->vertex, visited);
        }
    }
}

int main()
{
    Graph G = get_graph_from_user();
    bool *visited = new bool[G.vertex_count]();
    dfs(&G, 0, visited);
    return 0;
}