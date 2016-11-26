//
//  diskio.h
//  newCS240Proj
//
//  Created by Lu Yu on 11/24/16.
//  Copyright © 2016 Lu Yu. All rights reserved.
//

#ifndef diskio_h
#define diskio_h

#include "OS_CFG.h"
#include "continuation.h"
#include "kernel.h"
#include <stdint.h>
#include <limits.h>


/*
  =======================================
    Continuation Queue
  =======================================
*/

//// function pointer variable
//typedef void (*cont_func) (void*);
//typedef struct cont_obj{
//    cont_func func;
//    void *params;
//} cont_obj;


/* a link in the queue, holds the info and point to the next Node*/
typedef struct {
    int info;
} DATA;

typedef struct Node {
    t_id tid;
    char job_type;
    unsigned int base_sector;
    unsigned int sector_num;
    void *buffer;
    cont_func func;
    void *params;
    
    struct Node *prev;
} NODE;

/* the HEAD of the Queue, hold the amount of node's that are in the queue*/
typedef struct Queue {
    NODE *head;
    NODE *tail;
    int size;
    int limit;
} Queue;


void InitQueue();
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue* pQueue);
NODE *preDequeue(Queue *pQueue);

extern Queue* ContQueue;

/*
   =======================================
    Define bit map available operations
   =======================================
*/
// Bitmap to track free disk blocks
typedef struct bitmap{
    unsigned int DISKBITMAP[BITMAP_SIZE];
} bitmap;

static bitmap diskbitmap;

typedef struct Temsp {
    char array[512];
} Temsp;

void init_bitmap(bitmap *b);
int bitmapGet(bitmap *b);
void bitmapSet(bitmap *b, unsigned int pos);
void bitmapReset(bitmap *b, unsigned int pos);
void bset(unsigned int *b, unsigned int pos);
void breset(unsigned int *b, unsigned int pos);

void write_bitmap_to_disk(bitmap *b); // write disk_status bitmap back to disk, bitmap block_id
void read_bitmap_from_disk(bitmap *b); // write disk_status bitmap back to disk, bitmap block_id

/*
   ========================================
    Disk Page Size 4KB IO
   ========================================
 */

NODE * disk4k_write(unsigned int page_id,unsigned int length,void *buffer);
NODE * disk4k_read(unsigned int page_id, unsigned int length, void *buffer);

#endif /* diskio_h */
