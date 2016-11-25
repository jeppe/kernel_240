//
//  kernel.c
//  Test240
//
//  Created by Mootaz N. Elnozahy on 11/12/16.
//  Copyright © 2016 Mootaz N. Elnozahy. All rights reserved.
//

#include "kernel.h"
#include "test.h"

void kernel_start()
{
    start_console();
    initialize_memory();
    start_disk();
    ivec_init();
    
    char a[80];
    sprintf(a, "Hello World, disk, disk \n");
    write_console((unsigned) strlen(a), a);
    
    test_func();
    
    shutdown_machine();
}
