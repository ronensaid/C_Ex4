#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "edges.h"

//Helping function used in other functions to get the node
pnode get_node(pnode NODE, int ID) {
    while (NODE) {
        if (NODE->node_num == ID) {
            return NODE;
        }
        NODE = NODE->next;
    }
    return NULL;
}


void insert_node_cmd(pnode *head)
{
    int ID;
    scanf("%d", &ID);

    pnode new_node = get_node(*head, ID);

    int is_there_node = 0;


    if (new_node == NULL)
    {
        new_node = (pnode)malloc(sizeof(node));

        new_node->next = NULL;

        new_node->node_num = ID;

        new_node->edges = NULL;
    }


    else
    {
        is_there_node = 1;
        delete(new_node);
    }

    // insert edges
    int weight, dest;
    while (scanf("%d", &dest) > 0)
    {
        scanf("%d", &weight);
        add_edge(new_node, get_node(*head, dest), weight);
    }

    if (is_there_node)
        return;

    if (!*head)
    {
        *head = new_node;
        return;
    }

    pnode p = *head;
    while (p->next)
    {
        p = p->next;
    }
    p->next = new_node;
}
 
void delete_node_cmd(pnode *head)
{
    if (*head == NULL)
        return;

    int ID;
    scanf("%d", &ID);

    pnode p = *head;


    pnode *previous = head;



    while (p)
    {
        if (p->node_num == ID)
        {
            break;
        }
        else
        {
            previous = &(p->next);
            p = p->next;
        }
    }

    if (!p)
        return;

    // delete edges
    remove_edge(*head, p);
    // free node
    *previous = p->next;
    free(p);
}

void printGraph_cmd(pnode head)
{
    while (head)
    {
        printf("\\%d\\  \n", head->node_num);//the id/key

        print_edges(head);//printing the edges

        head = head->next;
    }
}

void deleteGraph_cmd(pnode *head)
{
    pnode p = *head;


    while (p)
    {
        delete(p);
        pnode temp = p;
        p = p->next;
        free(temp);
    }



    *head = NULL;
}

char build_graph_cmd(pnode *head)
{
    if (*head)
        deleteGraph_cmd(head);

    int size;
    scanf("%d", &size);

    pnode *p = head;
    for (int i = 0; i < size; i++)
    {
        pnode new_node = (pnode)malloc(sizeof(node));

        new_node->next = NULL;

        new_node->node_num = i;

        new_node->edges = NULL;

        *p = new_node;

        p = &(*p)->next;
    }

    int condition = 1;
    char C;
    while (condition && scanf(" %c", &C) > 0)
    {
        if (C == 'n')
        {
            int ID;
            // getting id/key
            scanf("%d", &ID);

            // Adding edges
            int weight, dest;
            pnode node = get_node(*head, ID);

            while (scanf("%d", &dest) > 0)
            {
                scanf("%d", &weight);
                add_edge(node, get_node(*head, dest), weight);
            }
        }

        else
        {
            condition = 0;
        }
    }




    return C;
}
