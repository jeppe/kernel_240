//
//  HashTable.c
//  cs240project
//
//  Created by Shichao Pei on 11/24/16.
//  Copyright © 2016 Shichao Pei. All rights reserved.
//

#include "HashTable.h"

HashNode node[SIZE];

int hashCode(int key){
    return key % SIZE;
}

HashNode hashArray[SIZE];

int search(int key) {

    int hashIndex = hashCode(key);
    int sec = node[hashIndex].PageId;
    /////read disk
    return sec;
}

void readPage(int PageId){
    void *physical = (void *) 0x210000;
    read_disk(PageId, 1, physical);
    char *virtual = map_physical_page((void *) physical);
    
}

void insert(int key){
    void *physical = (void *) 0x200000;
    int hashIndex = hashCode(key);
    HashNode anode = node[hashIndex];
    read_disk(anode.PageId, 1, physical);/////////////need to be modified.////////////////////
}

void deleteKey(int key){
    void *physical = (void *) 0x200000;
    int hashIndex = hashCode(key);
    HashNode anode = node[hashIndex];
    read_disk(anode.PageId, 1, physical);/////////////need to be modified.////////////////////
    void *virtual = map_physical_page((void *) physical);
    SecondTable SecondTableArray[SecondTableSize];
    /////////I dont know how to read the sector....I assume that the secondtable has been read into array
}

void HashTableInitialize(){
    void *physical = (void *) 0x610000;
//    read_disk(0, 8, physical);
    HashNode *virtual = (HashNode *)map_physical_page((void *) physical);
    NODE *item = disk4k_read(0, 1, physical);
    item->func = HashIntitialize;
    item->params = virtual;
    
}

/////////////////////////////////////////////////////////////////
///             initialize HashTable                        /////
/////////////////////////////////////////////////////////////////

void CreateHashTable(){
    HashTable table;
    for(int i=0, j = 1; i<SIZE && j < 512; i++, j = j + 1){
//    for(int i = 0; i<SIZE;i++){
        HashNode node = {.PageId = j, .NodeSize = 256};
        table.bucket[i] = node;
    }
    
//    int value[1022];
//    int j =0;
//    for (int i=0; i<SIZE*2;){
//        value[i] = table.bucket[j].sectorId;
//        i = i+1;
//        value[i] = table.bucket[j].NodeSize;
//        i = i+1;
//        j = j+1;
//    }
    
//        for(int i=0; i<1022; i++){
//            char a[80];
//    
//            sprintf(a, "%d\n", value[i]);
//    
//    
//            write_console((unsigned) strlen(a), a);
//        }
    
    void *physical = (void *) 0x300000;
    HashNode *virtual = map_physical_page((void *) physical);
    for (int i =0; i<SIZE; i++)
    {
        virtual[i] = table.bucket[i];
    }
    
    NODE *item = disk4k_write(0, 1, physical);
//    write_disk(0, 8, physical);

}

//////////////////////////////////////////////////////////////////
//                      Old Code Expire                      /////
//////////////////////////////////////////////////////////////////

//void SecondHashTableInitialization(){
//    SecondTable value[256];
//    for (int i = 0; i < 256; i++){
//        SecondTable node = {.Key_value = "", .sectorId = -1};
//        value[i] = node;
//    }
//    
//    for (int i = 1; i<512; i++){
//        void *physical = (void *) 0x300000;
//        SecondTable *virtual = map_physical_page((void *) physical);
//        for (int ii =0; ii<256; ii++)
//        {
//            virtual[ii] = value[ii];
//        }
////        write_disk(i, 8, physical);
//        NODE *item = disk4k_write(i, 1, physical);
//    }
//}
//
//void KeyNodeTableInitialization(){
//    KeyNode value = {.sectorId = {}, .size = {}};
//    for (int i = 513; i < 131329; i++){
//        void *physical = (void *) 0x300000;
//        KeyNode *virtual = map_physical_page((void *) physical);
//        virtual = &value;
////        write_disk(i, 1, physical);
//        NODE *item = disk4k_write(i, 1, physical);
//    }
//    
//}

/////////////////////////////////////////////////////////////////
///             initialize HashTable End                    /////
/////////////////////////////////////////////////////////////////




