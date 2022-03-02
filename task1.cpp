#include <stdio.h>
#include <omp.h>

#define TOSTR(x) (#x)

int main(){

omp_set_num_threads(8);  
#pragma omp parallel
        {
            printf("%s %d\n", TOSTR(omp_get_thread_num), omp_get_thread_num());
			printf("%s %d\n", TOSTR(omp_get_num_threads), omp_get_num_threads());
			printf("Hello World!\n");
        }
    
}

///вывод не всегда идентичен, потому что мы не можем воздейтсвовать на планировщик задач. Он работает непредвиденно