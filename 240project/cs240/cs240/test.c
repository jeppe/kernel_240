//
//  test.c
//  cs240
//
//  Created by Lu Yu on 11/25/16.
//  Copyright © 2016 Lu Yucom. All rights reserved.
//

#include "test.h"
#include "kernel.h"


void test_func(){
    char a[80] = "hello world\n";
    void *p;
    p = (char *)a;
    char b[80];
    sprintf(b, "Size of void function pointer %c\n", *(char *)(p + 1));
    write_console((unsigned) strlen(b), b);
    
    disk_write_test();
    disk_read_test();
    
}

void disk_write_test(){
    cont_obj *curcon_obj = malloc(sizeof(cont_obj));
    curcon_obj->func = disk_write_cont;
    
    char *addr = (char *) (1<<20);
    struct Temp *temp;
    temp = (struct Temp *)map_physical_page(addr);
    temp->array[0] = '1';
    temp->array[1] = '10';
    temp->array[2] = '\0';
    t_id tid = write_disk(0, 1, addr);
    insert_cont(handlerArrays, curcon_obj, tid);
    
}

void disk_write_cont(int *a){
    char b[512];
    sprintf(b, "write to disk continuation test\n");
    write_console((unsigned) strlen(b), b);
}

void disk_read_test(){
    Temp *temp2;
    void *addr2 = (void *)(1<<20);
    temp2 = (struct Temp *)map_physical_page(addr2);
    t_id tid = read_disk(0, 1, addr2);
    cont_obj *curcon_obj = malloc(sizeof(cont_obj));
    
    curcon_obj->func = print_read_test;
    curcon_obj->params = temp2;
    
    insert_cont(handlerArrays, curcon_obj, tid);
    
}

void print_read_test(Temp *data){
    char b[512];
    sprintf(b, "It works, we could successfully read from disk: %c\n", data->array[1]);
    write_console((unsigned) strlen(b), b);
}