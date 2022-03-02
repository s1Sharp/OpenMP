#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <ctime>

using namespace std;

//#define NUM_OF_THREAD;
int main() {

	srand(time(0));
	int a[10], b[10];

	for (int i = 0; i < 10; ++i)
	{
		a[i] = rand() % 100 + 1;
		b[i] = rand() % 100 + 1;
	}
	omp_set_num_threads(2);

#pragma omp parallel 
	{
		int cur_thr_num = omp_get_thread_num();
		
		if (cur_thr_num == 0)
		{
			int min = a[0];
			for (int i = 1; i < 10; ++i)
			{
				if (a[i] < min)
					min = a[i];
			}
			printf("parallel area number %d\n", cur_thr_num);
			printf("min a =%d \n", min);
		}
		if (cur_thr_num == 1)
		{
			int max = a[0];
			for (int i = 1; i < 10; ++i)
			{
				if (a[i] > max)
					max = a[i];
			}
			printf("parallel area number %d\n", cur_thr_num);
			printf("max b =%d \n", max);
		}

		if (cur_thr_num != 0 && cur_thr_num != 1)
			cout << endl << "ti chto, s yma sochel, skazano 2 potoka" << endl;
	}

}