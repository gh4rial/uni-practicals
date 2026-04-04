#include <climits>
#include <cstdlib>
#include <iostream>

#include "utils/graphutils.hpp"
#include "utils/queueutils.hpp"

enum Color {
    COLOR_WHITE,
    COLOR_GREY,
    COLOR_BLACK,
};

struct Vertex_Data {
    Color color;
    int dist;
    int predecessor;
};

void bfs(Graph *G, int start)
{
    Vertex_Data *VData = new Vertex_Data[G->vertex_count];
    for (int i = 0; i < G->vertex_count; i++) {
        if (i != start) {
            VData[i].color = COLOR_WHITE;
            VData[i].dist = INT_MAX;
            VData[i].predecessor = -1;
        }
    }

    std::cout << "Visiting start vertex: " << start << '\n';
    VData[start].color = COLOR_GREY;
    VData[start].dist = 0;
    VData[start].predecessor = -1;

    int *queue_buffer = new int[G->vertex_count];
    Queue Q = queue_new(queue_buffer, G->vertex_count);

    queue_enqueue(&Q, start);

    while (Q.head != Q.tail) {
        int u = queue_dequeue(&Q);

        for (Node *N = G->adj_list[u].head; N != NULL; N = N->next) {
            int v = N->vertex;

            if (VData[v].color == COLOR_WHITE) {
                std::cout << "Visiting vertex " << v << '\n';
                std::cout << "Predecessor: " << u << '\n';
                VData[v].color = COLOR_GREY;
                VData[v].dist = VData[u].dist + 1;
                VData[v].predecessor = u;
                queue_enqueue(&Q, v);
            }
        }

        VData[u].color = COLOR_BLACK;
    }
}

int main()
{
    Graph G = read_graph_from_file("test.txt");

    print_graph(&G);
    bfs(&G, 0);

    return 0;
}