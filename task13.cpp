#include <stdio.h>
#include <omp.h>

#define TOSTR(x) (#x)
#define OUT printf("Hello World!\t%s %d, %s %d\n", TOSTR(omp_get_thread_num), omp_get_thread_num(),TOSTR(omp_get_num_threads), omp_get_num_threads());

void raise1()
{
    #pragma omp parallel
    {
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 7)
            OUT
        }
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 6)
            OUT
        }
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 5)
            OUT
        }
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 4)
            OUT
        }
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 3)
            OUT
        }
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 2)
            OUT
        }
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 1)
            OUT
        }
        #pragma omp barrier
        {
            if(omp_get_thread_num() == 0)
            OUT
        }            
    }
    return;
}

void raise2()
{
#pragma omp parallel num_threads(8)
    {
        int n = omp_get_num_threads();
        for (int i = n - 1; i >= 0; i--)
        {
#pragma omp barrier
            {
                if (i == omp_get_thread_num())
                {
#pragma omp critical
                    OUT
                }
            }
        }
    }
    return;
}


/*void raise3()
{
        omp_set_num_threads(8);  
    int i;
    #pragma omp parallel private (i)
    {
        #pragma omp for ordered depend (sink: i+1)
        for (i=7; i >=0 ; i--)
        {
            #pragma omp ordered depend (source)
                {
                OUT
                }
        }
    }
}*/

void raise3()
{
    omp_set_num_threads(8);  
    int i;
    #pragma omp parallel private (i)
    {
        #pragma omp for ordered 
        for (i=7; i >=0 ; i--)
        {
            #pragma omp ordered 
                {
                printf("Hello World!\t%s %d, %s %d\n", TOSTR(omp_get_thread_num), 7 - omp_get_thread_num(),TOSTR(omp_get_num_threads), omp_get_num_threads());
                }
        }
    }
}


void raise4()
{
    omp_lock_t mutex;

    int idx;

    omp_init_lock(&mutex);
    int number = 7;
#pragma omp parallel shared(mutex,number) private(idx)
    {
        while (number!=-1) {
            idx = omp_get_thread_num();

            omp_set_lock(&mutex);
            if (omp_get_thread_num() == number)
            {
            #pragma omp critical
                {
                    OUT
                    --number;
                }
            }
            omp_unset_lock(&mutex);
        }
    }
    omp_destroy_lock(&mutex);
    return;

}


int main(){

    omp_set_num_threads(8);  
    raise1();
    raise2();
    raise3();
    raise4();

    return 0;
}
