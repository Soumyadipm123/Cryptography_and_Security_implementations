#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int GCD_cal(int a, int b){
     int temp,temp1;
    temp = a % b;
    while(temp != 0){
        temp1 = temp;
        temp = b % temp1;
        b = temp1;
    }
    return b;
}

int main(){
    clock_t start, end;
    int trials = 10000000;
    double cpu_time_used;
    
    srand(time(NULL));
    // 1. Declare pointers and allocate memory dynamically on the heap
    int *arr1 = (int *)malloc(trials * sizeof(int));
    int *arr2 = (int *)malloc(trials * sizeof(int));

    // 2. ALWAYS check if the computer actually gave you the memory
    if (arr1 == NULL || arr2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Stop the program if we are out of memory
    }

    // 3. Populate the arrays (the syntax remains exactly the same)
    for (int i = 0; i < trials; i++){
        arr1[i] = rand() + 1;
        arr2[i] = rand() + 1;
    }
    

    start = clock();
    for(int i =0; i < trials; i++){ 
        GCD_cal(arr1[i], arr2[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    double avg_time = (cpu_time_used/ trials) * 1000000000;
    printf("Total time for %d calculations: %f seconds\n", trials, cpu_time_used);
    printf("Average time per calculation: %f microseconds\n", avg_time);
    free(arr1);
    free(arr2);

    return 0;
}