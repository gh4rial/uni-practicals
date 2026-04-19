#include <climits>
#include <cstdlib>
#include <iostream>

#include "utils/graphutils.hpp"

void dijkstra(Graph *G, int start)
{
    int *dist = new int[G->vertex_count];
    int *parent = new int[G->vertex_count];
    bool *visited = new bool[G->vertex_count];

    for (int i = 0; i < G->vertex_count; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int i = 0; i < G->vertex_count-1; i++) {
        int min_vertex = -1;
        int min_dist = INT_MAX;

        for (int j = 0; j < G->vertex_count; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_vertex = j;
                min_dist = dist[j];
            }
        }

        if (min_vertex == -1) break;

        visited[min_vertex] = true;

        for (Node *node = G->adj_list[min_vertex].head; node != NULL; node = node->next) {
            if (!visited[node->vertex] && dist[min_vertex] + node->weight < dist[node->vertex]) {
                dist[node->vertex] = dist[min_vertex] + node->weight;
                parent[node->vertex] = min_vertex;
            }
        }
    }

    for (int i = 0; i < G->vertex_count; i++) {
        std::cout << "Distance to vertex " << i << " is " << dist[i] << " units\n";
        std::cout << "Reached from vertex " << parent[i] << '\n';
    }
}

int main()
{
    Graph G = read_weighted_graph_from_file("dijkstra_graph.txt");
    dijkstra(&G, 0);

    return 0;
}
