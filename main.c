#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "graph.h"



int main()
{

    
    char ch;

    int check = 1;
    
    int temp = 0;


    //graph
    pnode G = NULL;



    while (check)
    {
        if (!temp)
        {
            int in = scanf(" %c", &ch);
            if (in == 0 || in == -1)
            {
                check = 0;
            }
        }
        if (check)
        {
            temp = 0;
            
            
            if(ch=='A'){
                ch = build_graph_cmd(&G);
                temp = 1;
                
            }

            else if (ch=='B'){
                insert_node_cmd(&G);
            
            }


            else if (ch=='D'){
                delete_node_cmd(&G);
            }


            else if (ch=='P'){
                printGraph_cmd(G);
            }


            else if (ch=='S'){
                shortsPath_cmd(G);
                }


            else if (ch=='T'){
                TSP_cmd(G);
            }
            
        }
    }
    
    
    
     deleteGraph_cmd(&G);
    return 0;
}
