#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "bfs.c"

int main()
{
    /* Create a Graph */
    graph *g;
    g = malloc(sizeof(graph));

    /* Feed in graph data from STDIN */
    read_graph(g, false);

    /* Print the contents of the graph if desired */
    // print_graph(g);

    // Get a random vertex from the graph
    srand(time(0));
    uint64_t start = rand() % (g->number_vertices - 1);

    // Initiate BFS
    bfs(g, start);

    // Print the Parents List generated by the BFS to STDOUT
    print_parents(g);
    return 0;
}