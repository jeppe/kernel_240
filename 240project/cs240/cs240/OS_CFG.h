//
//  OS_CFG.h
//  cs240
//
//  Created by Lu Yu on 11/25/16.
//  Copyright © 2016 Lu Yucom. All rights reserved.
//

#ifndef OS_CFG_h
#define OS_CFG_h

#define FALSE 0
#define TRUE  1
#define WRITE 1
#define READ  0

/*
 ========================= Continuation =======================
 */

#define CONTINUATION_SIZE                   512

/*
 ========================= DISK PAGE =======================
 */
#define DISK_DEBUG_FLAG     1 // debug flag 1
#define DISK_PAGE_SIZE      8 // disk storage unit equals to 8 sectors

/*
   ======================= BITMAP =======================
 */
#define BITMAP_DISK_BLOCK                    2
#define BIT                                  (8 * sizeof(int))
#define BITMAP_NOTFOUND                      -1
#define BITMAP_SIZE                          4096

#endif /* OS_CFG_h */
