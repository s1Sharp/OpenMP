#include <iostream>
#include <omp.h>

int main() {

    omp_set_num_threads(3);

#pragma omp parallel if(omp_get_max_threads() > 2)
    {
      printf("thread - %d, num threads - %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    omp_set_num_threads(2);

#pragma omp parallel if(omp_get_max_threads() > 2)
    {
      printf("Thread - %d, num threads - %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    return 0;
}