#include "stack_types.h"
#include "errors.h"
#include "const.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


static stack_array Stack = {};

void stack_array_decrease (int num){

    memcpy (Stack.stack_ptrs + num, Stack.stack_ptrs + num + 1, Stack.numOfStack - num - 1);

    Stack.numOfStack --;
    stack_array_size_check();

}

void stack_array_increase (void){

    if(Stack.numOfStack != 0){
        Stack.numOfStack ++;
        stack_array_size_check();
    }
    else{
        Stack.numOfStack ++;
        stack_array_size_check();
        Stack.numOfStack --;

    }

}

void stack_array_size_check (){

    if (Stack.numOfStack == 0 && Stack.capacity != 0){

        free(Stack.stack_ptrs);

        Stack.stack_ptrs = NULL;

        Stack.capacity = 0;


    }

    else if (Stack.numOfStack >= Stack.capacity){

        int minAllowdSize  = (Stack.numOfStack * INCREASE_STEP) > START_STACK_ARR_SIZE ? (Stack.numOfStack * INCREASE_STEP) : START_STACK_ARR_SIZE;
        void **tmp_pointer = (void **)realloc(Stack.stack_ptrs, sizeof(void*)* minAllowdSize);

        assert(tmp_pointer);

        Stack.stack_ptrs = tmp_pointer;
        Stack.capacity   = minAllowdSize;

    }

    else if (Stack.numOfStack < Stack.capacity/DECREASE_STEP){

        int minAllowdSize  = (Stack.numOfStack / REAL_DECREASE_STEP) > START_STACK_ARR_SIZE ? (Stack.numOfStack / REAL_DECREASE_STEP) : START_STACK_ARR_SIZE;

        void **tmp_pointer = (void **)realloc(Stack.stack_ptrs, sizeof(void*)* minAllowdSize);

        assert(tmp_pointer);

        Stack.stack_ptrs = tmp_pointer;
        Stack.capacity   = minAllowdSize;

    }

}

int stack_ok (int num){

    void *vptrTargetStack = Stack.stack_ptrs[num];

    if (!vptrTargetStack){
        Stack_error_global   = NULL_STACK_PTR;
        Problem_steck_global = vptrTargetStack;
        return NULL_STACK_PTR;
    }

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if (!(ptrTargetStack->dataPtr)){
        Stack_error_global   = NULL_DATA_PTR;
        Problem_steck_global = vptrTargetStack;
        return NULL_DATA_PTR;
    }

    if ( (ptrTargetStack->currSize) > (ptrTargetStack->maxSize) ){
        Stack_error_global   = STACK_OVERFLOW;
        Problem_steck_global = vptrTargetStack;
        return STACK_OVERFLOW;
    }

    if ( (ptrTargetStack->currSize) < 0 ){
        Stack_error_global = STACK_UNDERFLOW;
        Problem_steck_global = vptrTargetStack;
        return STACK_UNDERFLOW;
    }

    return 0;

}

int stack_dump (int num, int checkNeed){

    void *vptrTargetStack = Stack.stack_ptrs[num];

    if (checkNeed == 1){

        if(Stack_error_global == NULL_STACK_PTR){
            printf("ERROR pointer tustruct is NULL");
            return NULL_STACK_PTR;
        }

        stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;
        printf("currSize = %d, maxsize = %d\n", ptrTargetStack->currSize, ptrTargetStack->maxSize);

        if(Stack_error_global == NULL_DATA_PTR){
            printf("ERROR pointer tustruct is NULL");
            return NULL_DATA_PTR;
        }
        return 0;

    }

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    printf("currSize = %d, maxsize = %d\n", ptrTargetStack->currSize, ptrTargetStack->maxSize);

    return 0;
}

