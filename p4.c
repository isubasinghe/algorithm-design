#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Get the first digit in an integer
int get_first(int a) {
    // This is O(log(a))
    /*
    while(a/10 > 1) {
        a /= 10;
    }
    return a;
    */

   // Faster than the loop, now this is O(1).
   int num_div = log10(a);
   a /= pow(10, num_div);
   return a;
}

// Comparision function for quicksort
int cmpfunc(const void *a, const void *b) {
    int *v1 = (int *)a;
    int *v2 = (int *)b;
    
    int first1 = get_first(*v1); // First digit of v1
    int first2 = get_first(*v2); // first digit of v2
    // We really care about the first value more than 
    // anything.
    if(first1 < first2) {
        return 1;
    }else {
        // our second priority is the number of digits
        // in each integer. log10 lets us do this in O(1).
        if(log10(*v1) < log10(*v2)) {
            return 1;
        }else {
            return 0;
        }
    }

}

// O(nlog(n)) time, don't think it is possible to be faster.
int bignum(int *array, int n) {
    qsort(array, n, sizeof(int), cmpfunc);
    int val = 0;

    // I really wanted to avoid doing this, 
    // that is why I didn't deal with chars initially.
    // It just feels 'hacky'.
    char buffer[2048];
    int bi = 0;

    for(int i=0; i < n; i++) {
        char num[128]; 
        // Convert to a string and put in num
        itoa(array[i], num, 10);
        // Append to a string buffer
        strcat(buffer, num);
    }
    // Set the null byte.
    buffer[2047] = 0;
    // Convert to a integer and return.
    return atoi(buffer);
}



int main(int argc, char *argv[]) {
    int array[] = {99, 10, 53, 5, 50};
    printf("%d\n", bignum(array, sizeof(array)/sizeof(int)));
    
    return 0;
}