#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "edges.h"

pnode get_node_recursive(pnode NODE, int ID)
{
    if(NODE == NULL)
        return NULL;
    if(NODE->node_num == ID)
        return NODE;
    return get_node_recursive(NODE->next, ID);
}

void insert_node_cmd(pnode *head)
{
    int ID;
    scanf("%d", &ID);

    pnode new_node = get_node_recursive(*head, ID);

    if (new_node == NULL)
    {
        new_node = (pnode)malloc(sizeof(node));
        new_node->node_num = ID;
        new_node->edges = NULL;
    }
    else
    {
        remove_out(new_node);
    }

    pnode last = *head;
    while (last != NULL && last->next != NULL)
        last = last->next;

    new_node->next = NULL;
    if (last == NULL)
        *head = new_node;
    else
        last->next = new_node;

    int weight, dest;
    while (scanf("%d", &dest) > 0)
    {
        scanf("%d", &weight);
        add_edge(new_node, get_node_recursive(*head, dest), weight);
    }

}


void delete_node_cmd(pnode *head)
{
    if (*head == NULL)
        return;

    int ID;
    scanf("%d", &ID);

    pnode prev = NULL;
    pnode curr = *head;

    // Find the node to delete
    while (curr != NULL && curr->node_num != ID)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return;

    // Delete edges
    remove_edge(*head, curr);

    // Remove the node from the linked list
    if (prev == NULL)
        *head = curr->next;
    else
        prev->next = curr->next;

    // Free the node
    free(curr);
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

    for (; p != NULL; p = p->next)
    {
        remove_out(p);
        free(p);
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
            pnode node = get_node_recursive(*head, ID);

            while (scanf("%d", &dest) > 0)
            {
                scanf("%d", &weight);
                add_edge(node, get_node_recursive(*head, dest), weight);
            }
        }

        else
        {
            condition = 0;
        }
    }
}