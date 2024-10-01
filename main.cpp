#include "stack_types.h"

#include "errors.h"

#include "const.h"

int main()
{
    void * testStack = NULL;
    stack_ctor(&testStack);

    IF_RIGHT_STACK push(testStack, 10) CHECK(testStack);
    IF_RIGHT_STACK push(testStack, 20) CHECK(testStack);
    printf("%d\n", look(testStack, 0));
    printf("%d\n", pop(testStack));
    push(testStack, 30);
    push(testStack, 40);
    printf("%d\n", pop(testStack));
    printf("%d\n", pop(testStack));


    stack_dtor(testStack, 1);

    return 0;
}
