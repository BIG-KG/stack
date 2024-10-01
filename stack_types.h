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

const int START_STACK_SIZE     = 10;
const int SIZE_STEP_UP         = 2;
const int SIZE_STEP_DOWN       = SIZE_STEP_UP * SIZE_STEP_UP;
const int INCREASE_STEP        = 2;
const int DECREASE_STEP        = 2;
const int REAL_DECREASE_STEP   = 2;
const int START_STACK_ARR_SIZE = 10;
const int ERROR_RETURN        = -2147483648;



struct stack_t{


    void *dataPtr = NULL;
    int currSize  = 0;
    int maxSize   = 0;
};

struct stack_array{

    void **stack_ptrs = NULL;
    int capacity      = 0;
    int numOfStack    = -1;
    int stacksExist   = 0;

};

void stack_array_decrease (int num);

void stack_array_increase (void);

void stack_array_size_check ();

int stack_ok(int num);

int stack_dump(int num, int checkNeed);

int stack_size_chk(int num);

int stack_ctor();

int pop(int num);

int push(int num, int pushingEl);

int look(int num, int ElNum);

int stack_dtor(int num, int check_right);

#endif // STACK_TYPES_H_INCLUDED
