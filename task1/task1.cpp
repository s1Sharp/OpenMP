#include <iostream>
#include <omp.h>
int main()
{
#ifdef _OPENMP
	std::cout << "Hello, OpenMP!" << std::endl;
#else
	std::cout << "OpenMP is not enabled." << std::endl;
#endif
	return 0;
}
