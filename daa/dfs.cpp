#include <cstdlib>
#include <iostream>

#include "utils/graphutils.hpp"

enum Color {
    COLOR_BLACK,
    COLOR_GREY,
    COLOR_WHITE,
};

int dfs_time;

struct Vertex_Data {
    Color color;
    int start, finish;
    int predecessor;
};

void dfs_visit(Graph *G, int u, Vertex_Data *VData)
{
    dfs_time++;
    std::cout << "Visited vertex " << u << " at t = " << dfs_time << '\n';
    VData[u].start = dfs_time;
    VData[u].color = COLOR_GREY;

    for (Node *N = G->adj_list[u].head; N != NULL; N = N->next) {
        int v = N->vertex;
        if (VData[v].color == COLOR_WHITE) {
            VData[v].predecessor = u;
            dfs_visit(G, v, VData);
        }
    }

    dfs_time++;
    std::cout << "Finished vertex " << u << " at t = " << dfs_time << '\n';
    VData[u].finish = dfs_time;
    VData[u].color = COLOR_BLACK;
}

void dfs(Graph *G)
{
    Vertex_Data *VData = new Vertex_Data[G->vertex_count];
    for (int i = 0; i < G->vertex_count; i++) {
        VData[i].color = COLOR_WHITE;
        VData[i].predecessor = -1;
    }

    dfs_time = 0;

    for (int i = 0; i < G->vertex_count; i++) {
        if (VData[i].color == COLOR_WHITE) {
            dfs_visit(G, i, VData);
        }
    }
}

int main()
{
    Graph G = read_graph_from_file("test.txt");

    dfs(&G);

    return 0;
}