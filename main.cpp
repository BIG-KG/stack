#include "stack_funk.h"
//#include "inner_stack_metods.h"

#include "errors.h"

#include "const.h"


struct copy_stack_t{

    int64_t strCanry = 0;
    void *dataPtr    = NULL;
    int currSize     = 0;
    int maxSize      = 0;
    int64_t endCamry = 0;

};



int main()
{

<<<<<<< Updated upstream
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
=======
>>>>>>> Stashed changes
    return 0;
}
