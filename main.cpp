#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack_types.h"


int stack_ok(stack_t * targetStack){

    int g = (1 & (int)(targetStack->dataPtr));//что ещё нужно?

}

int stack_init(stack_t ** ptrtargetStack){

    //assert(targetStack);

    stack_t *targetStack = (stack_t *)calloc(sizeof(stack_t), 1);
    *ptrtargetStack = targetStack;

    stack_t *tmpPointer  = (stack_t *)calloc(sizeof(int), START_STACK_SIZE);
    assert(tmpPointer);
    targetStack->dataPtr = tmpPointer;

    targetStack->currSize = 0;
    targetStack-> maxSize = START_STACK_SIZE;

    return targetStack-> maxSize;
}

int pop(stack_t * targetStack){

    if(targetStack->currSize < 1){
        printf("Error stack is empty");
        return ERROR_RETURN;
    }

    assert(targetStack);
    assert(targetStack->dataPtr);

    int tamporyEl = *((int*)(targetStack->dataPtr) + --targetStack->currSize);

    //add sizechack

    return tamporyEl;
}

int push(stack_t * targetStack, int pushingEl){

    assert(targetStack);
    assert(targetStack->dataPtr);

    targetStack->currSize++;

    //add size++

    *((int*)(targetStack->dataPtr) + (targetStack->currSize - 1)) = pushingEl;

    return targetStack->currSize;

}

int look(stack_t * targetStack, int ElNum){

    assert(targetStack);
    assert(targetStack->dataPtr);

    //add ElNum obrobotku

    return *((int*)(targetStack->dataPtr) + (targetStack->currSize - 1 - ElNum));

}

int main()
{
    stack_t *testStack = NULL;
    stack_init(&testStack);

    push(testStack, 10);
    push(testStack, 20);
    printf("%d\n", look(testStack, 0));
    printf("%d\n", pop(testStack));
    printf("%d\n", pop(testStack));
    printf("%d\n", pop(testStack));
}
