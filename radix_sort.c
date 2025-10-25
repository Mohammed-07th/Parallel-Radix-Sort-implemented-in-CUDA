%%writefile radix_sort.cu
#include <iostream>
#include <cuda_runtime.h>

#define N 16
__device__ void printArray(int* sharedInput, int size, int iteration) {
    printf("Iteration %d: ", iteration);
    for (int i = 0; i < size; i++) {
        printf("%d ", sharedInput[i]);
    }
    printf("\n");
    printf("-------------------------------------------------------------------------");
    printf("\n");
}
__global__ void radixSort(int* input, int* output) {
    __shared__ int sharedInput[N];
    __shared__ int sharedOutput[N];

    int idx = threadIdx.x;
    sharedInput[idx] = input[idx];

    for (int digitPlace = 0; digitPlace < 3; digitPlace++) {
        int countArray[10][N];
        int count[10] = { 0 };

        for (int i = 0; i < N; i++) {
            int digit = (sharedInput[i] / (int)pow(10, digitPlace)) % 10;

            countArray[digit][count[digit]++] = sharedInput[i];
        }

        int outputIndex = 0;
        for (int digit = 0; digit < 10; digit++) {
            for (int i = 0; i < count[digit]; i++) {
                sharedOutput[outputIndex++] = countArray[digit][i];
            }
        }

        for (int i = 0; i < N; i++) {
            sharedInput[i] = sharedOutput[i];
        }
        if (idx == 0) {
            printArray(sharedInput, N, digitPlace + 1);
        }
        __syncthreads();
    }

    output[idx] = sharedInput[idx];
}

int main() {
    int inputArray[N] = { 2, 75, 119, 72, 9, 32, 324, 943, 0, 42, 8, 754, 256, 21, 18, 111 };
    int outputArray[N];

    int *d_inputArray, *d_outputArray;
    int size = N * sizeof(int);

    cudaMalloc(&d_inputArray, size);
    cudaMalloc(&d_outputArray, size);

    cudaMemcpy(d_inputArray, inputArray, size, cudaMemcpyHostToDevice);

    printf("Input array: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", inputArray[i]);
    }

    printf("\n");
    printf("-------------------------------------------------------------------------");
    printf("\n");

    radixSort <<<1, N >>> (d_inputArray, d_outputArray);

    cudaMemcpy(outputArray, d_outputArray, size, cudaMemcpyDeviceToHost);

    cudaFree(d_inputArray);
    cudaFree(d_outputArray);

    printf("output array: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", outputArray[i]);
    }
    printf("\n");
    return 0;
}
    return 0;
}
