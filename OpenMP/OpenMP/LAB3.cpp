#include <iostream>
#include <omp.h>
#include <ctime>

int const N = 1e8;

int main() {

	srand(time(0));

	int i;
	bool key=0;
	printf(" Size of arrays : %d:\n\n", N);
	do
	{
		int total = 0;
		int total2 = 0;
		key ? printf(" Parallel :\n") : printf(" No parallel :\n");
		int* A = new int[N];
		int* B = new int[N];
		int* C = new int[N];

	double time = omp_get_wtime();
#pragma omp parallel shared(A , B , C) private(i) if(key)
	{
#pragma omp for 
		for (i = 0; i < N; i++)
		{

			A[i] = 1 + abs(rand() % 10);
			B[i] = 1 + abs(rand() % 10);
			C[i] = 1 + abs(rand() % 10);
		}
#pragma omp for reduction (+:total)
		for (i = 0; i < N; i++)
		{
			if (!(A[i] % 2))
			{
				total += (B[i] + C[i]);

			}
			 
			else (A[i] == 1 || B[i] == 1) ? 0 : total += (B[i] - A[i]);
		}

#pragma omp for 
		for (i = 0; i < N; i++)
		{
			if (!(A[i] % 2))
			{
				total2 += (B[i] + C[i]);

			}
			else (A[i] == 1 || B[i] == 1) ? 0 : total2 += (B[i] - A[i]);
		}

	}
		time = omp_get_wtime() - time;
		printf("with reduction :%d\n", total);	
		printf("without reduction %d\n", total2); //из-за состояния гонки процессов total2 и total1 могут отличаться при распараллеливании
		printf("time :%f\n", time);

	int the_correct_result = 0;
	for (i = 0; i < N; i++)
	{
		if (!(A[i] % 2))
		{
			the_correct_result += (B[i] + C[i]);

		}
		else (A[i] == 1 || B[i] == 1) ? 0 : the_correct_result += (B[i] - A[i]);
	}
		printf("the_correct_result :%d\n", the_correct_result);	// показывает, что правильный ответ total1
		printf("__________________________\n", time);
		delete[] A;
		delete[] B;
		delete[] C;
		key = !key;

	} while (key);


	return 0;
}






