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

    bool *inMST = new bool[G->vertex_count];
    int *parent = new int[G->vertex_count]; // constructed MST
    int *mins = new int[G->vertex_count]; // minimum weight from each vertex

    for (int i = 0; i < G->vertex_count; i++) {
        inMST[i] = false;
        parent[i] = -1;
        mins[i] = INT_MAX;
    }

    mins[start] = 0;

    for (int i = 0; i < G->vertex_count-1; i++) {
        int u = -1;
        int min = INT_MAX;

        for (int j = 0; j < G->vertex_count; j++) {
            if (!inMST[j] && mins[j] < min) {
                u = j;
                min = mins[j];
            }
        }

        if (u == -1) {
            std::cout << "Error: graph is disconnected\n";
            std::cout << "MST construction not possible\n";
            std::exit(1);
        }
        
        inMST[u] = true;

        for (Node *node = G->adj_list[u].head; node != NULL; node = node->next) {
            if (!inMST[node->vertex] && node->weight < mins[node->vertex]) {
                mins[node->vertex] = node->weight;
                parent[node->vertex] = u;
            }
        }
    }

    int total_cost = 0;

    for (int i = 0; i < G->vertex_count; i++) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " -> " << i << " (weight " << mins[i] << ")\n";
            total_cost += mins[i];
        }
    }

    std::cout << "Total cost: " << total_cost << '\n';
}

int main()
{
    Graph G = read_weighted_graph_from_file("prims_graph.txt");
    print_weighted_graph(&G);
    prims(&G, 0);

    return 0;
}