#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {

	const int n = 999;

	int m[n];
	srand(time(NULL));
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		{
			m[i] = rand() % 1000;
			printf("%d ", m[i]);
		}
		if (k == 10)
		{
			printf("\n"); k = 0;
		}
		else
			k++;
	}
	printf("\n");


	int local_max = -1;
	int max = m[0];
	omp_set_num_threads(4);
#pragma omp parallel private(local_max) shared(max)
	{
		local_max = -1;
#pragma omp parallel for 
		for (int i = 0; i < n; ++i)
		{
			if (m[i] % 7 == 0 && max < m[i])
			{
				local_max = m[i];
			}
		}

#pragma omp critical
		{
			if (max < local_max)
			{
				max = local_max;
				printf("max reset on %d value, thread area %d, count of threads %d\n", max, omp_get_thread_num(), omp_get_num_threads());
			}
		}
	}

    printf("Max element which multiples of 7 = %d", max);

    return 0;
}