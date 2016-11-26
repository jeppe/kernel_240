//
//  test.h
//  cs240
//
//  Created by Lu Yu on 11/25/16.
//  Copyright © 2016 Lu Yucom. All rights reserved.
//

#ifndef test_h
#define test_h

#include <stdio.h>
#include "continuation.h"


typedef struct Temp {
    char array[512];
} Temp;


void test_func();

void disk_write_test();

void disk_read_test();

void print_read_test();

void disk_write_cont(void *a);
void char_array_write_test();
void char_array_print_test();
void char_array_read_test();

#endif /* test_h */
