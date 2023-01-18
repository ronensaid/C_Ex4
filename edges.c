#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "nodes.h"


//Adding an edge (source,destination,weight)
void add_edge(pnode Src, pnode Dest, int Weight)
{
    if (!Src || !Dest)
        return;
    
    pedge new_edge = (pedge)malloc(sizeof(edge));

    new_edge->next = NULL;

    new_edge->weight = Weight;

    new_edge->endpoint = Dest;

    pedge EDG = Src->edges;

    while (EDG && EDG->next)
    {

        EDG = EDG->next;
    }

    if (!EDG)
    {
        Src->edges = new_edge;
        return;
    }

    EDG->next = new_edge;
}




//printing the edges
void print_edges(pnode node)
{
    if (node == NULL)
        return;

    pedge Edge = node->edges;
    
    printf("node %d edges are :\n", node->node_num);

    while (Edge)
    {
        printf("id %d weight %d , ", Edge->endpoint->node_num, Edge->weight);
        
        Edge = Edge->next;
    }
    printf("\n");
}

// delete out edges
void delete_out(pnode n)
{
    pedge ed = n->edges;
    while (ed)
    {
        pedge e = ed;
        ed = ed->next;
        free(e);
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

