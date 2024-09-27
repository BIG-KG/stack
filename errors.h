#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define IF_RIGHT_STACK if(!Stack_error_global)

             /*if(docheck != ' '){
                stack_ok(doChaeck);
            }*/


#define CHECK(doChaeck) ;                                               \
            if(Stack_error_global != 0){                                \
                printf("Error on line %d", __LINE__ );                  \
                if(      (Stack_error_global == STACK_UNDERFLOW)  ||    \
                         (Stack_error_global == STACK_OVERFLOW )    ){  \
                                                                        \
                    stack_dump(Problem_steck_global, 1);                \
                                                                        \
                }                                                       \
                else if( (Stack_error_global == NULL_STACK_PTR) ||      \
                         (Stack_error_global == NULL_DATA_PTR )    ){   \
                                                                        \
                    stack_dump(Problem_steck_global, 1);                \
                }                                                       \
                stack_dtor(doChaeck, 1);                                \
            }                                                                                                                                   \

          /*нужно ли делать?(stack_dtor(doChaeck))*/

enum error_codes{

    NULL_STACK_PTR  = 4,
    NULL_DATA_PTR   = 3,
    STACK_OVERFLOW  = 2,
    STACK_UNDERFLOW = 1

};

#endif // ERRORS_H_INCLUDED
