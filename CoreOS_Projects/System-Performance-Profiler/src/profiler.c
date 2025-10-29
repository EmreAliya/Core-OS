#include <stdio.h>
#include <stdint.h>
#include <time.h>

uint64_t rdtsc() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

void simulate_task(const char *name, int cycles) {
    uint64_t start = rdtsc();
    for (volatile int i = 0; i < cycles * 1000; i++);
    uint64_t end = rdtsc();
    printf("Task %-10s ran for %lu ns\n", name, end - start);
}

int main() {
    printf("=== System Performance Profiler ===\n");
    simulate_task("TaskA", 100);
    simulate_task("TaskB", 200);
    simulate_task("TaskC", 150);
    return 0;
}
