//
//  HashTable.h
//  cs240project
//
//  Created by Shichao Pei on 11/24/16.
//  Copyright © 2016 Shichao Pei. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h
#include "kernel.h"
#include "diskio.h"

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 511
#define SecondTableSize 512

typedef struct {
    int PageId;
    int NodeSize;  //???
} HashNode;

typedef struct HashTable {
    HashNode bucket[SIZE];
} HashTable;



typedef struct {
    char Key_value[12];
    int PageId;
} SecondTable;

typedef struct  {
    int PageId[512];
    int size[512];
} KeyNode;

int search(int key);
void readPage(int PageId);
void insert(int key);
void deleteKey(int key);
void HashTableInitialize();


#endif /* HashTable_h */
