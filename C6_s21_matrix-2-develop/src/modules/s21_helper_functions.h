#ifndef S21_HELPER_FUNCTIONS
#define S21_HELPER_FUNCTIONS

#include "../s21_matrix.h"

// The function validates matrix pointers and pointers to the location of the
// matrices themselves in memory
int s21_validate_matrix(int matrix_amount, matrix_t* A, ...);

// The function checks if all passed matrices have the same dimensions
int s21_is_matrix_same_size(int matrix_amount, matrix_t* A, ...);

// Counting the multiplication of two matrices via formula. Be careful, this
// function does not check pointers to matrices.
double s21_mult_matrix_res(int i, int j, matrix_t* A, matrix_t* B);

// Creates a minor matrix for the A[i][j] element. Be careful with this
// function. Can return NULL!
matrix_t* s21_create_minor(int excluded_row, int excluded_column, matrix_t* A);

// The function checks the matrix for squareness
int s21_is_matrix_square(matrix_t* A);

// The function initializes the entire matrix with values ​​​​from the
// given one and each time increasing by an iteration step
void s21_initialize_matrix(matrix_t* A, double start_value,
                           double iteration_step);

// The function prints the entire matrix to the console
void s21_print_matrix(matrix_t* A);

#endif  // S21_HELPER_FUNCTIONS
