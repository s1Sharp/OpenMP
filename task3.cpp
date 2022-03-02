#include <iostream>
#include <omp.h>

int main() {

    int a = 0, b = 0;
    printf("first input: a = %d, b = %d;\n", a, b);

#pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        a = 0;
        a += omp_get_thread_num();
        b += omp_get_thread_num();
        printf("in area:  %d, a = %d, b = %d\n", omp_get_thread_num(), a, b);
    }
    printf("after fisrt input: a = %d, b = %d\n", a, b);
#pragma omp parallel num_threads(4) shared(a) private(b)
    {
        b = 0;
        a -= omp_get_thread_num();
        b -= omp_get_thread_num();
        printf("in area:  %d, a = %d, b = %d\n", omp_get_thread_num(), a, b);
    }
    printf("after second input: a = %d, b = %d\n", a, b);

  return 0;
}