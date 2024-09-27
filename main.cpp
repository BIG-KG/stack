#include "stack_types.h"
#include "errors.h"


int main()
{
    void * testStack = NULL;
    stack_init(&testStack);

    push(testStack, 10);
    push(testStack, 20);
    printf("%d\n", look(testStack, 0));
    printf("%d\n", pop(testStack));
    push(testStack, 30);
    push(testStack, 40);
    printf("%d\n", pop(testStack));
    printf("%d\n", pop(testStack));
}
