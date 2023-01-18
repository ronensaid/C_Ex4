#include "graph.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define INFINITY 9999999 //used in Dijkstra's Algorithm



int maximum_key(pnode NODE)
{
    if (NODE == NULL)
    {
        return -1;
    }

    int max = NODE->node_num;
    while (NODE)
    {
        if (NODE->node_num > max)
        {
            max = NODE->node_num;
        }
        NODE = NODE->next;
    }

    return max;
}

bool is_empty(int is_v[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!is_v[i])//is visited
        {
            return false;
        }
    }
    return true;
}



int Minimum(int dist[], int is_v[], int length)
{
    int min = -1;

    for (int i = 0; i < length; i++)
    {
        if (min == -1)
        {
            if (dist[i] != INFINITY && !is_v[i])
                min = i;
        }


        else if (dist[i] != INFINITY && dist[i] < dist[min] && !is_v[i])
            min = i;
    }



    return min;
}







int Dijkstra_Algorithm(pnode head, int src, int dest)
{
    if (head == NULL)
        return -1;

    int dist_length = maximum_key(head) + 1;


    int *dist = (int *)malloc(sizeof(int) * dist_length);

    int *is_v = (int *)malloc(sizeof(int) * dist_length);

    
    for (int i = 0; i < dist_length; i++)
    {
        is_v[i] = 0;
        if (get_node(head, i) == NULL)
            is_v[i] = 1;
    }

    
    for (int i = 0; i < dist_length; i++)
        dist[i] = INFINITY;
    dist[src] = 0;

    int min;
    while (!is_empty(is_v, dist_length) && (min = Minimum(dist, is_v, dist_length)) != -1)
    {
        pnode p = get_node(head, min);
        pedge edge = p->edges;
        while (edge)
        {
            if (!is_v[edge->endpoint->node_num])
            {
                if (dist[p->node_num] != INFINITY && dist[p->node_num] + edge->weight < dist[edge->endpoint->node_num])
                {
                    dist[edge->endpoint->node_num] = dist[p->node_num] + edge->weight;
                }
            }
            edge = edge->next;
        }
        is_v[min] = 1;
    }

 
    free(is_v);

    if (dist[dest] == INFINITY)
    {
        free(dist);
        return -1;
    }

    int x = dist[dest];
    free(dist);
    return x;
}

//using Dijkstra Algorithm
void shortsPath_cmd(pnode head)
{
    if (head == NULL)
        return;

    int src, dest;
    scanf("%d %d", &src, &dest);//getting source and destination

    int ans = Dijkstra_Algorithm(head, src, dest);

    if (ans == -1)
    {
        printf("Dijsktra shortest path: -1 \n");
        return;
    }
    printf("Dijsktra shortest path: %d \n", ans);
}

int *delete_from_array(int arr[], int length, int k)
{
    int *new_array = (int *)malloc(sizeof(int) * length - 1);
    for (int i = 0, j = 0; i < length; i++)
    {
        if (i != k)
        {
            new_array[j] = arr[i];
            j++;
        }
    }
    return new_array;
}




void printArr(int arr[], int length)
{
    for (int i = 0; i < length; i++)
        printf("%d ,", arr[i]);

    printf("\n");
}






int helper(pnode head, int src, int arr[], int length)
{
    if (length == 1)
        return Dijkstra_Algorithm(head, src, arr[0]);

    int min = INFINITY;

    for (int i = 0; i < length; i++)
    {
        if (i != src)
        {
            int *p = delete_from_array(arr, length, i);

            int _shortest = Dijkstra_Algorithm(head, src, arr[i]);

            int ans = helper(head, arr[i], p, length - 1);

            if (_shortest != -1 && ans != -1 && ans + _shortest < min)
                min = ans + _shortest;

            free(p);
        }
    }

    if (min == INFINITY)
        return -1;




    return min;
}






void TSP_cmd(pnode head)
{
    int length;
    scanf("%d", &length);//getting the size 

    int *arr = (int *)malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++)
        scanf("%d", &arr[i]);

    int min = INFINITY;
    for (int i = 0; i < length; i++)
    {
        int *p = delete_from_array(arr, length, i);
        int tsp = helper(head, arr[i], p, length - 1);
        if (tsp != -1 && min > tsp)
        {
            min = tsp;
        }


        free(p);
    }





    if (min == INFINITY)
    {
        printf("TSP shortest path: -1 \n");
    }
    else
    {
        printf("TSP shortest path: %d \n", min);
    }






    free(arr);
}
