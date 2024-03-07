#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EMPTY -1

// https://oeis.org/A000045
unsigned int fibsequence[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155};

unsigned long long int fibloop(int n) {
    unsigned long long int mem[n+1];

    if (n > 0 && n < 3) {
        return n - 1;
    }

    mem[0] = 0, mem[1] = 1;

    for (int i = 2; i <= n; i++) {
        mem[i] = mem[i - 1] + mem[i - 2];
    }

    return mem[n - 1];
}

unsigned long long int fibdynamicmemo(int n, long long int *memo) {
    if (memo[n - 1] == EMPTY) {
        memo[n - 1] = fibdynamicmemo(n - 1, memo) + fibdynamicmemo(n - 2, memo);
    }
    return memo[n - 1];
}

unsigned long long int fibdynamic(int n) {
    unsigned long long int *memo = malloc((n+1) * sizeof(long long int));
    for (int i = 0; i < n; i++) {
        memo[i] = EMPTY;
    }

    memo[0] = 0, memo[1] = 1;
    unsigned long long int result = fibdynamicmemo(n, memo);
    
    free(memo);
    return result;
}

int test_loop() {
    int result = 1;
    for (int n = 1; n <= sizeof(fibsequence)/sizeof(int); n++) {
        unsigned int actual = fibloop(n);
        unsigned int expected = fibsequence[n - 1];
        if (actual != expected) {
            fprintf(stderr, "fibloop(%u) = %u != %u\n", n, actual, expected); result = 0;
        }
    }
    return result;
}

int test_dynamic() {
    int result = 1;
    for (int n = 1; n <= sizeof(fibsequence)/sizeof(int); n++) {
        int actual = fibdynamic(n);
        int expected = fibsequence[n - 1];
        if (actual != expected) {
            fprintf(stderr, "fibdynamic(%u) = %u != %u\n", n, actual, expected); result = 0;
        }
    }
    return result;
}

long long unsigned int binet(int n) { // floating point errors for n > 76
    double phi = (1 + sqrt(5)) / 2; 
    return round(pow(phi, n) / sqrt(5)); 
} 

void printfib(int n) {
    printf("fib.loop(%u) \t= %llu\n", n, fibloop(n));
    printf("fib.dyn(%u) \t= %llu\n", n, fibdynamic(n));
    printf("binet (%u) \t= %llu\n", n, binet(n-1));
}

int main(int argc, char *argv[]) {

    if (test_loop()) printf("fibloop passed\n");
    if (test_dynamic()) printf("fibdynamic passed\n");

    if (argc == 2) {
        int n = atoi(argv[1]);
        if (n > 0) printfib(n);
    } else {
        printf("usage: %s n", argv[0]);
    }
}