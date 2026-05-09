#include "common.h"

int main()
{
    set_cpu(1);

    printf("critical core hog active on core 1\n");

    while(1)
    {
    }

    return 0;
}
