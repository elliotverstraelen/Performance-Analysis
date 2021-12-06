#ifndef _SPIN_H_
#define _SPIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    u_int8_t flag;
} spin_t;

void spin_init(spin_t *spin);
void spin_lock(spin_t *spin);
void spin_unlock(spin_t *spin);

#endif