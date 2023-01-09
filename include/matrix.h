#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../lib/cache_line_size.h"

typedef struct matrix
{
    int number_of_rows;
    int number_of_columns;
    double **data;
} Matrix;

enum {SAME_SIZE = 1, SWAPPED_SIZE = 2};

long get_cache_line_size();

/**
 * @brief Creates a Matrix and allocates memory for the Matrix
 * 
 * @param rows number of rows of the Matrix
 * @param columns number of columns of the Matrix
 * @return Matrix* the pointer to a newly allocated Matrix struct
 */
Matrix *matrix_init(int rows, int columns);

/**
 * @brief Creates a Matrix with all zeros
 *
 * @param rows number of rows of the Matrix
 * @param columns number of columns of the Matrix
 * @return Matrix* the pointer to a newly allocated Matrix struct
 */
Matrix* matrix_zeros(int rows, int columns);

/**
 * @brief Updates all of the cells of the Matrix *mat
 * 
 * @param mat A pointer to the Matrix that will be updated
 * @param data A pointer to a list of numbers that will be added to the Matrix
 * @return int 0 on success, -1 on error.
 */
int matrix_edit(Matrix *mat, double *data);

/**
 * @brief Copies the data from one Matrix to another
 * 
 * @param mat the Matrix to copy from
 * @param mat2 the Matrix to copy to
 * @return int 0 on success, -1 on error.
 */
int matrix_copy(Matrix *mat, Matrix *mat2);

/**
 * @brief Duplicates a Matrix
 * 
 * @param mat the Matrix to be duplicated
 * @return Matrix* an instantiated duplicate Matrix
 */
Matrix *matrix_dup(Matrix *mat);

/**
 * @brief Deletes and frees all related memory
 * 
 * @param mat the Matrix to be freed
 * @return int 0 on success, -1 on error
 */
int matrix_del(Matrix *mat);

/**
 * @brief Prints the values in a matrix
 * 
 * @param mat the Matrix to be printed 
 * @param precision the number of decimal places to print
 */
void matrix_print(Matrix *mat, int precision);

/**
 * @brief Checks if the sizes of two matrices are compatible
 * 
 * @param mat1 a pointer to a Matrix
 * @param mat2 a pointer to the Matrix to compare
 * @return int SAME_SIZE if they are the same size, SWAPPED_SIZE if they mat1 is m by n and mat2 is n by m, 
 *   0 otherwise, and -1 on error
 */
int size_check(Matrix *mat1, Matrix *mat2);

/**
 * @brief Gets the identity Matrix
 * 
 * @param n the dimension of the row/column of the identity Matrix
 * @param mat an uninitialized pointer to a Matrix
 * @return Matrix* an n x n identity Matrix
 */
Matrix *get_identity(int n, Matrix* mat);

/**
 * @brief Scales a matrix by a given scalar
 * 
 * @param mat a pointer to a Matrix
 * @param scale the number by which the Matrix should be scaled 
 * @return int 0 on success, -1 on error
 */
int scale_matrix(Matrix *mat, double scale);

/**
 * @brief Adds two Matrices
 * 
 * @param mat1 an n by m Matrix to be added
 * @param mat2 a n by m Matrix to be added
 * @param output n by m destination matrix 
 * @return int 0 on success, -1 on error
 */
int add_matrices(Matrix *mat1, Matrix *mat2, Matrix *output);

/**
 * @brief Subtracts two Matrices
 * 
 * @param mat1 an n by m Matrix from which to subtrct
 * @param mat2 a n by m Matrix to subtract
 * @param output n by m destination matrix 
 * @return int 0 on success, -1 on error
 */
int subtract_matrices(Matrix *mat1, Matrix *mat2, Matrix *output);

/**
 * @brief Multiplies two Matrices
 * 
 * @param mat1 an n by m Matrix
 * @param mat2 an m by p Matrix
 * @param output n by p destination matrix
 * @return int 0 on success, -1 on error
 */
int multiply_matrices(Matrix *mat1, Matrix *mat2, Matrix *output);

/**
 * @brief Raises a Matrix to a power
 * 
 * @param mat a pointer to a Matrix
 * @param exponent the number to which to raise the Matrix
 * @param output an uninitialized pointer to a Matrix
 * @return Matrix* the resulting Matrix
 */
Matrix *matrix_pow(Matrix *mat, int exponent, Matrix *output);


/**
 * @brief Transposes a Matrix
 * 
 * @param mat a pointer to a Matrix
 * @param output an unitialized pointer to a Matrix
 * @return Matrix* the resulting Matrix
 */
Matrix *transpose(Matrix *mat, Matrix *output);

/**
 * @brief Get a submatrix from a Matrix
 * 
 * @param mat a pointer to a Matrix
 * @param row_indices the indices of the rows which should not be included in the submatrix
 * @param column_indices the indices of the columns which should not be included in the submatrix
 * @param output an uninitialized pointer to a Matrix
 * @return Matrix* the submatrix
 */
Matrix *get_submatrix(Matrix *mat, int row_indices, int column_indices, Matrix *output);

double get_determinant(Matrix *mat);

double get_trace(Matrix *mat);

Matrix *get_inverse(Matrix *mat);

void LU_decomposition(Matrix *mat, Matrix *L, Matrix *U);

void QR_decomposition(Matrix *mat, Matrix *Q, Matrix *R);

void SV_decomposition(Matrix *mat, Matrix *U, Matrix *SIG, Matrix *V);

void eigenvalue_decomposition(Matrix *mat, Matrix *X, Matrix *LAM, Matrix *X_inv);


#endif