int stack_size_chk (int num){

    void *vptrTargetStack = Stack.stack_ptrs[num];

    IF_ERR_GO_OUT(num);

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if(  (ptrTargetStack->currSize)  >=  (ptrTargetStack->maxSize)  ){

        void *tmpDataPtr = realloc(ptrTargetStack->dataPtr ,sizeof(int) * (ptrTargetStack->maxSize) * SIZE_STEP_UP);

        if(tmpDataPtr == NULL){
            printf("ERROR cant expend stack.");
            return 0;
        }
        //printf("\n\nextstartsize = %d  ", ptrTargetStack->maxSize);
        ptrTargetStack->dataPtr  = tmpDataPtr;
        ptrTargetStack->maxSize *= SIZE_STEP_UP;
        //printf("\n\nsize = %d  ", ptrTargetStack->maxSize);

        return 1;

    }
    else if(  ((ptrTargetStack->currSize)  <  (ptrTargetStack->maxSize/SIZE_STEP_DOWN))  &&
            ((ptrTargetStack->maxSize) > START_STACK_SIZE)  ){
            printf("aaaaaaaaaaaaaaaaaaa");

        //printf("\n\nstartsize = %d   crrsize = %d   ", ptrTargetStack->maxSize, ptrTargetStack->currSize);

        ptrTargetStack->maxSize /= SIZE_STEP_DOWN;

        void *tmpDataPtr = realloc(ptrTargetStack->dataPtr, sizeof(int) * (ptrTargetStack->maxSize));

        //printf("   size = %d\n\n", ptrTargetStack->maxSize);

        if(tmpDataPtr == NULL){
            printf("ERROR cant narrow down stack.");
            return 0;
        }

        ptrTargetStack->dataPtr  = tmpDataPtr;

        return 1;

    }

    IF_ERR_GO_OUT(num);

    return 1;

}

int stack_ctor (void){

    stack_array_increase();

    void ** VptrTargetStack = &Stack.stack_ptrs[Stack.numOfStack];

    if(!VptrTargetStack){
        printf("Error, can't make stack");
        return 5;
    }

    stack_t *ptrTargetStack = (stack_t *)calloc(sizeof(stack_t), 1);
    *VptrTargetStack = ptrTargetStack;

    void *tmpPointer  = (void *)calloc(sizeof(int), START_STACK_SIZE);
    assert(tmpPointer);
    ptrTargetStack->dataPtr = tmpPointer;

    ptrTargetStack->currSize = 0;
    ptrTargetStack-> maxSize = START_STACK_SIZE;

    IF_ERR_GO_OUT(Stack.numOfStack);

    return Stack.numOfStack;
}

int pop (int num){

    void *vptrTargetStack = Stack.stack_ptrs[num];

    IF_ERR_GO_OUT(num);

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if(ptrTargetStack->currSize < 1){
        printf("Error stack is empty");
        return ERROR_RETURN;
    }

    //assert(ptrTargetStack);
    //assert(ptrTargetStack->dataPtr);

    int tamporyEl = *((int*)(ptrTargetStack->dataPtr) + --ptrTargetStack->currSize);

    stack_size_chk(num);

    IF_ERR_GO_OUT(num);

    return tamporyEl;
}

int push (int num, int pushingEl){

    void *vptrTargetStack = Stack.stack_ptrs[num];

    IF_ERR_GO_OUT(num);

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    //assert(ptrTargetStack);
    //assert(ptrTargetStack->dataPtr);

    ptrTargetStack->currSize++;

    stack_size_chk(num);

    *((int*)(ptrTargetStack->dataPtr) + (ptrTargetStack->currSize - 1)) = pushingEl;

    IF_ERR_GO_OUT(num);

    return stack_ok(num);

}

int look (int num, int ElNum){

    void *vptrTargetStack = Stack.stack_ptrs[num];

    IF_ERR_GO_OUT(num);

    //assert(vptrTargetStack);
    //assert(((stack_t *)vptrTargetStack)->dataPtr);

    stack_t * ptrTtargetStack = (stack_t *)vptrTargetStack;

    //add ElNum obrobotku

    IF_ERR_GO_OUT(num);

    return *((int*)(ptrTtargetStack->dataPtr) + (ptrTtargetStack->currSize - 1 - ElNum));

}

int stack_dtor (int num, int check_right){

    void *vptrTargetStack = Stack.stack_ptrs[num];

    if(num < 0 || num)

    if(  (Stack_error_global != NULL_STACK_PTR)  ||  !(check_right)  ){

        stack_t * ptrTtargetStack = (stack_t *)vptrTargetStack;

        if(  (Stack_error_global != NULL_DATA_PTR)  ||  !(check_right)  ){
            free(ptrTtargetStack->dataPtr);
        }
        free(ptrTtargetStack);
    }

    stack_array_decrease (num);

    return 0;
}
