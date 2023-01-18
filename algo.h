#include "graph.h"

int maximum_key(pnode NODE);
bool is_empty(int is_v[], int length);
int Minimum(int dist[], int is_v[], int length);
int Dijkstra_Algorithm(pnode head, int src, int dest);
void shortsPath_cmd(pnode head);
int *delete_from_array(int arr[], int length, int k);
void printArr(int arr[], int length);
int helper(pnode head, int src, int arr[], int length);
void TSP_cmd(pnode head);
