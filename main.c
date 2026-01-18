#define _GNU_SOURCE
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

#define FS_NUM 5
#define MAX_INPUT 120
volatile sig_atomic_t work = 1;

void sigint_handler(int sig) { work = 0; }

int set_handler(void (*f)(int), int sigNo)
{
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    act.sa_handler = f;
    if (-1 == sigaction(sigNo, &act, NULL))
        return -1;
    return 0;
}

int main()
{
    if (set_handler(sigint_handler, SIGINT))
        ERR("Setting SIGINT:");
    //do_work();
    fprintf(stderr, "Program has terminated.\n");
    return EXIT_SUCCESS;
}