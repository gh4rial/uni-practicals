#include <cstdlib>
#include <fstream>
#include <iostream>

#include "graphutils.hpp"

Graph read_weighted_graph_from_file(const char *fname)
{
    std::ifstream fs(fname);

    int vertex_count, edge_count;

    fs >> vertex_count;
    if (vertex_count < 1) {
        std::cout << "Error: Number of vertices must be positive\n";
        std::exit(1);
    }

    fs >> edge_count;
    if (edge_count < 0) {
        std::cout << "Error: Number of edges must be positive\n";
        std::cout << "Found edge count: " << edge_count << '\n';
        std::exit(1);
    }

    Graph G = create_graph(vertex_count, edge_count);

    for (int i = 0; i < edge_count; i++) {
        int start, end, weight;
        fs >> start;
        fs >> end;
        fs >> weight;
        graph_add_weighted_edge(&G, start, end, weight);
    }

    return G;
}

Graph read_graph_from_file(const char *fname)
{
    std::ifstream fs(fname);

    int vertex_count, edge_count;

    fs >> vertex_count;
    if (vertex_count < 1) {
        std::cout << "Error: Number of vertices must be positive\n";
        std::exit(1);
    }

    fs >> edge_count;
    if (edge_count < 0) {
        std::cout << "Error: Number of edges must be positive\n";
        std::exit(1);
    }

    Graph G = create_graph(vertex_count, edge_count);

    for (int i = 0; i < edge_count; i++) {
        int start, end;
        fs >> start;
        fs >> end;
        graph_add_edge(&G, start, end);
    }

    return G;
}

void print_graph(Graph *G)
{
    std::cout << "Vertex count: " << G->vertex_count << '\n';
    std::cout << "Edge count: " << G->edge_count << '\n';
    std::cout << "Edges:\n";
    for (int i = 0; i < G->edge_count; i++) {
        std::cout << "[" << i << "]: ";
        std::cout << G->edge_list[i].start << "-" << G->edge_list[i].end << '\n';
    }
}

void print_weighted_graph(Graph *G)
{
    std::cout << "Vertex count: " << G->vertex_count << '\n';
    std::cout << "Edge count: " << G->edge_count << '\n';
    std::cout << "Edges:\n";
    for (int i = 0; i < G->edge_count; i++) {
        std::cout << "[" << i << "]: ";
        std::cout << G->edge_list[i].start << "-" << G->edge_list[i].end << ": " << G->edge_list[i].weight << '\n';
    }
}

Graph create_graph(int vertex_count, int edge_count)
{
    Graph G{};

    G.vertex_count = vertex_count;
    G.edge_count = edge_count;
    G.edge_index = 0;

    G.edge_list = new Edge[G.edge_count];

    G.adj_matrix = new int[G.vertex_count*G.vertex_count];
    for (int i = 0; i < G.vertex_count*G.vertex_count; i++) {
        G.adj_matrix[i] = 0;
    }

    G.adj_list = new Node_List[G.vertex_count];
    for (int i = 0; i < G.vertex_count; i++) {
        G.adj_list[i].head = NULL;
    }

    return G;
}


void graph_add_weighted_edge(Graph *G, int start, int end, int weight)
{
    if (start < 0 || start >= G->vertex_count) {
        std::cout << "Error: Vertex index " << start << " is out of bounds\n";
        std::exit(1);
    }

    if (end < 0 || end >= G->vertex_count) {
        std::cout << "Error: Vertex index " << end << " is out of bounds\n";
        std::exit(1);
    }

    if (weight <= 0) {
        std::cout << "Error: Weight must be positive\n";
        std::exit(1);
    }

    int i = G->edge_index;

    G->edge_list[i].start = start;
    G->edge_list[i].end = end;
    G->edge_list[i].weight = weight;

    G->edge_index++;

    G->adj_matrix[start*G->vertex_count + end] = weight;
    G->adj_matrix[end*G->vertex_count + start] = weight;

    list_append(&G->adj_list[start], end, weight);
    list_append(&G->adj_list[end], start, weight);
}

void graph_add_edge(Graph *G, int start, int end)
{
    graph_add_weighted_edge(G, start, end, 1);
}

Graph get_graph_from_user()
{
    int vertex_count, edge_count;

    std::cout << "Enter number of vertices: ";
    std::cin >> vertex_count;
    if (vertex_count < 1) {
        std::cout << "Error: Number of vertices must be positive\n";
        std::exit(1);
    }

    std::cout << "Enter number of edges: ";
    std::cin >> edge_count;
    if (edge_count < 0) {
        std::cout << "Error: Number of edges cannot be negative\n";
        std::exit(1);
    }

    Graph G = create_graph(vertex_count, edge_count);

    std::cout << "Enter edges:\n";
    for (int i = 0; i < edge_count; i++) {
        int start, end;
        std::cout << "Edge " << i+1 << ":\n";

        std::cout << "  Enter start vertex: ";
        std::cin >> start;

        std::cout << "  Enter end vertex: ";
        std::cin >> end;

        graph_add_edge(&G, start, end);
    }

    return G;
}

Graph get_weighted_graph_from_user()
{
    int vertex_count, edge_count;

    std::cout << "Enter number of vertices: ";
    std::cin >> vertex_count;
    if (vertex_count < 1) {
        std::cout << "Error: Number of vertices must be positive\n";
        std::exit(1);
    }

    std::cout << "Enter number of edges: ";
    std::cin >> edge_count;
    if (edge_count < 0) {
        std::cout << "Error: Number of edges cannot be negative\n";
        std::exit(1);
    }

    Graph G = create_graph(vertex_count, edge_count);

    std::cout << "Enter edges:\n";
    for (int i = 0; i < edge_count; i++) {
        int start, end, weight;
        std::cout << "Edge " << i+1 << ":\n";

        std::cout << "  Enter start vertex: ";
        std::cin >> start;

        std::cout << "  Enter end vertex: ";
        std::cin >> end;

        std::cout << "  Enter edge weight: ";
        std::cin >> weight;

        graph_add_weighted_edge(&G, start, end, weight);
    }

    return G;
}

void list_append(Node_List *list, int v, int weight)
{
    Node *N = new Node;
    N->vertex = v;
    N->weight = weight;
    N->next = list->head;
    list->head = N;
}
