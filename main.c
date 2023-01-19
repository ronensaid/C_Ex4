#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "graph.h"



int main()
{

    
    char choose;

    int check = 1;
    
    int cout = 0;


    //graph
    pnode G = NULL;



    while (check)
    {
        if (!cout)
        {
            int in = scanf(" %c", &choose);
            if (in == 0 || in == -1)
            {
                check = 0;
            }
        }
        if (check)
        {
            cout = 0;
            
            
            if(choose=='A'){
                choose = build_graph_cmd(&G);
                cout = 1;
                
            }

            else if (choose=='B'){
                insert_node_cmd(&G);
            
            }


            else if (choose=='D'){
                delete_node_cmd(&G);
            }


            else if (choose=='P'){
                printGraph_cmd(G);
            }


            else if (choose=='S'){
                shortsPath_cmd(G);
                }


            else if (choose=='T'){
                TSP_cmd(G);
            }
            
        }
    }
    
    
    
     deleteGraph_cmd(&G);
    return 0;
}
