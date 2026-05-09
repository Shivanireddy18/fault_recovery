#include "common.h"

int main()
{
    set_cpu(3);

    printf("non critical core hog active on core 3\n");

    while(1)
    {
    }

    return 0;
}
