#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    double data[4][3] = {
        {1, 2, 1},
        {2, 5, 3},
        {3, 6, 9},
        {1, 4, 6}
    };

    double square[3][4] = {
        {1, 2, 3, 4},
        {2, 3, 5, 7},
        {2, 4, 8, 16},
    };

    double I_2x2d[2][2] = {
        {1, 0},
        {0, 1}
    };

    Matrix *m;
    m = matrix_init(4, 3, m);
    matrix_edit(m, *data);
    matrix_print(m, 2);

    Matrix *I_2x2;
    I_2x2 = matrix_init(2, 2, I_2x2);
    matrix_edit(I_2x2, *I_2x2d);
    Matrix *product;
    Matrix *sq = matrix_init(3, 4, sq);
    matrix_edit(sq, *square);
    product = multiply_matrices(I_2x2, sq, product);
    matrix_print(product, 2);

    

    return 0;
}
