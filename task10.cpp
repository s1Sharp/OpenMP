#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

	const int w = 6;
	const int h = 8;

	int d[w][h];
	srand(time(NULL));

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			d[i][j] = rand() % 90 + 10;
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");

	int min = d[0][0];
	int max = d[0][0];
	int counter = 0;
	int local_min, local_max;
#pragma omp parallel for private(local_max, local_min) shared(max,min) reduction(+:counter)
	for (int i = 0; i < w; ++i)
	{
		local_max = local_min = d[i][0];

		for (int j = 0; j < h; ++j)
		{
			++counter;
			if (d[i][j] > local_max) local_max = d[i][j];
			else if (d[i][j] < local_min) local_min = d[i][j];
		}
#pragma omp critical
		{
			if (local_max > max) max = local_max;
			else if (local_min < min) min = local_min;
		}

	}
	printf("counter is %d\n", counter);
	printf("max is %d, min is %d\n", max, min);

}