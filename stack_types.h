#ifndef STACK_TYPES_H_INCLUDED
#define STACK_TYPES_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define IF_ERR_GO_OUT(a){               \
        stack_ok(a);                    \
        if(Stack_error_global != 0){    \
            return Stack_error_global;  \
        }                               \
}                                       \


typedef int stackEl;

const int START_STACK_SIZE = 10;
const int SIZE_STEP_UP     = 2;
const int SIZE_STEP_DOWN   = SIZE_STEP_UP * SIZE_STEP_UP;
const int ERROR_RETURN     = -2147483648;


struct stack_t{

    int64_t strCanry = 0;
    void *dataPtr    = NULL;
    int currSize     = 0;
    int maxSize      = 0;
    int64_t endCamry = 0;

};

int look(void * vptrTargetStack, int ElNum);

int push(void * vptrTargetStack, int pushingEl);

int pop(void * vptrTargetStack);

int stack_ctor(void ** VptrTargetStack);

int stack_size_chk(void *vptrTargetStack);

int stack_dump(void *vptrTargetStack, int checkNeed);

int stack_ok(void *vptrTargetStack);

int stack_dtor(void * vptrTargetStack, int check_right);

#endif // STACK_TYPES_H_INCLUDED
