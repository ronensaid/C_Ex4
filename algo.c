#include "graph.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define INFINITY 9999999 //used in Dijkstra's Algorithm



int maximum(pnode NODE)
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

bool is_empty(int v[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (!v[i])//is visited
        {
            return false;
        }
    }
    return true;
}



int minimum(int dist[], int v[], int len)
{
    int min = -1;

    for (int i = 0; i < len; i++)
    {
        if (min == -1)
        {
            if (dist[i] != INFINITY && !v[i])
                min = i;
        }


        else if (dist[i] != INFINITY && dist[i] < dist[min] && !v[i])
            min = i;
    }



    return min;
}







int Dijkstra_Algorithm(pnode head, int src, int dest)
{
    if (head == NULL)
        return -1;

    int dist_length = maximum(head) + 1;


    int *dist = (int *)malloc(sizeof(int) * dist_length);

    int *v = (int *)malloc(sizeof(int) * dist_length);

    
    for (int i = 0; i < dist_length; i++)
    {
        v[i] = 0;
        if (get_node(head, i) == NULL)
            v[i] = 1;
    }

    
    for (int i = 0; i < dist_length; i++)
        dist[i] = INFINITY;
    dist[src] = 0;

    int min;
    while (!is_empty(v, dist_length) && (min = minimum(dist, v, dist_length)) != -1)
    {
        pnode p = get_node(head, min);
        pedge edge = p->edges;
        while (edge)
        {
            if (!v[edge->endpoint->node_num])
            {
                if (dist[p->node_num] != INFINITY && dist[p->node_num] + edge->weight < dist[edge->endpoint->node_num])
                {
                    dist[edge->endpoint->node_num] = dist[p->node_num] + edge->weight;
                }
            }
            edge = edge->next;
        }
        v[min] = 1;
    }

 
    free(v);

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
    int *new_array = (int *)malloc(sizeof(int) * len - 1);
    for (int i = 0, j = 0; i < len; i++)
    {
        if (i != k)
        {
            new_array[j] = arr[i];
            j++;
        }
    }
    return new_array;
}




void printArr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ,", arr[i]);

    printf("\n");
}






int helper(pnode head, int src, int arr[], int len)
{
    if (len == 1)
        return Dijkstra_Algorithm(head, src, arr[0]);

    int min = INFINITY;

    for (int i = 0; i < len; i++)
    {
        if (i != src)
        {
            int *p = delete_from_array(arr, len, i);

            int _shortest = Dijkstra_Algorithm(head, src, arr[i]);

            int ans = helper(head, arr[i], p, len - 1);

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
    int len;
    scanf("%d", &len);//getting the size 

    int *arr = (int *)malloc(sizeof(int) * len);

    for (int i = 0; i < len; i++)
        scanf("%d", &arr[i]);

    int min = INFINITY;
    for (int i = 0; i < len; i++)
    {
        int *p = delete_from_array(arr, len, i);
        int tsp = helper(head, arr[i], p, len - 1);
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
