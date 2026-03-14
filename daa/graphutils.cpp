#include <cstdlib>
#include <iostream>

#include "graphutils.hpp"
#include "matrixutils.hpp"

Graph get_graph_from_user()
{
    Graph G{};

    std::cout << "Enter number of vertices: ";
    std::cin >> G.vertex_count;

    if (G.vertex_count < 1) {
        std::cout << "Error: Number of vertices must be positive\n";
        std::exit(1);
    }

    G.vertices = new char[G.vertex_count];

    std::cout << "Enter vertex labels:\n";
    for (int i = 0; i < G.vertex_count; i++) {
        std::cout << "[" << i << "]: ";
        std::cin >> G.vertices[i];
    }

    std::cout << "Enter number of edges: ";
    std::cin >> G.edge_count;

    if (G.edge_count < 0) {
        std::cout << "Error: Number of edges cannot be negative\n";
        std::exit(1);
    }

    if (G.edge_count) {
        G.edges = new Graph_Edge[G.edge_count];
    }

    for (int i = 0; i < G.edge_count; i++) {
        char tmp;

        std::cout << "Enter start vertex: ";
        std::cin >> tmp;

        if (!graph_has_vertex(tmp)) {
            std::cout << "Error: Vertex \'" << tmp << "\'does not exist\n";
            std::exit(1);
        }
        G.edge_list[i].start = tmp;

        std::cout << "Enter end vertex: ";
        std::cin >> tmp;

        if (!graph_has_vertex(tmp)) {
            std::cout << "Error: Vertex\'" << tmp << "\' does not exist\n";
            std::exit(1);
        }
        G.edge_list[i].end = tmp;

        if (!G.weighted) {
            G.edge_list[i].weight = 0;
        }
    }

    graph_update_adj_matrix(G);
    
    return G;
}

void print_graph(Graph G)
{

}