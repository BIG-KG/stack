#ifndef STACK_TYPES_H_INCLUDED
#define STACK_TYPES_H_INCLUDED

const int START_STACK_SIZE = 10;
const int ERROR_RETURN = -2147483648;


struct stack_t{

    void *dataPtr = NULL;
    int currSize= 0;
    int maxSize = 0;

};

#endif // STACK_TYPES_H_INCLUDED
