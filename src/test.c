#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "matrix.h"
#include "image.h"
#include "test.h"
#include "args.h"

double what_time_is_it_now()
{
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void test_matrix_speed()
{
    int i;
    int n = 128;
    matrix a = random_matrix(512, 512, 1);
    matrix b = random_matrix(512, 512, 1);
    double start = what_time_is_it_now();
    for(i = 0; i < n; ++i){
        matrix d = matmul(a,b);
        free_matrix(d);
    }
    printf("Matmul elapsed %lf sec\n", what_time_is_it_now() - start);
    start = what_time_is_it_now();
    for(i = 0; i < n; ++i){
        matrix at = transpose_matrix(a);
        free_matrix(at);
    }
    printf("Transpose elapsed %lf sec\n", what_time_is_it_now() - start);
}

void test_matmul() {
    matrix matrix_a = make_matrix(2, 2);
    matrix matrix_b = make_matrix(2, 2);
    float a_data[] = {
        1, 0,
        0, 1,
    };
    float b_data[] = {
        0, 0,  
        1, 1
    };

    float c_expected_data[] = {
        0, 0,  
        1, 1,
    };

    matrix_a.data = a_data;
    matrix_b.data = b_data;
    matrix matrix_c = matmul(matrix_a, matrix_b);
    for (int i = 0; i < matrix_c.cols * matrix_c.rows; i++) {
        assert(matrix_c.data[i] - c_expected_data[i] < 0.001 && matrix_c.data[i] - c_expected_data[i] > -0.001);
    }
}

void run_tests()
{
    test_matrix_speed();
    test_matmul();
    //printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}

