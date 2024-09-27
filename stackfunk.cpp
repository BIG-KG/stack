#include "stack_types.h"
#include "errors.h"
#include "const.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern char Stack_error_global;
extern void *Problem_steck_global;

int stack_ok(void *vptrTargetStack){

    if (!vptrTargetStack){
        Stack_error_global = NULL_STACK_PTR;
        Problem_steck_global = vptrTargetStack;
        return NULL_STACK_PTR;
    }

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if (!(ptrTargetStack->dataPtr)){
        Stack_error_global = NULL_DATA_PTR;
        Problem_steck_global = vptrTargetStack;
        return NULL_DATA_PTR;
    }

    if ( (ptrTargetStack->currSize) > (ptrTargetStack->maxSize) ){
        Stack_error_global = STACK_OVERFLOW;
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

int stack_dump(void *vptrTargetStack, int checkNeed){

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

int stack_size_chk(void *vptrTargetStack){

    IF_ERR_GO_OUT(vptrTargetStack);

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

    IF_ERR_GO_OUT(vptrTargetStack);

    return 1;

}

int stack_ctor(void ** VptrTargetStack){


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

    IF_ERR_GO_OUT(*VptrTargetStack);

    return ptrTargetStack-> maxSize;
}

int pop(void * vptrTargetStack){

    IF_ERR_GO_OUT(vptrTargetStack);

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if(ptrTargetStack->currSize < 1){
        printf("Error stack is empty");
        return ERROR_RETURN;
    }

    //assert(ptrTargetStack);
    //assert(ptrTargetStack->dataPtr);

    int tamporyEl = *((int*)(ptrTargetStack->dataPtr) + --ptrTargetStack->currSize);

    stack_size_chk(vptrTargetStack);

    IF_ERR_GO_OUT(vptrTargetStack);

    return tamporyEl;
}

int push(void * vptrTargetStack, int pushingEl){

    IF_ERR_GO_OUT(vptrTargetStack);

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    //assert(ptrTargetStack);
    //assert(ptrTargetStack->dataPtr);

    ptrTargetStack->currSize++;

    stack_size_chk(vptrTargetStack);

    *((int*)(ptrTargetStack->dataPtr) + (ptrTargetStack->currSize - 1)) = pushingEl;

    IF_ERR_GO_OUT(vptrTargetStack);

    return stack_ok(vptrTargetStack);

}

int look(void * vptrTargetStack, int ElNum){

    IF_ERR_GO_OUT(vptrTargetStack);

    //assert(vptrTargetStack);
    //assert(((stack_t *)vptrTargetStack)->dataPtr);

    stack_t * ptrTtargetStack = (stack_t *)vptrTargetStack;

    //add ElNum obrobotku

    IF_ERR_GO_OUT(vptrTargetStack);

    return *((int*)(ptrTtargetStack->dataPtr) + (ptrTtargetStack->currSize - 1 - ElNum));

}

int stack_dtor(void * vptrTargetStack, int check_right){

    static int had_dest = 0;

    if(!had_dest){
        if(  (Stack_error_global != NULL_STACK_PTR)  ||  !(check_right)  ){

            stack_t * ptrTtargetStack = (stack_t *)vptrTargetStack;
            if(  (Stack_error_global != NULL_DATA_PTR)  ||  !(check_right)  ){
                free(ptrTtargetStack->dataPtr);
            }
            free(ptrTtargetStack);
        }
    }

    had_dest = 1;

    return 0;
}



