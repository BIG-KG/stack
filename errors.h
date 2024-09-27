#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#defile IF_RIGHT_STACK if(!Stack_error_global)


#defile CHECK(doChaeck) ; {                                             \
            /*if(docheck != ' '){                                         \
                stack_ok(doChaeck);                                     \   нужно ли ещё раз проверять?
            }*/                                                           \
                                                                        \                                                                        \
            if(Stack_error_global != 0){                                \
                printf("Error on line %d", __LINE__ );                  \
                if(      (Stack_error_global == STACK_UNDERFLOW)  ||    \
                         (Stack_error_global == STACK_OVERFLOW )    ){  \
                                                                        \
                    stackdump(Problem_stack_global, 1);                 \
                                                                        \
                }                                                       \
                else if( (Stack_error_global == NULL_STACK_PTR) ||      \
                         (Stack_error_global == NULL_DATA_PTR ){        \
                                                                        \
                    stackdump(Problem_stack_global, 1);                 \
                                                                        \
                }                                                       \
                stack_dtor(doChaeck)                                    \
            }                                                           \ /*нужно ли делать?*/                                                                       \
         }                                                              \

enum error_codes{

    NULL_STACK_PTR  = 4,
    NULL_DATA_PTR   = 3,
    STACK_OVERFLOW  = 2,
    STACK_UNDERFLOW = 1

};

#endif // ERRORS_H_INCLUDED
