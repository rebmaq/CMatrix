#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


typedef struct matrix
{
    int number_of_rows;
    int number_of_columns;
    double **data;
} Matrix;

const int SAME_SIZE = 1;
const int SWAPPED_SIZE = 2;

/**
 * @brief Creates a Matrix and allocates memory for the Matrix
 * 
 * @param rows number of rows of the Matrix
 * @param columns number of columns of the Matrix
 * @param mat a pointer to the Matrix
 * @return Matrix* the pointer to a newly allocated Matrix struct
 */
Matrix *matrix_init(int rows, int columns, Matrix *mat);

/**
 * @brief Updates all of the cells of the Matrix *mat
 * 
 * @param mat A pointer to the Matrix that will be updated
 * @param data A pointer to a list of numbers that will be added to the Matrix
 */
void matrix_edit(Matrix *mat, double *data);

/**
 * @brief Copies the data from one Matrix to another
 * 
 * @param mat the Matrix to copy from
 * @param mat2 the Matrix to copy to
 */
void matrix_copy(Matrix *mat, Matrix *mat2);

/**
 * @brief Duplicates a Matrix
 * 
 * @param mat the Matrix to be duplicated
 * @param mat2 the pointer to the Matrix that will be instantiated 
 * @return Matrix* an instantiated duplicate Matrix
 */
Matrix *matrix_dup(Matrix *mat, Matrix *mat2);

/**
 * @brief Deletes and frees all related memory
 * 
 * @param mat the Matrix to be freed
 */
void matrix_del(Matrix *mat);

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
 * @return int SAME_SIZE if they are the same size, SWAPPED_SIZE if they mat1 is m by n and mat2 is n by m, 0 otherwise
 */
int size_check(Matrix *mat1, Matrix *mat2);

/**
 * @brief Scales a matrix by a given scalar
 * 
 * @param mat a pointer to a Matrix
 * @param scalar the number by which the Matrix should be scaled 
 */
void matrix_scale(Matrix *mat, double scalar);

/**
 * @brief Adds two Matrices
 * 
 * @param mat1 an n by m Matrix to be added
 * @param mat2 a n by m Matrix to be added
 * @param output an uninitialized pointer to a Matrix 
 * @return Matrix* the sum of mat1 and mat2
 */
Matrix *add_matrices(Matrix *mat1, Matrix *mat2, Matrix *output);

/**
 * @brief Multiplies two Matrices
 * 
 * @param mat1 an n by m Matrix
 * @param mat2 an m by p Matrix
 * @param output an uninitialized pointer to a Matrix 
 * @return Matrix* an n by p Matrix with the product of mat1 and mat2
 */
Matrix *multiply_matrices(Matrix *mat1, Matrix *mat2, Matrix *output);

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

Matrix *get_submatrix(Matrix *mat, Matrix *output);
 
#endif