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

/*
 input should be ignored
 */
void clock_handler(int input){
    
    halt();
}

/* 
 input value specifies the transaction identifier
 */
 void disk_handler(int input){
    
    halt();
}

/*
 input value contains a character that has been received from console
 */

void console_handler(int input){
    
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
    
    halt();
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

    for(int i = 0; i < IVEC_SIZE; i++){
        set_ivec(i, interrupt_vec_table[i]);
    }
    
}

