//
// Created by jefferson on 21/09/16.
//

#include "UniformRandomInt.h"
#include <stdlib.h>



UniformRandomInt::UniformRandomInt(int a, int b) :
        a(a), b(b)
{
}

thrust::device_vector<double> UniformRandomInt::generate(int n) {
    thrust::device_vector<double> result(static_cast<unsigned long>(n));
    thrust::counting_iterator<unsigned int> index_sequence_begin(0);

    thrust::transform(index_sequence_begin,
                      index_sequence_begin + n,
                      result.begin(),
                      prg_int(static_cast<unsigned int>(rand()), a, b));

    return result;
}

void UniformRandomInt::test() {
    // Size of vectors
    int n = 10000;

    // Input vectors
    double *__restrict__ a;
    double *__restrict__ b;
    // Output vector
    double *__restrict__ c;

    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(double);

    // Allocate memory for each vector
    a = (double*)malloc(bytes);
    b = (double*)malloc(bytes);
    c = (double*)malloc(bytes);

    // Initialize content of input vectors, vector a[i] = sin(i)^2 vector b[i] = cos(i)^2
    int i;
    for(i=0; i<n; i++) {
        a[i] = sin(i)*sin(i);
        b[i] = cos(i)*cos(i);
    }

    // sum component wise and save result into vector c
    #pragma acc kernels copyin(a[0:n],b[0:n]), copyout(c[0:n])
    for(i=0; i<n; i++) {
        c[i] = a[i] + b[i];
    }

    // Sum up vector c and print result divided by n, this should equal 1 within error
    double sum = 0.0;
    for(i=0; i<n; i++) {
        sum += c[i];
    }
    sum = sum/n;
    printf("final result: %f\n", sum);

    // Release memory
    free(a);
    free(b);
    free(c);
}
