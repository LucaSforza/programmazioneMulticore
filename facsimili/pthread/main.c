#define _GNU_SOURCE // IMPORTANTE: lasciare queste tre righe 
#include <pthread.h>
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#include "utils/logging.h"

#include "args.h"
Global_Contex glob_ctx = {0};

typedef struct {
    int rank;
} Thread_Contex;

void *run(void *arg) {
    Thread_Contex *ctx = arg;
    printf("Hello World from: %d, size: %ld\n",ctx->rank, glob_ctx.thread_size);
    free(ctx);
    return NULL;
}

int main(int argc, char **argv) {
    setvbuf(stderr, NULL, _IONBF, 0);
    parse_args(argc, argv);

    pthread_t *threads = malloc(glob_ctx.thread_size*sizeof(pthread_t));

    for(int i=0; i < glob_ctx.thread_size; i++) {
        Thread_Contex *arg = _aligned_alloc(sizeof(*arg));
        arg->rank = i;
        pthread_create(&threads[i],NULL,run,arg);
    }

    for(int i=0; i < glob_ctx.thread_size; i++) {
        pthread_join(threads[i],NULL);
    }

    free(threads);
    return 0;
}