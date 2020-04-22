/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/* define MACROS for the cases of multiplication function */
#define SQUARE 1
#define U_NORMAL 2
#define N_LOWER 3

/*
 * Add your unoptimized implementation here
 */

/* return a multiplication of 2 specified matrices in a case */
double *matrix_multiplication(double *a, double *b, int N, int mul_case)
{

	double *result;
	int i, j, k;

	result = (double *)malloc(sizeof(double) * N * N);

	if (result == NULL) {
		printf("Memory allocation error in matrix_multipl\n");
		return NULL;
	}

	if (mul_case == SQUARE) {
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				double sum = 0;

				for (k = 0; k < N; k++) {
					if (i <= j)
						sum += a[i * N + k] * b[k * N + j];
				}

				result[i * N + j] = sum;
			}
		}
	} else if (mul_case == U_NORMAL) {
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				double sum = 0;

				for (k = i; k < N; k++)
					sum += a[i * N + k] * b[k * N + j];

				result[i * N + j] = sum;
			}
		}
	} else {
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				double sum = 0;

				for (k = j; k < N; k++)
					sum += a[i * N + k] * b[k * N + j];

				result[i * N + j] = sum;
			}
		}
	}

	return result;
}

/* return a transpose matrix */
double *trans(double *a, int N)
{

	double *res;
	int i, j;

	res = (double *)malloc(sizeof(double) * N * N);

	if (res == NULL) {
		printf("Memory allocation error in transpose\n");
		return NULL;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			res[j * N + i] = a[i * N + j];
	}

	return res;
}

double *my_solver(int N, double *A, double *B)
{

	double *a_2, *a_2b, *bat, *transpose;
	int i, j;

	a_2 = (double *)malloc(sizeof(double) * N * N);
	a_2b = (double *)malloc(sizeof(double) * N * N);
	bat = (double *)malloc(sizeof(double) * N * N);
	transpose = (double *)malloc(sizeof(double) * N * N);

	if (!a_2 || !a_2b || !bat || !transpose) {
		printf("Memory allocation error in main\n");
		return NULL;
	}

	/* do the operation */
	a_2 = matrix_multiplication(A, A, N, SQUARE);
	a_2b = matrix_multiplication(a_2, B, N, U_NORMAL);
	transpose = trans(A, N);
	bat = matrix_multiplication(B, transpose, N, N_LOWER);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			bat[i * N + j] += a_2b[i * N + j];
	}

	free(a_2);
	free(a_2b);
	free(transpose);

	return bat;
}
