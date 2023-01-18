#include <stdio.h>
#include "graph.h"

void create_new_graph() {
    char user_input;
    int num_vertices;
    int vertex_num;
    int edge_num;
    int weight;
    pnode graph = NULL;
    pedge current_edge;

    printf("Enter 'A' to create a new graph: ");
    scanf(" %c", &user_input);
    if (user_input == 'A') {
        printf("Enter the number of vertices in the graph: ");
        scanf("%d", &num_vertices);

        // Create a linked list of nodes
        for (int i = 0; i < num_vertices; i++) {
            printf("Enter the vertex number: ");
            scanf("%d", &vertex_num);
            printf("Enter the number of edges for vertex %d: ", vertex_num);
            scanf("%d", &edge_num);

            // Create a new node
            pnode new_node = (pnode) malloc(sizeof(node));
            new_node->node_num = vertex_num;
            new_node->edges = NULL;
            new_node->next = graph;
            graph = new_node;

            // Add edges to the node
            for (int j = 0; j < edge_num; j++) {
                printf("Enter the edge number: ");
                scanf("%d", &edge_num);
                printf("Enter the weight of the edge: ");
                scanf("%d", &weight);

                // Create a new edge
                pedge new_edge = (pedge) malloc(sizeof(edge));
                new_edge->weight = weight;
                new_edge->endpoint = NULL;
                new_edge->next = new_node->edges;
                new_node->edges = new_edge;
            }
        }
    }
}