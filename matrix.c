#include "matrix.h"

#define eprintf(fmt, ...) \
            do { fprintf(stderr, fmt, __VA_ARGS__); } while (0)

Matrix *matrix_init(int rows, int columns)
{
    Matrix *mat = malloc(sizeof(Matrix));
    if (!mat)
        goto return_null;

    mat->data = malloc(rows * sizeof(double*));
    if (!mat->data)
        goto free_mat;

    mat->data[0] = malloc(rows * columns * sizeof(double));
    if (!mat->data[0])
        goto free_mat_data;

    mat->number_of_rows = rows;
    mat->number_of_columns = columns;
    
    for (int i = 1; i < rows; i++) {
        mat->data[i] = mat->data[i - 1] + columns;
    }

    return mat;
     
    // Error cases
    free_mat_data:
        free(mat->data);

    free_mat:
        free(mat);
    
    return_null:
        eprintf("matrix_init(): could not allocate memory for the matrix\n");
        return NULL;
}

Matrix* matrix_zeros(int rows, int columns)
{
    Matrix* mat = matrix_init(rows, columns);
    if (!mat)
        return NULL;

    for (int i = 0; i < mat->number_of_rows; i++) {
        for (int j = 0; j < mat->number_of_columns; j++) {
            mat->data[i][j] = 0;
        }
    }

    return mat;
}

int matrix_edit(Matrix *mat, double *data)
{
    if (!mat || !data) {
        eprintf("matrix_edit(): either mat or data is NULL\n");
        return -1;
    }

    for (int i = 0; i < mat->number_of_rows; i++) {
        for (int j = 0; j < mat->number_of_columns; j++) {
            mat->data[i][j] = data[i * mat->number_of_columns + j];
        }
    }

    return 0;
}

int matrix_copy(Matrix *mat, Matrix *mat2)
{
    if (!mat || !mat2) {
        eprintf("matrix_copy(): either mat or mat2 is NULL\n");
        return -1;
    }

    if (size_check(mat, mat2) != SAME_SIZE) {
        eprintf("matrix_copy(): size mismatch\n");
        return -1;
    }

    for (int i = 0; i < mat->number_of_rows; i++) {
        for (int j = 0; j < mat->number_of_columns; j++) {
            mat2->data[i][j] = mat->data[i][j];
        }
    }

    return 0;
}

Matrix *matrix_dup(Matrix *mat) 
{
    if (!mat) {
        eprintf("matrix_dup(): mat is NULL\n");
        return NULL;
    }

    Matrix *mat2 = matrix_init(mat->number_of_rows, mat->number_of_columns);
    if (!mat2)
        return NULL;

    for (int i = 0; i < mat->number_of_rows; i++) {
        for (int j = 0; j < mat->number_of_columns; j++) {
            mat2->data[i][j] = mat->data[i][j];
        }
    }
    return mat2;
}

int matrix_del(Matrix *mat)
{
    if (!mat) {
        eprintf("matrix_del(): mat is NULL\n");
        return -1;
    }

    mat->number_of_rows = 0;
    mat->number_of_columns = 0;
    free(mat->data[0]);
    free(mat->data);
    free(mat);

    return 0;
}

void matrix_print(Matrix *mat, int precision)
{
    if (!mat) {
        eprintf("matrix_print(): mat is NULL\n");
        return;
    }
    
    printf("[\n");
    for (int i = 0; i < mat->number_of_rows; i++) {
        printf("\t[ ");
        for (int j = 0; j < mat->number_of_columns; j++) {
            printf("%.*lf ", precision, mat->data[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}

int size_check(Matrix *mat1, Matrix *mat2)
{
    if (!mat1 || !mat2) {
        eprintf("size_check(): either mat1 or mat2 is NULL\n");
        return -1;
    }

    // Matrices are the same size
    if (mat1->number_of_rows == mat2->number_of_rows && mat1->number_of_columns == mat2->number_of_columns) {
        return SAME_SIZE;
    }
    // Matrices are m x n and n x m
    if (mat1->number_of_rows == mat2->number_of_columns && mat1->number_of_columns == mat2->number_of_rows) {
        return SWAPPED_SIZE;
    }
    return 0;
}

int scale_matrix(Matrix *mat, double scale)
{
    if (!mat) {
        eprintf("scale_matrix(): mat is NULL\n");
        return -1;
    }

    for (int i = 0; i < mat->number_of_rows; i++) {
        for (int j = 0; j < mat->number_of_columns; j++) {
            mat->data[i][j] *= scale;
        }
    }

    return 0;
}

int add_matrices(Matrix *mat1, Matrix *mat2, Matrix *output)
{
    if (size_check(mat1, mat2) != SAME_SIZE || size_check(mat2, output) != SAME_SIZE) {
        eprintf("add_matrices(): size mismatch\n");
        return -1;
    }

    for (int i = 0; i < mat1->number_of_rows; i++) {
        for (int j = 0; j < mat1->number_of_columns; j++) {
            output->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }

    return 0;
}

int subtract_matrices(Matrix *mat1, Matrix *mat2, Matrix *output)
{
    if (size_check(mat1, mat2) != SAME_SIZE || size_check(mat2, output) != SAME_SIZE) {
        eprintf("subtract_matrices(): size mismatch\n");
        return -1;
    }

    for (int i = 0; i < mat1->number_of_rows; i++) {
        for (int j = 0; j < mat1->number_of_columns; j++) {
            output->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
        }
    }

    return 0;
}

int multiply_matrices(Matrix* mat1, Matrix* mat2, Matrix* output)
{
    if (!mat1 || !mat2 || !output) {
        eprintf("multiply_matrices(): either mat1, mat2 or output is NULL\n");
        return -1;
    }

    if (mat1->number_of_columns != mat2->number_of_rows ||
        output->number_of_rows != mat1->number_of_rows || output->number_of_columns != mat2->number_of_columns) {
        eprintf("multiply_matrices(): size mismatch\n");
        return -1;
    }

    for (int i = 0; i < mat1->number_of_rows; i++) {
        for (int j = 0; j < mat2->number_of_columns; j++) {
            int sum = 0;
            for (int k = 0; k < mat1->number_of_columns; k++) {
                sum += mat1->data[i][k] * mat2->data[k][j];
            }
            output->data[i][j] = sum;
        }
    }
    
    return 0;
}