#include "matrix.h"

Matrix *matrix_init(int rows, int columns, Matrix *mat)
{
    mat = (Matrix *)malloc(sizeof(Matrix));
    mat->number_of_rows = rows;
    mat->number_of_columns = columns;
    mat->data = malloc(rows*sizeof(double *));
    for(int i = 0; i < rows; i++){
        mat->data[i] = calloc(columns, sizeof(double));
    }
    // mat->data = calloc(rows*columns, sizeof(double));
    return mat;
}

void matrix_edit(Matrix *mat, double *data)
{
    for(int i = 0; i < mat->number_of_rows; i++){
        for(int j = 0; j < mat->number_of_columns; j++){
            mat->data[i][j] = data[i * mat->number_of_columns + j];
        }
    }
}

void matrix_copy(Matrix *mat, Matrix *mat2)
{
    for(int i = 0; i < mat->number_of_rows; i++){
        for(int j = 0; j < mat->number_of_columns; j++){
            mat2->data[i][j] = mat->data[i][j];
        }
    }
}

Matrix *matrix_dup(Matrix *mat, Matrix *mat2){
    mat2 = matrix_init(mat->number_of_rows, mat->number_of_columns, mat2);
        for(int i = 0; i < mat->number_of_rows; i++){
            for(int j = 0; j < mat->number_of_columns; j++){
                mat2->data[i][j] = mat->data[i][j];
            }
    }
    return mat2;
}

void matrix_del(Matrix *mat)
{
    mat->number_of_rows = 0;
    mat->number_of_columns = 0;
    free(mat->data);
    free(mat);
}

void matrix_print(Matrix *mat, int precision)
{
    if(!mat){
        printf("Matrix is NULL");
        return -1;
    }
    
    printf("[\n");
    for(int i = 0; i < mat->number_of_rows; i++){
        printf("\t[ ");
        for(int j = 0; j < mat->number_of_columns; j++){
            printf("%.*lf ", precision, mat->data[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}

int size_check(Matrix *mat1, Matrix *mat2)
{
    // Matrices are the same size
    if(mat1->number_of_rows == mat2->number_of_rows && mat1->number_of_columns == mat2->number_of_columns){
        return SAME_SIZE;
    }
    // Matricies are m x n and n x m
    if(mat1->number_of_rows == mat2->number_of_columns && mat1->number_of_columns == mat2->number_of_rows){
        return SWAPPED_SIZE;
    }
    return 0;
}

void matrix_scale(Matrix *mat, double scalar)
{
    for(int i = 0; i < mat->number_of_rows; i++){
        for(int j = 0; j < mat->number_of_columns; j++){
            mat->data[i][j] = mat->data[i][j]*scalar;
        }
    }
}

Matrix *add_matrices(Matrix *output, Matrix *mat1, Matrix *mat2)
{
    if(size_check(mat1, mat2) != SAME_SIZE){
        return NULL;
    }

    output = matrix_init(mat1->number_of_rows, mat1->number_of_columns, output);

    for(int i = 0; i < mat1->number_of_rows; i++){
        for(int j = 0; j < mat1->number_of_columns; j++){
            output->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }

    return output;
}

Matrix *multiply_matrices(Matrix *mat1, Matrix *mat2, Matrix *output)
{
    if(!size_check(mat1, mat2)){
        return NULL;
    }

    output = matrix_init(mat1->number_of_rows, mat2->number_of_columns, output);

    for(int i = 0; i < mat1->number_of_rows; i++){
        for(int j = 0; j < mat2->number_of_columns; j++){
            int sum = 0;
            for(int k = 0; k < mat1->number_of_columns; k++){
                sum += mat1->data[i][k] * mat2->data[k][j];
            }
            output->data[i][j] = sum;
        }
    }
    
    return output;
}

Matrix *matrix_pow(Matrix *mat, int exponent, Matrix *output){

}

Matrix *transpose(Matrix *mat, Matrix *output){

}
