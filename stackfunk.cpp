#include "stack_types.h"
#include "errors.h"
#include "const.h"
#include "canary.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int stack_ok(void *vptrTargetStack){

    if (!vptrTargetStack){
        Stack_error_global = NULL_STACK_PTR;
        return NULL_STACK_PTR;
    }

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if (!(ptrTargetStack->dataPtr)){
        Stack_error_global = NULL_DATA_PTR;
        return NULL_DATA_PTR;
    }

    if(  *((int64_t *)(ptrTargetStack->dataPtr) - 1) != canary()  ){
        printf("real canry = %ld, given canry = %ld", canary(), *((int64_t *)(ptrTargetStack->dataPtr) - 1));
        Stack_error_global = BROKEN_CANNARY;
    }

    if ( (ptrTargetStack->currSize) > (ptrTargetStack->maxSize) ){
        Stack_error_global = STACK_OVERFLOW;
        return STACK_OVERFLOW;
    }

    if ( (ptrTargetStack->currSize) < 0 ){
        Stack_error_global = STACK_UNDERFLOW;
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

        int newSize      = (ptrTargetStack->maxSize) * SIZE_STEP_UP;
        void *tmpDataPtr = realloc (  ((char *)ptrTargetStack->dataPtr - 8) , ((sizeof(stackEl) * newSize / 64)  + 3) * 64  );

        if(tmpDataPtr == NULL){
            printf("ERROR cant expend stack.");
            return 0;
        }

        plant_canary(tmpDataPtr, newSize, sizeof(stackEl));
        ptrTargetStack->dataPtr  = (char *)tmpDataPtr + 8;
        ptrTargetStack->maxSize *= SIZE_STEP_UP;

        return 1;

    }


    else if(  ((ptrTargetStack->currSize)  <  (ptrTargetStack->maxSize/SIZE_STEP_DOWN))  &&
              ((ptrTargetStack->maxSize) > START_STACK_SIZE)  ){

        ptrTargetStack->maxSize /= SIZE_STEP_DOWN;

        void *tmpDataPtr = realloc(  ((char *)ptrTargetStack->dataPtr - 8) , ((sizeof(stackEl) * ptrTargetStack->maxSize / 64)  + 3) * 64  );

        if(tmpDataPtr == NULL){
            printf("ERROR cant narrow down stack.");
            return 0;
        }

        plant_canary(tmpDataPtr, ptrTargetStack->maxSize, sizeof(stackEl));
        ptrTargetStack->dataPtr = (char *)tmpDataPtr + 8;

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
    ptrTargetStack->strCanry = canary();
    ptrTargetStack->endCamry = canary();
    *VptrTargetStack = ptrTargetStack;

    int realSize            = (  (sizeof(stackEl) * START_STACK_SIZE / 64)  + 3) * 64;
    void *tmpPointer        = (void *)calloc(realSize, 1);
    assert(tmpPointer);

    plant_canary(tmpPointer, START_STACK_SIZE, sizeof(stackEl));

    ptrTargetStack->dataPtr = (char *)tmpPointer + 8;

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
                free((char *)ptrTtargetStack->dataPtr - 8);
            }
            free(ptrTtargetStack);
        }
    }

    had_dest = 1;

    return 0;
}


