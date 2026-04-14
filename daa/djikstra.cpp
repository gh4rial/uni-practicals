#include <cstdlib>
#include <iostream>

#include "utils/graphutils.hpp"

void djikstra(Graph *G, int start)
{
}

int main()
{
    Graph G = read_weighted_graph_from_file("djikstra_graph.txt");
    djikstra(&G, 0);

    return 0;
}