#include <climits>
#include <cstdlib>
#include <iostream>

#include "utils/graphutils.hpp"

void prims(Graph *G, int start)
{
    if (start < 0 || start >= G->vertex_count) {
        std::cout << "Error: Vertex index out of bounds\n";
        std::exit(1);
    }

    bool *visited = new bool[G->vertex_count];
    for (int i = 0; i < G->vertex_count; i++) {
        visited[i] = false;
    }

    int *mins = new int[G->vertex_count];
    for (int i = 0; i < G->vertex_count; i++) {
        mins[i] = INT_MAX;
    }

    mins[start] = 0;

    for (int i = 0; i < G->vertex_count && !visited[i]; i++) {

    }
}

int main()
{
    Graph G = get_weighted_graph_from_user();
    prims(&G, 0);

    return 0;
}

