#include "common.h"

void set_cpu(int cpu)
{
    unsigned runmask;

    runmask = 1U << cpu;

    ThreadCtl(_NTO_TCTL_RUNMASK,
              (void *)(uintptr_t)runmask);
}

void write_blackbox(const char *event)
{
    FILE *fp;

    fp = fopen("/tmp/blackbox.log", "a");

    if(fp == NULL)
    {
        return;
    }

    fprintf(fp,
            "%s\n",
            event);

    fclose(fp);
}
