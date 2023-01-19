#include "graph.h"

int maximum(pnode NODE);
bool is_empty(int v[], int len);
int minimum(int dist[], int v[], int len);
int Dijkstra_Algorithm(pnode head, int src, int dest);
void shortsPath_cmd(pnode head);
int *delete_from_array(int arr[], int len, int k);
void printArr(int arr[], int len);
int helper(pnode head, int src, int arr[], int len);
void TSP_cmd(pnode head);
bool next_permutation(int *arr, int size)

