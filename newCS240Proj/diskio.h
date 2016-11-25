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

#define BITMAP_DISK_BLOCK                    66

// Bitmap to track free disk blocks
typedef struct bitmap{
    int map[4096];
} bitmap;

/* 
   ===================================
   Define bit map available operations
   ===================================
 */

int get_free_block_id(bitmap map); // get free block id

int map_row_num(int bid); // get row number for the bitmap
int map_col_num(int bid); // get column number for the bitmap

void delete_block(bitmap map, int bid); // delete a single block
void flip_bitmap(bitmap map, int bid); // flip bitmap

void write_bitmap_disk(bitmap *map, int disk_block_id); // write disk_status bitmap back to disk, bitmap block_id


#endif /* diskio_h */
