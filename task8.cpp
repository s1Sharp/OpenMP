#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <cmath>


using namespace std;

#define TOSTR(x) (#x)
#define MAS_SIZE 160000

double a[MAS_SIZE];
double b[MAS_SIZE];

enum option{
    NULLOPT=-1,
    STATIC=1,
    DYNAMIC=2,
    GUIDED=3,
    RUNTIME=4
};

double parallel_for_schedule_static(size_t chunk_size)
{            
              
    double start_time, end_time, tick;
    start_time = omp_get_wtime();       

#pragma omp parallel for schedule(static, chunk_size)              
        for (int i = 0; i < MAS_SIZE; ++i)          
        {                                           
            a[i] = double(i + 1);                   
        }                                          
#pragma omp parallel for schedule(static, chunk_size)              
        for (int i = 1; i < MAS_SIZE - 1; ++i)      
        {                                           
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;  
        }                            

    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;

}  

double parallel_for_schedule_dynamic(size_t chunk_size)
{            
              
    double start_time, end_time, tick;
    start_time = omp_get_wtime();  

#pragma omp parallel for schedule(dynamic, chunk_size)              
        for (int i = 0; i < MAS_SIZE; ++i)          
        {                                           
            a[i] = double(i + 1);                   
        }                                          
#pragma omp parallel for schedule(dynamic, chunk_size)              
        for (int i = 1; i < MAS_SIZE - 1; ++i)      
        {                                           
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;  
        }                            

    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;

} 

double parallel_for_schedule_guided(size_t chunk_size)
{                           
    double start_time, end_time, tick;
    start_time = omp_get_wtime();     

#pragma omp parallel for schedule(guided, chunk_size)              
        for (int i = 0; i < MAS_SIZE; ++i)          
        {                                           
            a[i] = double(i + 1);                   
        }                                          
#pragma omp parallel for schedule(guided, chunk_size)              
        for (int i = 1; i < MAS_SIZE - 1; ++i)      
        {                                           
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;  
        }                            

    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;

} 

double parallel_for_schedule_runtime()
{                           
    double start_time, end_time, tick;
    start_time = omp_get_wtime();        

#pragma omp parallel for schedule(runtime)              
        for (int i = 0; i < MAS_SIZE; ++i)          
        {                                           
            a[i] = double(i + 1);                   
        }                                          
#pragma omp parallel for schedule(runtime)              
        for (int i = 1; i < MAS_SIZE - 1; ++i)      
        {                                           
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;  
        }                            

    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;

} 

double check_better_time(double &bettertime, double time, option &betteroption, option opt){
    if (bettertime > time)
    {
        bettertime = time;
        betteroption = opt;
    }
    return time;
}

#define MAX_CHUNK_SIZE 500
#define CHUNK_STEP 1
#define BETTER_TIME INT_MAX

//#define NUM_OF_THREAD;
int main() {

	omp_set_num_threads(8);
    size_t better_opt_cout[4] = {0, 0, 0, 0};
	srand(time(0));
    for (size_t chunk_size = 0; chunk_size < MAX_CHUNK_SIZE; chunk_size += CHUNK_STEP)
    {
        double better_time = (double)BETTER_TIME;
        option better_opt = NULLOPT;
        printf("\tOption %s, time: %.4f msec\n", TOSTR(STATIC),1000 * check_better_time(better_time, parallel_for_schedule_static(chunk_size), better_opt, STATIC));
        printf("\tOption %s, time: %.4f msec\n", TOSTR(DYNAMIC),1000 * check_better_time(better_time, parallel_for_schedule_dynamic(chunk_size), better_opt, DYNAMIC));
        printf("\tOption %s, time: %.4f msec\n", TOSTR(GUIDED),1000 * check_better_time(better_time, parallel_for_schedule_guided(chunk_size), better_opt, GUIDED));
        printf("\tOption %s, time: %.4f msec\n", TOSTR(RUNTIME),1000 * check_better_time(better_time, parallel_for_schedule_runtime(), better_opt, RUNTIME));
        printf("BETTER OPTION %d, BETTER TIME %.4f msec, CHUNK_SIZE = %d\n\n", better_opt, 1000 * better_time, chunk_size);
        better_opt_cout[better_opt-1] ++;
    }
    printf("BETTER Options count:\nSTATIC: %d\nDYNAMIC: %d\nGUIDED: %d\nRUNTIME: %d\n",better_opt_cout[STATIC-1],better_opt_cout[DYNAMIC-1],better_opt_cout[GUIDED-1],better_opt_cout[RUNTIME-1]);

    return 0;

}