#include "canary.h"

int64_t canary(void){

    static int funckStartedTimes = 0;
    static int64_t canary        = 0;

    if(funckStartedTimes == 0){

        canary = canary | ((int64_t)rand())<<32;
        canary = canary | ((int64_t)rand())    ;

    }

    return canary;

}
