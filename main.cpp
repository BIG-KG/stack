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
    printf("%d\n", pop(test));
    printf("%d\n", pop(test));


}
