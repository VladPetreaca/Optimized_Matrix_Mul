/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	
	double *a = (double *) malloc (sizeof(double) * N * N);
	double *b = (double *) malloc (sizeof(double) * N * N);
	int i,j;

	if (a == NULL || b == NULL) {
		printf("Eroare\n");
		return NULL;
	}

	//copy A in a and B in b
	cblas_dcopy(N * N, A, 1, a, 1);
	cblas_dcopy(N * N, B, 1, b, 1);

	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, a, N);
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, a, N, B, N);
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, b, N);	
	
	for(i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			b[i * N + j] += B[i * N + j]; 
	}

	return b;
}
