//
//  interrupt.h
//  cs240
//
//  Created by Lu Yu on 11/14/16.
//  Copyright © 2016 Lu Yu. All rights reserved.
//

#ifndef interrupt_h
#define interrupt_h

#include "hardware_interface.h"

/*
 * Define ISR
 * author: Lu Yu
 * date: 13/11/2016
 */

// intrrupt handler takes int input, return void
typedef void (*isr_vector) (int);

void clock_handler(int input); // input should be ignored

void disk_handler(int input); // input value specifies the transaction identifier

void console_handler(int input); // input value contains a character that has been received from console

void trap_handler(int input); // input should be ingored

void exception_handler(int input); // input value specifies type of exceptions

void machine_check_handler(int input); // define the nature of malfunction, however, we will ignore

void unused1(int input);

void unused2(int input);

void ivec_init();


#endif /* interrupt_h */
