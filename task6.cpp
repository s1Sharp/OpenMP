#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <ctime>

using namespace std;

//#define NUM_OF_THREAD;
int main() {

	srand(time(0));
	int a[100];

	for (int i = 0; i < 100; ++i)
	{
		a[i] = rand() % 100 + 1;
	}
	
	double meanSA = 0;
#pragma omp parallel for reduction(+:meanSA)
    for (int i = 0; i < 100; i++) {
        meanSA += a[i];
    }

    meanSA /= 10;
    printf("mead of a = %.2lf\n",meanSA);


//without reduction we writing into meanSA, without atomic operation. Threads might rewrite value, which changed in orher thread. it`s dangerous operation.
//reduction save operation, because operator(+) will be execute atfer for directive.
    meanSA = 0;
#pragma omp parallel for 
    for (int i = 0; i < 100; i++) {
        meanSA += a[i];
    }

    meanSA /= 10;
    printf("mead of a = %.2lf\n",meanSA);


  return 0;
}