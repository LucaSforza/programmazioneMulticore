#include <stdio.h>
#include <cuda.h>

__global__ void run(void) {
    printf("Hello World!\n");
}

int main(void) {
    run<<<1,10>>>();
    cudaDeviceSynchronize();
    return 1;
}