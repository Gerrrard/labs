#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    int quant, tempid, tempte, temptc, size = 0, nowtime = 0, next = 1;
    data block, process;
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

        if(queue_push(queue, tempid, temptc, tempte)){
            printf("Queue is full, error\n");
            return 1;
        }
        size++;
    }

    printf("Queue size is %d\n\n", size);

    size = 0;
    tempid = 0, tempte = 1;
    Queue * mq = queue_new();

    do{
        if(tempte > 0){
            tempte--;
        }

        while(next == 1 || block.id != -1){
            if(next == 1){
                block = queue_pop(queue);
                next = 0;
            }

            if(block.id != -1){
                if(block.tc == nowtime){
                    queue_push(mq, block.id, block.tc, block.te);
                    size++;
                    next = 1;
                }else{
                    break;
                }
            }
        }

        if(tempid == 0 || tempte == 0){
            process = queue_pop(mq);

            if(process.id != -1){
                size--;
                tempte = (process.te - quant >= 0)? quant : process.te;
                process.te -= tempte;
            }
        }

        printf("%d   %d\n", nowtime, process.id);       //if no process, writes -1, behavior can be easily changed
        nowtime++;

        if(tempte == 1 && process.te > 0){
            queue_push(mq, process.id, process.tc, process.te);
            size++;
        }

    }while(block.id != -1 || size != 0 || tempte != 0);

    queue_delete(mq);
    queue_delete(queue);

    printf("Finished\n");
}
