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
    for(pedge Edge = node->edges; Edge != NULL; Edge = Edge->next)
    {
        printf("id %d weight %d , ", Edge->endpoint->node_num, Edge->weight);
    }
    printf("\n");
}
void remove_out(pnode n)
{
    if(n == NULL) return;
    pedge *ed = &n->edges;
    while (*ed)
    {
        pedge e = *ed;
        *ed = e->next;
        free(e);
    }
}


void remove_edge(pnode NODE, pnode n)
{
    if (NODE == NULL || n == NULL)
        return;
    pedge *ed;
    for(; NODE != NULL; NODE = NODE->next)
    {
        ed = &NODE->edges;
        while (*ed)
        {
            if ((*ed)->endpoint == n)
            {
                pedge e = *ed;
                *ed = e->next;
                free(e);
            }
            else ed = &(*ed)->next;
        }
    }

    ed = &n->edges;
    while (*ed)
    {
        pedge e = *ed;
        *ed = e->next;
        free(e);
    }
}