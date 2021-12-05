#include "spin.h"

void spin_init(spin_t *spin){
    spin->flag = 0;
}

void spin_lock(spin_t *spin){
    asm("loop:\n\t"
        "xchgb %%al, %0\n\t"
        "testb %%al, %%al\n\t"
        "jnz loop":
        "=m"(spin->flag):
        "a"(1)
    );
}

void spin_unlock(spin_t *spin){
    asm("xchgb %%al, %0":
        "=m"(spin->flag):
        "a"(0)
    );
}