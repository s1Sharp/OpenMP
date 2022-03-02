#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <ctime>

using namespace std;

//#define NUM_OF_THREAD;
int main() {

	srand((uint64_t)time(0));
	int mas[6][8];

	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 8; ++j)
		{
			mas[i][j] = rand() % 100 + 1;
		}


#pragma omp parallel sections
	{
#pragma omp section
		{
			int sum = 0, k = 0;
			for (int i = 0; i < 6; ++i)
				for (int j = 0; j < 8; ++j)
				{
					sum += mas[i][j]; 
					k++;
				}
			printf("thread num = %d, mean = %.2lf\n", omp_get_thread_num(), float(sum) / k); 	
		}
#pragma omp section
		{
			int max = mas[0][0], min = mas[0][0];
			for (int i = 0; i < 6; ++i)
				for (int j = 0; j < 8; ++j)
				{
					if (mas[i][j] > max)
					{
						max = mas[i][j];
					}
					if (mas[i][j] < min)
					{
						min = mas[i][j];
					}
				}
            printf("thread num = %d, min = %d, max = %d\n", omp_get_thread_num(), min, max); 
		}
#pragma omp section
		{
			int count = 0;
			for (int i = 0; i < 6; ++i)
				for (int j = 0; j < 8; ++j)
				{
					if (mas[i][j] % 3 == 0)
						count++;
				}
            printf("thread num = %d, count = %d\n", omp_get_thread_num(), count); 
		}
	}
}
