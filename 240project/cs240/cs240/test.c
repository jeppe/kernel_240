//
//  test.c
//  cs240
//
//  Created by Lu Yu on 11/25/16.
//  Copyright © 2016 Lu Yucom. All rights reserved.
//

#include "test.h"
#include "kernel.h"
#include <limits.h>

void test_func(){
    char a[80] = "hello world\n";
    char b[80];
    
//    unsigned int t1 = 16;
//    unsigned int t = 1;
//    t1 = t1 & t;
    
    sprintf(b, "Size of void function pointer %d\n", &a[0]);
    write_console((unsigned) strlen(b), b);
    
//    disk_write_test();
//    disk_read_test();
    
    char_array_write_test();
    char_array_read_test();
    
}

void disk_write_test(){
    cont_obj *curcon_obj = malloc(sizeof(cont_obj));
    curcon_obj->func = disk_write_cont;
    
    char *addr = (char *) (1 << 20);
    
    struct Temp *temp;
    temp = (struct Temp *)map_physical_page(addr);
    temp->array[0] = '1';
    temp->array[1] = 'b';
    temp->array[2] = '\0';
    t_id tid = write_disk(0, 1, addr);
    insert_cont(handlerArrays, curcon_obj, tid);
    
}

void char_array_write_test(){
//    cont_obj *curcon_obj = malloc(sizeof(cont_obj));
//    curcon_obj->func = disk_write_cont;
    
    char *addr = (char *) (1 << 20);
    
    char *ind;
    ind = (char *)map_physical_page(addr);
    *ind = 'c';
    *(ind + 1) = 'b';
    *(ind + 2) = '\0';
    
    NODE *item = disk4k_write(0, 1, addr);
    item->func = disk_write_cont;
    
//    insert_cont(handlerArrays, curcon_obj, tid);
}

void disk_write_cont(void *a){
    char b[512];
    sprintf(b, "write to disk continuation test\n");
    write_console((unsigned) strlen(b), b);
}

void char_array_print_test(char *data){
    char b[512];
    sprintf(b, "It works, we could successfully read from disk: %s\n", data);
    write_console((unsigned) strlen(b), b);
}


void char_array_read_test(){
    char *temp2;
    void *addr2 = (void *)(1<<20);
    temp2 = (char *)map_physical_page(addr2);
    NODE * item = disk4k_read(0, 1, addr2);
    item->func = char_array_print_test;
    item->params = temp2;
    
//    cont_obj *curcon_obj = malloc(sizeof(cont_obj));
//    
//    curcon_obj->func = char_array_print_test;
//    curcon_obj->params = temp2;
//    
//    insert_cont(handlerArrays, curcon_obj, tid);
    
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