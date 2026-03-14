#pragma once

#include "matrixutils.hpp";

struct Graph_Edge {
    char start, end;
    int weight;
};

struct Graph {
    int vertex_count;
    char *vertices;
    int edge_count;
    Graph_Edge *edge_list;
    bool weighted;
    Matrix adj_matrix;
};

Graph get_graph_from_user();
void print_graph(Graph G);