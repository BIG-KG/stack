#include "stack_types.h"

#include "errors.h"

#include "const.h"


int main()
{
    int test = stack_ctor();
    push(test, 3);
    push(test, 4);
    push(test, 5);
    printf("%d\n", pop(test));
    printf("%d\n", pop(test));
    push(test, 6);
    push(test, 7);
    printf("%d\n", pop(test));

    int test2 = stack_ctor();

    push(test2, 0);
    push(test2, 1);
    push(test2, 2);
    printf("%d\n", pop(test2));
    printf("%d\n", pop(test2));


    printf("a  = %d\n", pop(test));

    stack_dtor(test2,  1);
    printf("     wer         \n");
    stack_dtor(test, 1);
    printf("tyu");




    return 0;
}
