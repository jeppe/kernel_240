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

void disk_write_cont(int *a);
#endif /* test_h */
