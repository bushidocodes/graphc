#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <mpi.h>
#include "bfs.c"

int main(int argc, char *argv[])
{
    /* MPI Vars */
    int noProcesses, processId;
    // dest, src, tag;
    // MPI_Status status;

    /* Problem Vars */
    graph *g;
    int start;

    /* MPI Setup */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);

    /* Create a Graph */
    g = malloc(sizeof(graph));

    /* Feed in graph data from STDIN */
    if (processId == 0)
    {
        read_graph(g, false);
        /* Print the contents of the graph if desired */
        // print_graph(g);

        // Get a random vertex from the graph
        srand(time(0));
        printf("# Vertices: %lu", g->number_vertices);
        start = rand() % (g->number_vertices - 1);

        // Initiate BFS
        bfs(g, start);

        // Print the Parents List generated by the BFS to STDOUT
        print_parents(g);
    }
    MPI_Finalize();
    return 0;
}