#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "edges.h"

//Helping function used in other functions
pnode get_node(pnode NODE, int ID)//return the node (getting the node)
{

    while (NODE && NODE->node_num != ID)
    {
        NODE = NODE->next;
    }
    if (!NODE)
        return NULL;
    return NODE;
}

void insert_node_cmd(pnode *head)
{
    int ID;
    scanf("%d", &ID);

    pnode new_node = get_node(*head, ID);

    if (new_node == NULL)
    {
        new_node = (pnode)malloc(sizeof(node));
        new_node->next = *head;
        new_node->node_num = ID;
        new_node->edges = NULL;
    }
    else
    {
        remove_out(new_node);
    }

    int weight, dest;
    while (scanf("%d", &dest) > 0)
    {
        scanf("%d", &weight);
        add_edge(new_node, get_node(*head, dest), weight);
    }

    *head = new_node;
}

void delete_node_cmd(pnode *head)
{
    if (*head == NULL)
        return;

    int ID;
    scanf("%d", &ID);

    pnode p = *head;

    // Find the node to delete
    while (p != NULL && p->node_num != ID)
        p = p->next;

    if (p == NULL)
        return;

    // Delete edges
    remove_edge(*head, p);

    // Remove the node from the linked list
    if (p == *head)
        *head = p->next;
    else {
        pnode temp = *head;
        while (temp->next != p)
            temp = temp->next;
        temp->next = p->next;
    }

    // Free the node
    free(p);
}


void printGraph_cmd(pnode head)
{
    pnode current = head;
    for(int i = 0; current != NULL; i++)
    {
        printf("\\%d\\  \n", current->node_num);//the id/key

        print_edges(current);//printing the edges

        current = current->next;
    }
}

void deleteGraph_cmd(pnode *head)
{
    pnode p = *head;


    while (p)
    {
        remove_out(p);
        pnode temp = p;
        p = p->next;
        free(temp);
    }



    *head = NULL;
}

void build_graph_cmd(pnode *head)
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




    // return C;
}