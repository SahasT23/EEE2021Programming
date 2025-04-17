#include <stdio.h>

/*
Iterative works by just going through the array, looping through the elements (3, 6, 7, 8)
so 3! :
1 x 2 x 3,
then 6! :
1 x 2 x 3 x 4 x 5 x 6
etc.
*/

int main() {
    /**
     * .data
     * testInput: .word 3, 6, 7, 8
     * 
     * And then start the .text section
     * .text
     * main:
    */
    
    int testInput[] = {3, 6, 7, 8};   // Defined in .data section 
    int arraySize = 4;                  // addi t1, x0, 4      # t1 = 4 (array size) 
    
    int i = 0;                         //  add t0, x0, x0       t0 = 0 (initialise loop counter) 
    
    // Process each element in the array (main_loop in assembly) 
    while (i < arraySize) {            /* main_loop:beq t0, t1, main_exit  # Exit loop if i equals arraySize */
        
        int value = testInput[i];      /* slli t3, t0, 2      # t3 = i * 4 (byte offset)
                                          la t2, testInput     # t2 = address of the testInput part
                                          add t4, t2, t3      # t4 = address of testInput[i] index
                                          lw a0, 0(t4)        # a0 = testInput[i] */
        
        /* Save registers before function call */
                                       /* addi sp, sp, -20    # Allocate stack space
                                          sw t0, 0(sp)        # Save i
                                          sw t1, 4(sp)        # Save arraySize
                                          sw t2, 8(sp)        # Save testInput address
                                          sw t3, 12(sp)       # Save byte offset
                                          sw t4, 16(sp)       # Save element address */
        
        /* Calculate factorial */
        int result = factorial(value); /* jal ra, factorial   # Call factorial, save return address */
        
        /* Restore registers after function call */
                                       /* lw t0, 0(sp)        # Restore i
                                          lw t1, 4(sp)        # Restore arraySize
                                          lw t2, 8(sp)        # Restore testInput address
                                          lw t3, 12(sp)       # Restore byte offset
                                          lw t4, 16(sp)       # Restore element address
                                          addi sp, sp, 20     # Deallocate stack space */
        
        /* Print the result and a space */
        printf("%d ", result);         /* mv a1, a0           # Move result to a1 for printing
                                          li a0, 1            # System call code for print_int
                                          ecall               # Print the integer
                                          li a1, ' '          # Load space character to a1
                                          li a0, 11           # System call code for print_char
                                          ecall               # Print the space */
        
        /* Increment loop counter */
        i++;                           /* addi t0, t0, 1      # Increment i
                                          j main_loop         # Jump back to start of loop */
    }
    
    return 0;                          /* main_exit:
                                          li a0, 10           # System call code for exit
                                          ecall               # Exit programme */
}

/* Function to multiply using repeated addition */
int multiply(int a, int b) {           /* multiply:           # a0 = a, a1 = b */
    
    int result = 0;                    /* add t0, x0, x0      # t0 = 0 (result) */
    
    /* Handle case where b is 0 */
    if (b == 0) {                      /* beq a1, x0, mult_return_zero  # If b == 0, return 0 */
        return 0;                      /* mult_return_zero:
                                          add a0, x0, x0      # a0 = 0
                                          jalr x0, 0(ra)      # Return to caller */
    }
    
    /* Use repeated addition to calculate a*b */
    for (int i = 0; i < b; i++) {      /* add t1, x0, x0      # t1 = 0 (loop counter i)
                                          mult_loop:
                                          beq t1, a1, mult_done  # If i == b, exit loop */
        
        result += a;                   /* add t0, t0, a0      # result += a */
        
                                       /* addi t1, t1, 1      # i++
                                          j mult_loop         # Continue loop */
    }
    
    return result;                     /* mult_done:
                                          add a0, t0, x0      # Return result in a0
                                          jalr x0, 0(ra)      # Return to caller */
}

/* Factorial function using repeated addition for multiplication */
int factorial(int n) {                 /* factorial:          # a0 = n */
    
    /* Base case: factorial of 0 is 1 */
    if (n == 0) {                      /* beq a0, x0, fact_return_one  # If n == 0, return 1 */
        return 1;                      /* fact_return_one:
                                          addi a0, x0, 1      # a0 = 1
                                          jalr x0, 0(ra)      # Return to caller */
    }
    
    /* Initialise result to 1 */
    int result = 1;                    /* addi t0, x0, 1      # t0 = 1 (result) */
    
    /* Calculate n! = 1 * 2 * 3 * ... * n */
    for (int i = 1; i <= n; i++) {     /* addi t1, x0, 1      # t1 = 1 (loop counter i)
                                          fact_loop:
                                          bgt t1, a0, fact_done  # If i > n, exit loop */
        
        /* Use repeated addition for multiplication */
        result = multiply(result, i); 
        
        /** addi sp, sp, -12    # Allocate stack space
         * sw ra, 0(sp)        # Save return address
         * sw t0, 4(sp)        # Save result
         * sw t1, 8(sp)        # Save i
         * 
         * mv a0, t0           # First argument = result
         * mv a1, t1           # Second argument = i
         * jal ra, multiply    # Call multiply function
         * 
         * lw ra, 0(sp)        # Restore return address
         * lw t1, 8(sp)        # Restore i
         * addi sp, sp, 12     # Deallocate stack space
         * 
         * mv t0, a0           # Store multiply result in t0
         * 
         * addi t1, t1, 1      # i++
         * fact_loop         # Continue loop 
        */
    }
    
    return result;   /* fact_done:
                        mv a0, t0           # Return result in a0
                        jalr x0, 0(ra)      # Return to caller */
}