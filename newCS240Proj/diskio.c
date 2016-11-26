//
//  diskio.c
//  newCS240Proj
//
//  Created by Lu Yu on 11/24/16.
//  Copyright © 2016 Lu Yu. All rights reserved.
//

#include <stdio.h>
#include "diskio.h"

Queue* ContQueue = NULL;

/*
 ===============================================================================
                    Define bit map available operations
 ===============================================================================
 */

int bitmapGet(bitmap *b){
    unsigned int row = 0;
    int dominator = 1;
    
    int temp = 0;
    int pos = -1;
    
    for(int i = 0; i < BITMAP_SIZE; i++){
        row = b->DISKBITMAP[i];
        if (row < UINT_MAX){
            for(int j = 0; j < BIT; j++){
                temp = row >> j;
                temp = temp & dominator;
                if(temp == 0) pos = j + i * BIT;
            }
            
        }
    }
    
    return pos;
}

void init_bitmap(bitmap *b){
    for(int i = 0; i < BITMAP_SIZE; i++){
        
        b->DISKBITMAP[i] = 0;
    }
}

void bitmapSet(bitmap *b, unsigned int pos){
    /* pos is something from 0 to 7*/
    /* sets bit to 1 */
    bset(&(b->DISKBITMAP[pos/BIT]), pos%BIT);
}
void bitmapReset(bitmap *b, unsigned int pos){
    /* sets bit at pos to 0 */
    breset(&(b->DISKBITMAP[pos/BIT]), pos%BIT);
}

void bset(unsigned int *b, unsigned int pos) {
    /* pos is something from 0 to 7*/
    /* sets bit to 1 */
    *b |= 1 << pos;
}

void breset(unsigned int *b, unsigned int pos) {
    /* pos is something from 0 to 7*/
    /* sets bit to 0 */
    *b &= ~(1 << pos);
}

void write_bitmap_to_disk(bitmap *b){
    cont_obj *curcon_obj = malloc(sizeof(cont_obj));
    char *addr = (char *)(1 << 20);
    struct bitmap *temp;
    temp = (struct bitmap *)map_physical_page(addr);
    temp = b;
//    t_id tid = disk4k_write(1, 8, addr);
//    insert_cont(handlerArrays, curcon_obj, tid);
} // write disk_status bitmap back to disk, bitmap block_id


void read_bitmap_from_disk(bitmap *b){
//    bitmap *temp2;
//    void *addr2 = (void *)(1<<22);
//    temp2 = (struct bitmap *)map_physical_page(addr2);
//    t_id tid = read_disk(0, 1, addr2);
//    cont_obj *curcon_obj = malloc(sizeof(cont_obj));
//    
//    curcon_obj->func = print_read_test;
//    curcon_obj->params = temp2;
//    
//    insert_cont(handlerArrays, curcon_obj, tid);
    
} // write disk_status bitmap back to disk, bitmap block_id


/*
  ================================================================================
                            Disk Page Size 4KB IO
  ================================================================================
 */

NODE * disk4k_write(unsigned int page_id,unsigned int length, void *buffer){
    InitQueue();
        
    unsigned int base_sector = page_id * DISK_PAGE_SIZE;
    unsigned int sector_num = length * DISK_PAGE_SIZE;
    
    NODE *item = (NODE *) malloc(sizeof(NODE));
    item->base_sector = base_sector;
    item->sector_num = sector_num;
    item->buffer = buffer;
    item->job_type = WRITE;
    
    if( isEmpty(ContQueue) ){
        t_id tid = write_disk(base_sector, sector_num, buffer);
        item->tid = tid;
    }
    
    Enqueue(ContQueue, item);
    
    return item;
}

NODE * disk4k_read(unsigned int page_id, unsigned int length, void *buffer){
    InitQueue();
    
    unsigned int base_sector = page_id * DISK_PAGE_SIZE;
    unsigned int sector_num = length * DISK_PAGE_SIZE;
    
    NODE *item = (NODE *) malloc(sizeof(NODE));
    item->base_sector = base_sector;
    item->sector_num = sector_num;
    item->buffer = buffer;
    item->job_type = READ;
    
    if( isEmpty(ContQueue) ){
        t_id tid = read_disk(base_sector, sector_num, buffer);
        item->tid = tid;
    }
    
    Enqueue(ContQueue, item);
    
    return item;
}

/*
  ================================================================================
                            Continuation Queue
  ================================================================================
 */

void InitQueue() {
    if(ContQueue == NULL){
        ContQueue =  (Queue *) malloc(sizeof(Queue));
        ContQueue->limit = CONTINUATION_SIZE;
        ContQueue->size = 0;
        ContQueue->head = NULL;
        ContQueue->tail = NULL;
    }
}

void DestructQueue(Queue *queue) {
    NODE *pN;
    while (!isEmpty(queue)) {
        pN = Dequeue(queue);
        free(pN);
    }
    free(queue);
}

int Enqueue(Queue *pQueue, NODE *item) {
    /* Bad parameter */
    if ((pQueue == NULL) || (item == NULL)) {
        return FALSE;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
        return FALSE;
    }
    /*the queue is empty*/
    item->prev = NULL;
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;
        
    } else {
        /*adding item to the end of the queue*/
        pQueue->tail->prev = item;
        pQueue->tail = item;
    }
    pQueue->size++;
    return TRUE;
}

NODE * Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    NODE *item;
    if (isEmpty(pQueue))
        return NULL;
    item = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    return item;
}

NODE * preDequeue(Queue *pQueue){
    /*the queue is empty or bad param*/
    NODE *item = (NODE *) malloc(sizeof(NODE));
    if (isEmpty(pQueue))
        return NULL;
    item = pQueue->head;
    return item;
}


int isEmpty(Queue* pQueue) {
    if (pQueue == NULL) {
        return FALSE;
    }
    if (pQueue->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}