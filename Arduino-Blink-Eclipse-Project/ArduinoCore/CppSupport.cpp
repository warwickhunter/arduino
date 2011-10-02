/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  Standard C++ support methods.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#include "WProgram.h"
#include <stdlib.h>

void crash(const char* message) {
    cli();
    for (;;);
}

extern "C" void __cxa_pure_virtual() {
    crash("Error: pure virtual function called");
}

__extension__ typedef int __guard __attribute__((mode (__DI__)));

void * operator new(size_t size) {
    return malloc(size);
}

void operator delete(void * ptr) {
    free(ptr);
}

void * operator new[](size_t size) {
    return malloc(size);
}

void operator delete[](void * ptr) {
    if (ptr)
        free(ptr);
}

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);}
void __cxa_guard_release (__guard *g) {*(char *)g = 1;}
void __cxa_guard_abort (__guard *) {}
