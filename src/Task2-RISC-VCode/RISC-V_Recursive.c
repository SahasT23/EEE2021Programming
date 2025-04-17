#include <stdio.h>

/*
Recursive works by using the previous results, as we return the previous result back into the calculation.
Looking back at the array (3, 6, 7, 8)
So first, the function calculates 3! normally:
1 x 2 x 3.
Now for 6, it uses the previously stored result for 3!. We can think of 6! like this:
3! x 4 x 5 x 6. 
The above uses the previous calculation for 3! in the calculation for 6!.
7! would then use the previous result of 6! and multiply it by 7. 
*/

int main() {
    /* Assembly would have a .data section for the array:
       .data
   testInput: .word 3, 6, 7, 8
       
       And then start the .text section:
       .text
       main:
    */
    
    int testInput[] = {3, 6, 7, 8};   /* Defined in .data section */
    int arraySize = 4;                 /* addi t1, x0, 4      # t1 = 4 (array size) */
    
    int i = 0;                         /* add t0, x0, x0      # t0 = 0 (initialise loop counter) */
    
    /* Process each element in the array (main_loop in assembly) */
    while (i < arraySize) {            /* main_loop:
                                          beq t0, t1, main_exit  # Exit loop if i equals arraySize */
        
        /* Get the current array element */
        int value = testInput[i];      /* slli t3, t0, 2      # t3 = i * 4 (byte offset)
                                          la t2, testInput     # t2 = address of testInput
                                          add t4, t2, t3      # t4 = address of testInput[i]
                                          lw a0, 0(t4)        # a0 = testInput[i] */
        
        /* Save registers before function call */
                                       /* addi sp, sp, -20    # Allocate stack space
                                          sw t0, 0(sp)        # Save i
                                          sw t1, 4(sp)        # Save arraySize
                                          sw t2, 8(sp)        # Save testInput address
                                          sw t3, 12(sp)       # Save byte offset
                                          sw t4, 16(sp)       # Save element address */
        
        /* Calculate factorial using recursive approach */
        int result = factorial_recursive(value); /* jal ra, factorial_recursive   # Call factorial, save return address */
        
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

/* Recursive factorial function using repeated addition for multiplication */
int factorial_recursive(int n) {       /* factorial_recursive:  # a0 = n */
    
    /* Base case: factorial of 0 is 1 */
    if (n == 0) {                      /* beq a0, x0, fact_return_one  # If n == 0, return 1 */
        return 1;                      /* fact_return_one:
                                          addi a0, x0, 1      # a0 = 1
                                          jalr x0, 0(ra)      # Return to caller */
    }
    
    /* Recursive case: n! = n * (n-1)! */
    /* Save return address and n for after recursive call */
                                       /* addi sp, sp, -8     # Allocate stack space
                                          sw ra, 0(sp)        # Save return address
                                          sw a0, 4(sp)        # Save n */
    
    /* Calculate (n-1)! */
    int n_minus_1 = n - 1;             /* addi a0, a0, -1     # a0 = n - 1 */
    int factorial_n_minus_1 = factorial_recursive(n_minus_1);  
                                       /* jal ra, factorial_recursive  # Call factorial_recursive(n-1) */
    
    /* Restore n and prepare for multiplication */
                                       /* lw a1, 4(sp)        # Load original n into a1
                                          mv a2, a0           # Save factorial(n-1) in a2 */
    
    /* Use repeated addition to multiply n * factorial(n-1) */
    int result = multiply(n, factorial_n_minus_1);  
                                       /* mv a0, a1           # Set first argument to n
                                          mv a1, a2           # Set second argument to factorial(n-1)
                                          jal ra, multiply    # Call multiply */
    
    /* Restore return address and return */
                                       /* lw ra, 0(sp)        # Restore return address
                                          addi sp, sp, 8      # Deallocate stack space */
    
    return result;                     /* jalr x0, 0(ra)      # Return to caller with result in a0 */
}