#include "common.h"

pid_t primary_pid;
pid_t ghost_pid;
pid_t media_pid;
pid_t guardian_pid;
pid_t controller_pid;

int system_state = NORMAL_OPERATION;

int primary_restart_count = 0;

pid_t start_process(const char *path)
{
    pid_t pid;

    pid = spawnlp(P_NOWAIT,
                  path,
                  path,
                  NULL);

    if(pid == -1)
    {
        perror("spawnlp");
    }

    return pid;
}

int process_alive(pid_t pid)
{
    int status;

    pid_t result;

    result = waitpid(pid,
                     &status,
                     WNOHANG);

    if(result == 0)
    {
        return 1;
    }

    return 0;
}

int main()
{
//    set_cpu(2);

    printf("\n");
    printf("----------------------------------------\n");
    printf("THE UNSTOPPABLE SYSTEM\n");
    printf("Deterministic Fault Tolerant ADAS\n");
    printf("----------------------------------------\n");
    printf("\n");

    printf("initializing qnx supervisory architecture\n");
    printf("\n");

    printf("loading safety critical services\n");
    printf("loading non critical services\n");
    printf("\n");

    printf("assigning cpu partitions\n");
    printf("\n");

    printf("core 0 -> safe controller\n");
    printf("core 1 -> primary lidar\n");
    printf("core 2 -> ghost + watchdog\n");
    printf("core 3 -> media + background\n");
    printf("\n");

    printf("starting watchdog supervisor\n");
    printf("starting arbitration manager\n");
    printf("starting predictive guardian\n");
    printf("\n");

    printf("starting primary perception\n");

    primary_pid =
        start_process("/tmp/primary_app");

    printf("starting ghost backup\n");

    ghost_pid =
        start_process("/tmp/ghost_app");

    printf("starting safe controller\n");

    controller_pid =
        start_process("/tmp/controller_app");

    printf("starting predictive guardian process\n");

    guardian_pid =
        start_process("/tmp/guardian_app");

    printf("starting media services\n");

    media_pid =
        start_process("/tmp/media_app");

    printf("\n");

    printf("system initialization complete\n");

    printf("\n");

    printf("----------------------------------------\n");
    printf("SYSTEM STATE : NORMAL OPERATION\n");
    printf("PRIMARY SYSTEM : ACTIVE\n");
    printf("GHOST SYSTEM   : STANDBY\n");
    printf("----------------------------------------\n");

    printf("\n");

    write_blackbox("system initialized");

    while(1)
    {
        if(!process_alive(media_pid))
        {
            printf("\n");

            printf("----------------------------------------\n");
            printf("NON CRITICAL FAILURE DETECTED\n");
            printf("----------------------------------------\n");
            printf("\n");

            printf("process : media_app\n");
            printf("\n");

            printf("watchdog response :\n");
            printf("restarting media services\n");
            printf("\n");

            write_blackbox("media failure");

            media_pid =
                start_process("/tmp/media_app");

            sleep(2);

            printf("media recovery successful\n");
            printf("\n");

            printf("critical systems remain deterministic\n");
            printf("\n");

            printf("SYSTEM STATE : NORMAL OPERATION\n");
            printf("\n");
        }

        if(system_state == NORMAL_OPERATION)
        {
            if(!process_alive(primary_pid))
            {
                primary_restart_count++;

                printf("\n");

                printf("----------------------------------------\n");
                printf("PRIMARY FAILURE DETECTED\n");
                printf("----------------------------------------\n");
                printf("\n");

                printf("watchdog heartbeat timeout\n");
                printf("arbitration manager notified\n");
                printf("recovery manager engaged\n");
                printf("\n");

                printf("restart attempt : %d\n",
                        primary_restart_count);

                write_blackbox("primary failure");

                if(primary_restart_count <= 2)
                {
                    printf("\n");

                    printf("attempting primary restart\n");

                    primary_pid =
                        start_process("/tmp/primary_app");

                    sleep(2);

                    if(process_alive(primary_pid))
                    {
                        printf("primary recovery successful\n");

                        write_blackbox("primary recovered");
                    }
                    else
                    {
                        printf("primary restart failed\n");
                    }
                }
                else
                {
                    printf("\n");

                    printf("primary considered unstable\n");
                    printf("\n");

                    printf("----------------------------------------\n");
                    printf("TRANSITIONING TO REDUNDANT MODE\n");
                    printf("----------------------------------------\n");
                    printf("\n");

                    printf("ghost backup promoted to ACTIVE\n");
                    printf("controller switched to ghost perception\n");
                    printf("safe path continuity maintained\n");
                    printf("\n");

                    printf("SYSTEM STATE : REDUNDANT OPERATION\n");
                    printf("\n");

                    system_state = REDUNDANT_OPERATION;

                    write_blackbox("ghost active");
                }
            }
        }

        if(system_state == REDUNDANT_OPERATION)
        {
            if(!process_alive(primary_pid))
            {
                printf("primary recovering in background\n");

                primary_pid =
                    start_process("/tmp/primary_app");

                sleep(3);
            }

            if(process_alive(primary_pid))
            {
                printf("\n");

                printf("----------------------------------------\n");
                printf("PRIMARY RECOVERY DETECTED\n");
                printf("----------------------------------------\n");
                printf("\n");

                printf("primary process restarted\n");
                printf("synchronizing perception pipelines\n");

                sleep(2);

                printf("state validation successful\n");
                printf("switching control back to primary\n");
                printf("ghost returned to standby\n");
                printf("\n");

                printf("SYSTEM STATE : NORMAL OPERATION\n");
                printf("\n");

                system_state = NORMAL_OPERATION;

                primary_restart_count = 0;

                write_blackbox("primary restored");
            }

            if(!process_alive(primary_pid) &&
               !process_alive(ghost_pid))
            {
                printf("\n");

                printf("----------------------------------------\n");
                printf("CRITICAL REDUNDANCY FAILURE\n");
                printf("----------------------------------------\n");
                printf("\n");

                printf("primary unavailable\n");
                printf("ghost unavailable\n");
                printf("\n");

                printf("all redundant perception lost\n");
                printf("initiating fail safe strategy\n");
                printf("vehicle entering minimum risk state\n");
                printf("\n");

                printf("SYSTEM STATE : FAIL SAFE MODE\n");
                printf("\n");

                system_state = FAIL_SAFE_MODE;

                write_blackbox("fail safe mode");
            }
        }

        sleep(2);
    }

    return 0;
}
