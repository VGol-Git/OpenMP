#include <iostream>
#include <omp.h>
#include <ctime>

int N = 1e8;

int main() {

	srand(time(0));
	int i;
	int count = 1;
	int* A = new int[N];
	int* B = new int[N];
	int* C = new int[N];
#pragma omp parallel shared(A , B , C) private(i) 
	{
#pragma omp for 
		for (i = 0; i < N; i++)
		{
			A[i] = 1 + abs(rand() % 10);
			B[i] = 1 + abs(rand() % 10);
			C[i] = 1 + abs(rand() % 10);
		}
	}

	do
	{
		printf(" Size of arrays : %d:\n\n", N);
		int total = 0;
		double time = omp_get_wtime();
#pragma omp parallel shared(A , B , C) private(i) 
		{
			#pragma omp master
				printf("master: Hey, Smile for the barrier! \n");
			#pragma omp barrier
			#pragma omp for reduction ( +: total)
				for (i = 0; i < N; i++)
				{
					if (!(A[i] % 2))
					{
							total += (B[i] + C[i]);
					}
					else if (!(A[i] == 1 || B[i] == 1)) {
							total += (B[i] - A[i]);
					}
				}
		}
		time = omp_get_wtime() - time;
		printf("result with barrier :%d\n", total);
		printf("time :%f\n", time);

		int the_correct_result = 0;
		time = omp_get_wtime();
		for (i = 0; i < N; i++)
		{
			if (!(A[i] % 2))
			{
				the_correct_result += (B[i] + C[i]);
			}
			else (A[i] == 1 || B[i] == 1) ? 0 : the_correct_result += (B[i] - A[i]);
		}
		time = omp_get_wtime() - time;
		printf("the_correct_result :%d\n", the_correct_result);
		printf("time  :%f\n", time);
		printf("__________________________\n");

		N /= 100;
		count++;
	} while (count < 4);

	delete[] A;
	delete[] B;
	delete[] C;


	return 0;
}

