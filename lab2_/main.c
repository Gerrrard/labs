#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    int quant, tempid, tempte, temptc, size = 0, nowtime = 0;
    data block;
    Queue * queue = queue_new();

    if(get_int(&quant)){
        printf("Error in input, EOF\n");
        return 1;
    }

    while(!get_int(&tempid)){

        if(!tempid){
                break;
        }

        scanf("%d",&temptc);
        scanf("%d",&tempte);


        /*if(get_int(&temptc)){
            printf("Error in input, EOF\n");
            return 1;
        }
        if(get_int(&tempte)){
            printf("Error in input, EOF\n");
            return 1;
        }*/

        if(queue_push(queue, tempid, temptc, tempte)){
            printf("Queue is full, error\n");
            return 1;
        }
        size++;
    }

    printf("Queue size is %d\n\n", size);

    do{
        block = queue_pop(queue);
        if(block.id != -1){
            tempte = (block.te - quant >= 0)? quant : block.te % quant;
            while(tempte > 0){
                printf("%d   &d\n", nowtime, block.id);
                tempte--;
                nowtime++;
                block.te -= 1;
            }
            if(block.te > 0){
                queue_push(queue, block.id, block.tc, block.te);
            }
        }
    }while(block.id != -1);

    printf("Finished\n", size);
}
