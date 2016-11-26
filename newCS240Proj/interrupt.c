//
//  interrupt.c
//  cs240
//
//  Created by Lu Yu on 11/14/16.
//  Copyright © 2016 Lu Yu. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interrupt.h"
#include "kernel.h"
#include "diskio.h"

/*
 input should be ignored
 */
void clock_handler(int input){
//    char a[80];
//    sprintf(a, "Clock Handler Implemented.\n");
//    write_console((unsigned) strlen(a), a);
    halt();
}

/* 
 input value specifies the transaction identifier
 */
 void disk_handler(int input){
    
     char a[80];
     sprintf(a, "Disk Handler Implemented %d.\n", input);
     write_console((unsigned) strlen(a), a);
     
     NODE *item = preDequeue(ContQueue);
     if(item != NULL){
         if(item->tid > -1 && item->tid == input){
             item->func(item->params);
             Dequeue(ContQueue);
             
             NODE *titem = preDequeue(ContQueue);
             if(titem != NULL){
                 if(titem->job_type == WRITE)
                     titem->tid = write_disk(item->base_sector, item->sector_num, item->buffer);
                 else
                     titem->tid = read_disk(item->base_sector, item->sector_num, item->buffer);
             }
             else{
                 sprintf(a, "IO Queue is empty.\n");
                 write_console((unsigned) strlen(a), a);
             }
         }
     }
}

/*
 input value contains a character that has been received from console
 */

void console_handler(int input){
    char a[80];
    sprintf(a, "Console Handler Implemented.\n");
    write_console((unsigned) strlen(a), a);
    halt();
}

/*
 input should be ingored
 */
void trap_handler(int input){
    halt();
}

/*
 input value specifies type of exceptions
 */
void exception_handler(int input){
    halt();
}

/*
 machine check interrupt handler
 */
void machine_check_handler(int input){
    char a[80];
    sprintf(a, "Machine Handler Implemented.\n");
    write_console((unsigned) strlen(a), a);
    
}

void unused1(int input){
    // do nothing
    
}

void unused2(int input){
    // do nothing
    
}

static isr_vector interrupt_vec_table[IVEC_SIZE] = {
    clock_handler,
    disk_handler,
    console_handler,
    trap_handler,
    exception_handler,
    machine_check_handler,
    unused1,
    unused2
};

/*
 initialize interrupt vector table
 key function ivec()
 */
void ivec_init(){

    for(int i = 0; i < IVEC_SIZE; i++) set_ivec(i, interrupt_vec_table[i]);
}

