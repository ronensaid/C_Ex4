#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "nodes.h"

void add_edge(pnode Src, pnode Dest, int Weight)
{
    if (!Src || !Dest)
        return;
    
    pedge new_edge = (pedge)malloc(sizeof(edge));
    new_edge->weight = Weight;
    new_edge->endpoint = Dest;

    new_edge->next = Src->edges;
    Src->edges = new_edge;
}


void print_edges(pnode node)
{
    if (node == NULL)
        return;

    printf("node %d edges are :\n", node->node_num);

    pedge Edge = node->edges;
    while (Edge)
    {
        printf("id: %d, weight: %d\n", Edge->endpoint->node_num, Edge->weight);
        Edge = Edge->next;
    }
}


void delete(pnode n)
{
    if (!n) return;

    pedge current = n->edges;
    pedge previous = NULL;

    while (current)
    {
        previous = current;
        current = current->next;
        free(previous);
    }
    n->edges = NULL;
}


void remove_edge(pnode NODE, pnode n) {
    if (NODE == NULL)
        return;

    // Delete edges coming into 'n'
    pedge p = NODE->edges;
    while (NODE) {
        pedge previous = NULL;
        while (p) {
            if (p->endpoint == n) {
                if (previous) {
                    previous->next = p->next;
                } else {
                    NODE->edges = p->next;
                }
                free(p);
                break;
            }
            previous = p;
            p = p->next;
        }
        NODE = NODE->next;
    }

    // Delete edges going out of 'n'
    p = n->edges;
    while (p) {
        pedge next = p->next;
        free(p);
        p = next;
    }
    n->edges = NULL;
}
