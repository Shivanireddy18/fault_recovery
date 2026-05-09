#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/neutrino.h>
#include <sys/wait.h>

extern char **environ;

#define NORMAL_OPERATION      1
#define REDUNDANT_OPERATION   2
#define FAIL_SAFE_MODE        3

void set_cpu(int cpu);

void write_blackbox(const char *event);

#endif
