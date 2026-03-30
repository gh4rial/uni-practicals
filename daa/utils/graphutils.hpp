#pragma once

struct Node {
    int weight;
    int vertex;
    Node *next;
};

struct Node_List {
    Node *head;
};

struct Edge {
    int start, end;
    int weight;
};

struct Graph {
    int vertex_count;
    char *vertices;
    int edge_count;
    Edge *edge_list;
    int edge_index;
    int *adj_matrix;
    Node_List *adj_list;
};

void  list_append(Node_List *list, int v, int weight);
Graph create_graph(int vertex_count, int edge_count);
void  graph_add_edge(Graph *G, int start, int end);
void  graph_add_weighted_edge(Graph *G, int start, int end, int weight);
Graph get_graph_from_user();
Graph get_weighted_graph_from_user();