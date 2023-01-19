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


void remove_edge(pnode NODE, pnode n)
{
    if (NODE == NULL)
        return;

    
    while (NODE)//deleting the coming edges
    {
        pedge p = NODE->edges;
        pedge *previous = &NODE->edges;
        while (p)
        {
            if (p->endpoint == n)
            {
                *previous = p->next;
                free(p);
                p = *previous;
            }
            else
            {
                previous = &(p->next);
                p = p->next;
            }
        }

        NODE = NODE->next;
    }

    
    pedge ed = n->edges;//deleting going out edges
    while (ed)
    {
        pedge e = ed;
        ed = ed->next;
        free(e);
    }
}