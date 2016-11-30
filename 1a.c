// revised thread program c[i]=a[i]+b[i] and d[i]=a[i]-b[i]
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define n 15
int main (int argc, char *argv[])
{
	int i, nthreads, tid;
	int a[100], b[100], c[100], d[100];
	for (i = 0; i < n; i++)
	{
		a[i] = i * 3;
		b[i] = i * 2;
	}
	for (i = 0; i < n; i++) c[i] = d[i] = 0;
	#pragma omp parallel shared (a,b,c,d,nthreads) private(i,tid)
	{
		tid = omp_get_thread_num();
		if (tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
		printf("Thread %d starting...\n", tid);
		#pragma omp sections
		{
			#pragma omp section
			{
				printf("Thread %d doing section 1\n", tid);
				for (i = 0; i < n; i++)
				{
					c[i] = a[i] + b[i];
					printf("Thread %d: c[%d]= %d\n", tid, i, c[i]);
				}
			}
			#pragma omp section
			{
				printf("Thread %d doing section 2\n", tid);
				for (i = 0; i < n; i++)
				{
					d[i] = a[i] - b[i];
					printf("Thread %d: d[%d]= %d\n", tid, i, d[i]);
				}
			}
		} /* end of sections */
		printf("Thread %d done.\n", tid);
	} /* end of parallel section */
}