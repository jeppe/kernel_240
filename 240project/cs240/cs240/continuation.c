//
//  continuation.c
//  cs240
//
//  Created by Lu Yu on 11/25/16.
//  Copyright © 2016 Lu Yu com. All rights reserved.
//

#include <stdio.h>
#include "continuation.h"
#include "kernel.h"

handlerCont handlerArrays[CONTINUATION_SIZE];

void init_cont(){
    
    for(int i = 0; i < CONTINUATION_SIZE; i++){
        handlerArrays[i].empty = TRUE; // indicate this element has not been allocated
        handlerArrays[i].tid = -1;
        handlerArrays[i].co = NULL;
    }
}

void add_cont(handlerCont *hc, handlerCont *ce){
    handlerCont *temp;
    
    for(int i = 0; i < CONTINUATION_SIZE; i++){
        temp = &hc[i];
        if (temp->empty){
            hc[i] = *ce;
            break;
        }
    }
}

void insert_cont(handlerCont *hc, cont_obj *co, int tid){
    handlerCont *temp;
    
    for(int i = 0; i < CONTINUATION_SIZE; i++){
        temp = &hc[i];
        if (temp->empty){
            temp->tid = tid;
            temp->co = co;
            temp->empty = FALSE;
            
            break;
        }
    }
   
}

void remove_cont(handlerCont *hc, int index){
    hc[index].empty = TRUE;
}

handlerCont *find_cont(handlerCont *hc, t_id tid){
    
    handlerCont *curnode;
    for(int i = 0; i < CONTINUATION_SIZE; i++){
        curnode = &hc[i];
        if(!curnode->empty && curnode->tid == tid){
            char a[80];
            sprintf(a, "Disk Handler TID %d.\n", tid);
            write_console((unsigned) strlen(a), a);
            return curnode;
        }
        
    }
    return NULL;
}