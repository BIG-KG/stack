#include "stack_funk.h"

#include "errors.h"

#include "const.h"

int main()
{

    int64_t test = stack_ctor();
    for(int i = 0 ; i < 100; i++){
        push(test, i);
    }
    stack_dump(test, 0);

    int64_t test1 = stack_ctor();
    for(int i = 100 ; i > 0; i--){
        push(test1, i);
    }
    stack_dtor(test);
    stack_dump(test1, 0);

    return 0;
}
