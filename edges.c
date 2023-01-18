#include <stdio.h>
#include <stdlib.h>


#include "graph.h"
#include "nodes.h"








void add_edge(pnode src, pnode dest, int Weight) 
 {
    if (!src || !dest)
        return;
    
    pedge new_edge = (pedge)malloc(sizeof(edge));
    new_edge->next = NULL;
    new_edge->weight = weight;
    new_edge->dest = dest;
    pedge edge = Src->edges;

    while (edge && edge->next) {
        edge = edge->next;
    }

    if (!edge) {
        src->edges = new_edge;
        return;
    }

    edge->next = new_edge;
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


void remove_out(pnode n)
{
    // delete out edges
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


