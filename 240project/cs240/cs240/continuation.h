//
//  continuation.h
//  cs240
//
//  Created by Lu Yu on 11/25/16.
//  Copyright © 2016 Lu Yucom. All rights reserved.
//

#ifndef continuation_h
#define continuation_h
#include "hardware_interface.h"

#define CONTINUATION_SIZE                   512
#define FALSE                               0
#define TRUE                                1

// function pointer variable
typedef void (*cont_func) (int*);

typedef struct cont_obj{
    cont_func func;
    void *params;
} cont_obj;

typedef struct handlerCont{
    t_id tid;
    struct cont_obj *co;
    char empty;
} handlerCont;

extern handlerCont handlerArrays[CONTINUATION_SIZE];

void init_cont(handlerCont *hc);

void add_cont(handlerCont *hc, handlerCont *ce);

void insert_cont(handlerCont *hc, cont_obj *co, int tid);

void remove_cont(handlerCont *hc, int index);

handlerCont *find_cont(handlerCont *hc, t_id tid);

#endif /* continuation_h */
