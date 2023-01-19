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
    for (pnode temp = NODE; temp != NULL; temp = temp->next)
    {
        if (temp->node_num > max)
        {
            max = temp->node_num;
        }
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



int minimum(int dist[], int v[], int len) {
    int min = INT_MAX;
    int min_index = -1;
    for (int i = 0; i < len; i++) {
        if (!v[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
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

int *delete_from_array(int arr[], int len, int k)
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


bool next_permutation(int *arr, int size)
{
    int i;
    for (i = size - 2; i >= 0 && arr[i] >= arr[i + 1]; i--);
    if (i < 0)
        return false;

    int j;
    for (j = size - 1; arr[j] <= arr[i]; j--);
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    for (int k = i + 1; k < (size + i + 1) / 2; k++)
    {
        tmp = arr[k];
        arr[k] = arr[size + i - k];
        arr[size + i - k] = tmp;
    }
    return true;
}

int helper(pnode head, int src, int arr[], int len)
{
    if (len == 1)
        return Dijkstra_Algorithm(head, src, arr[0]);

    int min = INFINITY;
    int *perm = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        perm[i] = arr[i];

    do
    {
        int current = src;
        int sum = 0;
        for (int i = 0; i < len; i++)
        {
            if (perm[i] != current)
            {
                int dist = Dijkstra_Algorithm(head, current, perm[i]);
                if (dist == -1)
                {
                    sum = -1;
                    break;
                }
                else
                    sum += dist;
                current = perm[i];
            }
        }
        if (sum != -1 && sum < min)
            min = sum;
    } while (next_permutation(perm, len));

    free(perm);

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
