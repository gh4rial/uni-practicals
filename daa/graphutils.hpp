#pragma once

#include "matrixutils.hpp";

struct Graph_Edge {
    char start, end;
    int weight;
};

struct Graph {
    bool weighted;
    int vertex_count;
    char *vertices;
    int edge_count;
    Graph_Edge *edge_list;
    Matrix adj_matrix;
};

Graph get_graph_from_user();
