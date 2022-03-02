#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <cmath>

#include <omp.h>
#include <iostream>
#include <time.h>


#define MAX_CHUNK_SIZE 20
#define CHUNK_STEP 4

#define MATRIX_SIZE 200
#define MATRIX_STEP 20

static int matrix_size_barrier = 0;
static bool matrix_value_barrier_set = false;

using namespace std;

double Mult_Matrix_Vector(int** matr, int* vec, int n, int* res) {
	res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime(); 

	for (int i = 0; i < n; i++)
	{
		res[i] = 0;
		for (int j = 0; j < n; j++)
			res[i] += matr[i][j] * vec[j];
	}
    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Static(int** matr, int* vec, int n, int* res, size_t chunk_size) {
	res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime(); 

#pragma omp parallel for schedule(static,chunk_size)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }
    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Dynamic(int** matr, int* vec, int n, int* res, size_t chunk_size) {
	res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime(); 

#pragma omp parallel for schedule(static,chunk_size)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }
    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Guided(int** matr, int* vec, int n, int* res, size_t chunk_size) {
	res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime(); 

#pragma omp parallel for schedule(static,chunk_size)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }
    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Runtime(int** matr, int* vec, int n, int* res, size_t chunk_size) {
	res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime(); 

#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }

    end_time = omp_get_wtime();                                                                            
    return end_time - start_time;
}

#define TOSTR(x) (#x)

enum option{
    NULLOPT=-1,
    STATIC=1,
    DYNAMIC=2,
    GUIDED=3,
    RUNTIME=4,
    NONPARALLEL=5
};

#define BETTER_TIME INT_MAX

double check_better_time(double &bettertime, double time, option &betteroption, option opt){
    if (bettertime > time)
    {
        bettertime = time;
        betteroption = opt;
    }
    return time;
}


//#define NUM_OF_THREAD;


void get_better_opt(int n)
{

    int** matr = new int*[n];
    for (int i = 0; i < n; i++)
        matr[i] = new int[n];

    int* vec = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matr[i][j] = rand() % 10 - 5;
    for (int i = 0; i < n; i++)
        vec[i] = rand() % 10 - 5;

    int* res = new int[n];

    size_t better_opt_cout[5] = {0, 0, 0, 0, 0}; //5 nonparallel

    for (size_t chunk_size = 0; chunk_size < MAX_CHUNK_SIZE; chunk_size += CHUNK_STEP)
    {
        double time_non_parallel = 0.0;
        double better_time = (double)BETTER_TIME;
        option better_opt = NULLOPT;

        printf("\tOption %s, time: %.4f msec\n", TOSTR(STATIC),1000 * check_better_time(better_time, 
                                                                                        Mult_Matrix_Vector_Parallel_Static(matr,vec,n,res,chunk_size), better_opt, STATIC));
        printf("\tOption %s, time: %.4f msec\n", TOSTR(DYNAMIC),1000 * check_better_time(better_time, 
                                                                                        Mult_Matrix_Vector_Parallel_Dynamic(matr,vec,n,res,chunk_size), better_opt, DYNAMIC));
        printf("\tOption %s, time: %.4f msec\n", TOSTR(GUIDED),1000 * check_better_time(better_time, 
                                                                                        Mult_Matrix_Vector_Parallel_Guided(matr,vec,n,res,chunk_size), better_opt, GUIDED));
        printf("\tOption %s, time: %.4f msec\n", TOSTR(RUNTIME),1000 * check_better_time(better_time, 
                                                                                        Mult_Matrix_Vector_Parallel_Runtime(matr,vec,n,res,chunk_size), better_opt, RUNTIME));

        time_non_parallel =  Mult_Matrix_Vector_Parallel_Runtime(matr,vec,n,res,chunk_size);
        printf("\tOption %s, time: %.4f msec\n", TOSTR(NONPARALLEL),1000 * check_better_time(better_time, time_non_parallel, better_opt, NONPARALLEL));         \

                                                                         
        printf("BETTER OPTION %d, BETTER TIME %.4f msec, CHUNK_SIZE = %d\n\n", better_opt, 1000 * better_time, chunk_size);

        if(better_opt != NONPARALLEL && !matrix_value_barrier_set)
        {
            matrix_size_barrier = n;
            matrix_value_barrier_set = true;
        }

        better_opt_cout[better_opt-1] ++;
    }
    printf("BETTER Options count:\nSTATIC: %d\nDYNAMIC: %d\nGUIDED: %d\nRUNTIME: %d\nNONPARALLEL: %d\n",
                                            better_opt_cout[STATIC-1],better_opt_cout[DYNAMIC-1],better_opt_cout[GUIDED-1],better_opt_cout[RUNTIME-1], better_opt_cout[NONPARALLEL-1]);

    
    printf("MATRIX SIZE: %d\n", n);
    printf("MATRIX VALUE BARRIER: %d\n", matrix_size_barrier);
    delete[]res;
    delete[]vec;
    for (int i = 0; i < n; i++)
        delete[] matr[i];
    delete[]matr;
    return;
}



int main() 
{
	srand(time(0));
    omp_set_num_threads(8);

    for (int matrix_size = MATRIX_STEP; matrix_size < MATRIX_SIZE; matrix_size += MATRIX_STEP) { get_better_opt(matrix_size); }


    return 0;

}