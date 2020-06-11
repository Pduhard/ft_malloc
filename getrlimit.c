/* -*- mode: c; indent-tabs-mode: nil; c-basic-offset: 4; coding: utf-8-unix -*- */
#include <stdio.h>
#include <stdint.h>
#include <sys/resource.h>
#include <unistd.h>

void print_rlimit(struct rlimit *r, const char *name) {
    int64_t cur;                /* Soft limit */
    int64_t max;                /* Hard limit */
    cur = r->rlim_cur;
    max = r->rlim_max;
    printf("RLIMIT_%s :rlim_cur => %#lx, :rlim_max => %#lx\n",
           name, cur, max);
}

int main(int argc, char *argv[]) {
    struct rlimit rlim;
    int resources[] = {RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA, RLIMIT_FSIZE,
                       RLIMIT_MEMLOCK, RLIMIT_NOFILE, RLIMIT_NPROC, RLIMIT_RSS,
                       RLIMIT_STACK};
    const char *names[] = {"CORE", "CPU", "DATA", "FSIZE",
                           "MEMLOCK", "NOFILE", "NPROC", "RSS",
                           "STACK"};
    int n = sizeof(resources)/sizeof(resources[0]);
    int i;
    for (i = 0; i < n; i++) {
        getrlimit(resources[i], &rlim);
        print_rlimit(&rlim, names[i]);
    }
    printf("%x getpagesize\n", getpagesize());
    printf("%lx getpagesize\n", sysconf(_SC_PAGESIZE));
    return 0;
}