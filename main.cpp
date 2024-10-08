#include "stack_funk.h"
//#include "inner_stack_metods.h"

#include "errors.h"

#include "const.h"

int main()
{
    /*
    for(int i = 0; i < 260; i ++){
        printf("%lld\n", right_random_64());
    }*/

    int64_t test0   = stack_ctor();
    int64_t test100 = stack_ctor();
    for(int i = 0 ; i < 100; i++){
        test100 = stack_ctor();
        //printf("%lld\n", test);
    }

    push(test0, 10);
    push(test0, 20);
    push(test0, 30);
    push(test100, 40);
    push(test100, 50);
    push(test100, 60);
    printf("%d\n", pop(test0));
    printf("%d\n", pop(test0));
    printf("%d\n", pop(test0));
    printf("%d\n", pop(test100));
    printf("%d\n", pop(test100));
    printf("%d\n", pop(test100));
    return 0;
}
