#include "common.h"

int main()
{
    int latency;

    srand(time(NULL));

    set_cpu(2);

    while(1)
    {
        latency = 40 + rand() % 12;

        if(latency >= 50)
        {
            printf("\n");

            printf("----------------------------------------\n");
            printf("LATENCY INSTABILITY DETECTED\n");
            printf("----------------------------------------\n");
            printf("\n");

            printf("guardian analysis :\n");
            printf("latency approaching deadline\n");
            printf("predictive overload warning issued\n");
            printf("critical controller timing preserved\n");
            printf("\n");

            write_blackbox("latency warning");
        }

        sleep(5);
    }

    return 0;
}
