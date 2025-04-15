#include <stdio.h>

/* Function prototype */
int factorial(int n);

int main() {
    /* .data
       test_input: .word 3 6 7 8 */
    int test_input[] = {3, 6, 7, 8};
    
    /* add t0, x0, x0        # Initialise loop counter i to 0 */
    int i = 0;
    
    /* addi t1, x0, 4        # Set array size to 4 */
    int array_size = 4;
    
    /* la t2, test_input     # Load address of test_input array */
    int *array_ptr = test_input;
    
    /* main_loop:            # Beginning of the main loop */
    while (1) {
        /* beq t0, t1, main_exit # Exit loop if i equals array_size */
        if (i == array_size) break;
        
        /* slli t3, t0, 2    # Calculate offset (i*4) as bytes */
        int offset = i * 4;
        
        /* add t4, t2, t3    # Calculate address of array[i] */
        int *element_ptr = (int*)((char*)array_ptr + offset);
        
        /* lw a0, 0(t4)      # Load array[i] into a0 for function argument */
        int value = *element_ptr;
        
        /* Call factorial function
           Registers are saved on stack in assembly */
        int result = factorial(value);
        
        /* Print result 
           addi a1, a0, 0    # Move result to a1
           addi a0, x0, 1    # Set a0 to 1 (print integer ecall code)
           ecall             # Print result */
        printf("%d", result);
        
        /* addi a1, x0, ' '  # Load space character
           addi a0, x0, 11   # Set a0 to 11 (print character ecall code)
           ecall             # Print space */
        printf(" ");
        
        /* addi t0, t0, 1    # Increment loop counter */
        i++;
        
        /* jal x0, main_loop # Jump back to start of loop */
        /* Loop continues through the while(1) structure */
    }
    
    /* main_exit:
       addi a0, x0, 10      # Set a0 to 10 (exit ecall code)
       ecall                # Exit programme */
    return 0;
}

int factorial(int n) {
    /* # YOUR CODE HERE - function stub in the original assembly
       This would normally contain the factorial implementation */
    return 0; /* Placeholder since original has no implementation */
}