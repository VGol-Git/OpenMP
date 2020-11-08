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

		//____________________________________________________________________2sections
		int total = 0;
		double time2 = omp_get_wtime();
#pragma omp parallel sections reduction(+: total) private(i)
		{
#pragma omp section 
			{
				for (i = 0; i < N; i++)
				{
					if (!(A[i] % 2))
					{
						total += (B[i] + C[i]);
					}
				}
			}
#pragma omp section
			{
				for (i = 0; i < N; i++)
					if ((A[i] % 2) && (!(A[i] == 1 || B[i] == 1)))
					{
						total += (B[i] - A[i]);
					}
			}
		}
		time2 = omp_get_wtime() - time2;
		printf("total with 2 sections :%d\n", total);
		printf("time  with 2 sections :%f\n", time2);


		//____________________________________________________________________4sections
		total = 0;
		double time4 = omp_get_wtime();
#pragma omp parallel sections reduction(+: total)  private(i)
		{
#pragma omp section 
			{
				for (i = 0; i < N/2; i++)
				{
					if (!(A[i] % 2))
					{
						total += (B[i] + C[i]);
					}
				}
			}
#pragma omp section 
			{
				for (i = N/2; i < N; i++)
				{
					if (!(A[i] % 2))
					{
						total += (B[i] + C[i]);
					}
				}
			}
#pragma omp section
			{
				for (i = 0; i < N/2; i++)
					if ((A[i] % 2) && (!(A[i] == 1 || B[i] == 1)))
					{
						total += (B[i] - A[i]);
					}
			}
#pragma omp section
			{
				for (i = N/2; i < N; i++)
					if ((A[i] % 2) && (!(A[i] == 1 || B[i] == 1)))
					{
						total += (B[i] - A[i]);
					}
			}
		}
		time4 = omp_get_wtime() - time4;
		printf("total with 4 sections :%d\n", total);
		printf("time  with 4 sections :%f\n", time4);

		//____________________________________________________________________8sections
		total = 0;
		double time8 = omp_get_wtime();
#pragma omp parallel sections reduction(+: total)  private(i)
		{
#pragma omp section 
			{
				for (i = 0; i < N / 4; i++)
				{
					if (!(A[i] % 2))
					{
						total += (B[i] + C[i]);
					}
				}
			}
#pragma omp section 
			{
				for (i = N / 4; i < N/2; i++)
				{
					if (!(A[i] % 2))
					{
						total += (B[i] + C[i]);
					}
				}
			}
#pragma omp section 
			{
				for (i = N / 2; i < N*3/4; i++)
				{
					if (!(A[i] % 2))
					{
						total += (B[i] + C[i]);
					}
				}
			}
#pragma omp section 
			{
				for (i = N * 3 / 4; i < N; i++)
				{
					if (!(A[i] % 2))
					{
						total += (B[i] + C[i]);
					}
				}
			}
#pragma omp section
			{
				for (i = 0; i < N / 4; i++)
					if ((A[i] % 2) && (!(A[i] == 1 || B[i] == 1)))
					{
						total += (B[i] - A[i]);
					}
			}
#pragma omp section
			{
				for (i = N / 4; i < N/2; i++)
					if ((A[i] % 2) && (!(A[i] == 1 || B[i] == 1)))
					{
						total += (B[i] - A[i]);
					}
			}
#pragma omp section
			{
				for (i = N / 2; i < N * 3 / 4; i++)
					if ((A[i] % 2) && (!(A[i] == 1 || B[i] == 1)))
					{
						total += (B[i] - A[i]);
					}
			}
#pragma omp section
			{
				for (i = N * 3 / 4; i < N; i++)
					if ((A[i] % 2) && (!(A[i] == 1 || B[i] == 1)))
					{
						total += (B[i] - A[i]);
					}
			}
		}
		time8 = omp_get_wtime() - time8;
		printf("total with 8 sections :%d\n", total);
		printf("time  with 8 sections :%f\n", time8);

		//____________________________________________________________________ the_correct_result
		int the_correct_result = 0;
		double time = omp_get_wtime();
		for (i = 0; i < N; i++)
		{
			if (!(A[i] % 2))
			{
				the_correct_result += (B[i] + C[i]);
			}
			else (A[i] == 1 || B[i] == 1) ? 0 : the_correct_result += (B[i] - A[i]);
		}
		time = omp_get_wtime() - time;
		printf("the_correct_result without parralel sections :%d\n", the_correct_result);	// показывает, что правильный ответ total1
		printf("time  :%f\n", time);
		printf("__________________________\n");

		N /= 100;
		count++;
	} while (count <4);
	
		delete[] A;
		delete[] B;
		delete[] C;

	return 0;
}
