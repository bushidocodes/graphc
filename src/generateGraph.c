#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "rand_uint64.c"

typedef struct header
{
    uint64_t numVertices;
    uint64_t numEdges;
} header;

typedef struct edgerecord
{
    uint64_t source, destination;
} edgerecord;

int main(int argc, char *argv[])
{
    unsigned int edgeFactor, scale;
    header *newHeader;
    edgerecord *newEdgerecord;
    FILE *fp;

    if (argc == 1)
    {
        printf("You are missing the required scale integer\n");
        printf("This command takes the arguments generategraph SCALE EDGEFACTOR\n");
        exit(-1);
    }

    newHeader = malloc(sizeof(header));
    newEdgerecord = malloc(sizeof(edgerecord));
    fp = fopen(FILE_PATH, "w");

    edgeFactor = (argc == 3) ? atoi(argv[2]) : 16;

    printf("You entered %d arguments\n", argc - 1);

    scale = atoi(argv[1]);

    newHeader->numVertices = pow(2.0, scale);
    newHeader->numEdges = newHeader->numVertices * edgeFactor;

    printf("Scale of %d yields %lu vertices\n", scale, newHeader->numVertices);
    printf("Edge Factor of %d yields %lu edges\n", edgeFactor, newHeader->numEdges);
    // Writing Edge List Header to Text file
    fprintf(fp, "%lu %lu\n", newHeader->numVertices, newHeader->numEdges);

    // Write the header record to a binary file
    srand(time(0));
    for (uint64_t i = 1; i <= newHeader->numEdges; i++)
    {
        newEdgerecord->source = (rand_uint64() % newHeader->numVertices) + 1;
        newEdgerecord->destination = (rand_uint64() % newHeader->numVertices) + 1;
        // Write the edge record to a text file
        fprintf(fp, "%lu %lu\n", newEdgerecord->source, newEdgerecord->destination);
    }

    // Calculate number of nodes: 2^(scale int)
    // Calculate number of edges: #nodes * edgefactor
    // Open a File
    // Write the first line (#nodes #edges)
    // For Loop to generate a random connection between two nodes until complete
    // Write the lines out at a time to STDOUT
    // This allows us to pipe either to a file or another process
    fclose(fp);
    free(newHeader);
    free(newEdgerecord);
}
