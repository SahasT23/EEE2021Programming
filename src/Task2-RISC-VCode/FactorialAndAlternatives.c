#include <stdio.h>  
#include <time.h>   // Maybe don't need to worry about this for the assembly annotations. Not sure though.

/**
 * Need to add:
 * 1. space and time complexity
 * 2. Explanation for stack usage
 * 3. demonstrate I know how the stack works.
 * 4. Create a graph for comparison, add in larger values and increase the array size. (still considering)
 * 5. Add Task 1 writing to google doc. Make sure the cyclical strucuture idea links throughout the report -> refer to ideas in task 1 in tasl 3.,
 * 6. Add in pseudocode to show understanding for the difference between iterative and recursive method (link to point one).
 * 7. find GPU emulators to show why optimisation is necessary (more for task 1).
 * 8. wait until lectures start for Task 2B help.
 * 9. Add C kernel for Jupyter Notebook. Convert writte notes for GeMM to Python prototype and C code. 
 */

double measure_time(int (*func)(int), int input, int iterations) {
    
    clock_t start, end;  // Local variables already allocated on stack. 
    int result;         // HAd to change the timing function because I was just getting zeros when finding the time.
    
    start = clock();  // Function call:
    
    for (int i = 0; i < iterations; i++) {  // Loop goes through initialisation:
        /**
         * li t0, 0                Initialising i = 0 in t0.
         * loop_start:
         * bge t0, a2, loop_end    Exit loop if i >= iterations (a2), so it acts like a conditional statement.
         */
        
        result = func(input);      // Function call through the pointer:
    }
    
    end = clock();       // Another function call to the clock(): 
    return ((double)(end - start)) / CLOCKS_PER_SEC / iterations;
}

/** 
 * 1. Standard iterative implementation
 * Not RISC-V, uses multiplication.
 * Time: O(n) - Does exactly n multiplications.
 * Space: O(1) - Fixed memory for 2 variables. 
*/
int iterative_array(int n) {
    /**
     * addi sp, sp, -16   Allocates the stack frame.
     * sw ra, 12(sp)      Saves the return address.
     */
    
    int result = 1;      // Initialises the result in the register:
    // li t0, 1       Load immediate 1 into t0 (the result).
    
        /**
         * li t1, 1     Initialises i = 1 in t1
         * loop_start:
         * bgt t1, a0, loop_end  Exit if i > n (a0) (to finish everything).
         */
    for (int i = 1; i <= n; i++) {  // Loop setup:
        
        result *= i;      // NOt RISC-V, down below.
        /**
         * mul t0, t0, t1     result = result * i.
         * addi t1, t1, 1     increment i by one each time. 
         * j loop_start       Jumps back to start of loop for the iterative process to actually work.
         * loop_end:
         */
    }
    
    return result;        // Return the result:
    /**
     * mv a0, t0          Moves the result to a0 (the return register).
     * lw ra, 12(sp)      Restores the return address.
     * addi sp, sp, 16    Deallocates the stack frame.
     * jalr zero, ra, 0   Return to function caller.
     * Add time and space complexity later, talk about the stack later.
     */
}

/** 
 * 2. Recursive implementation with special (base case, covers 0 and 1 factorial) case.
 * Time: O(n) - Makes n function calls.
 * Space: O(n) - Needs n stack frames.
 */
int recursive(int n) {
    /**
     * addi sp, sp, -16     Allocates the stack frame.
     * sw ra, 12(sp)        Saves the return address.
    */
    if (n == 0 || n == 1) return 1;  // Base case check:
    /**
     * bgt a0, 1, recursive_call    If n > 1, branch to recursive call.
     * li a0, 1                     Load 1 into return register.
     * j return_path                Jump to function return.
     * 
     * recursive_call:
     * Stack frame for recursive call:
     * sw a0, 8(sp)         Save n on the stack.
     */
    return n * recursive(n - 1);  // Recursive call with multiplication, RISC-V version below:
    /**
     * addi a0, a0, -1      Calculate n-1.
     * jal ra, recursive    Call recursive(n-1) function.
     * lw t0, 8(sp)         Restore n from stack.
     * mul a0, t0, a0       Multiply n * recursive(n-1).
     * 
     * return_path:
     * lw ra, 12(sp)        Restore the return address.
     * addi sp, sp, 16      Deallocate stack frame.
     * jalr zero, ra, 0     Return to caller.
     */
}

/*
 * Helper function for multiplication via addition.
 * This simulates how RISC-V would implement multiplication.
 * without using the MUL instruction, because multiplication is just repeated addition and will also be needed for task 2B.
 */
int add_multiplication(int a, int b) {
    /**
     * addi sp, sp, -16     Allocate stack frame for 4 integers.
     * sw ra, 12(sp)        Save return address.
     */
    
    int sum = 0;          // Initialise sum to 0:
    // li t0, 0            t0 will hold the sum for this function.
    
    for (int i = 0; i < b; i++) {  // Loop setup:
        /**
         * li t1, 0           Initialise i = 0 in t1
         * loop_start:
         * bge t1, a1, loop_end   Exit if i >= b (a1)
         */
        
        /**
         * sum += a;          Addition instead of multiplication:
         * add t0, t0, a0     sum += a.
         * addi t1, t1, 1     Increments i.
         * j loop_start       Jump back to the start of the loop.
         * loop_end:
         */
    }
    
    return sum;            // Return the sum:
    /**
     * mv a0, t0            Move sum to a0 (return register)
     * 
     * lw ra, 12(sp)        Restore return address
     * addi sp, sp, 16      Deallocate stack frame
     * jalr zero, ra, 0     Return to caller
     */
}

/** 
 * 3. Iterative implementation without using the MUL instruction
 * Shows nested loops and simulates assembly-level multiplication
 * Time: O(n²) - Does 1+2+3+...+n = n(n+1)/2 additions
 * Space: O(1) - Fixed memory (4 variables) 
 */
int iterativeRISCV(int n) {
    // addi sp, sp, -16     Allocate stack frame
    // sw ra, 12(sp)        Save return address
    
    int result = 1;        // Initialise result:
    // li t0, 1             t0 will hold result
    
    for (int i = 1; i <= n; i++) {  // Outer loop setup:
        /** 
         * li t1, 1           Initialise i = 1 in t1
         * outer_loop_start:
         * bgt t1, a0, outer_loop_end     Exit if i > n (a0)
        */
        
        int temp = 0;      // Initialise temp variable for multiplication:
        // li t2, 0           t2 will hold temp
        
        for (int j = 0; j < i; j++) {  // Inner loop for multiplication:
            /**
             * li t3, 0                    Initialise j = 0 in t3
             * inner_loop_start:
             * bge t3, t1, inner_loop_end  Exit if j >= i (t1)
             */
            
            temp += result;  // Add result to temp i times:
            /**
             * add t2, t2, t0     temp += result
             * 
             * addi t3, t3, 1     Increment j
             * j inner_loop_start   Jump back to inner loop start
             * inner_loop_end:
             */
        }
        
        result = temp;     // Update result:

    }
    
    return result;         // Return result:
    /**
     * mv a0, t0              Move result to a0 (return register)
     *
     *  lw ra, 12(sp)          Restore return address
     * addi sp, sp, 16        Deallocate stack frame
     * jalr zero, ra, 0       Return to caller
     */
}
     

/** 
 * 4. Recursive implementation without using the MUL instruction
 * Shows both recursion and simulated assembly-level multiplication
 * Time: O(n^2) - Each call does O(n) work, n times total
 * Space: O(n) - Needs stack for n recursive calls
 * Much worse in terms of complexity, need
 */
int recursiveRISCV(int n) { 
    // addi sp, sp, -24       Allocate stack frame
    // sw ra, 20(sp)          Save return address
    
    if (n == 0 || n == 1) return 1;  // Base case check: I initially used n <= 1, but decided to change my method
    /**
     * bgt a0, 1, recursive_call      If n > 1, branch to recursive call
     * li a0, 1                       Load 1 into return register
     * j return_path                  Jump to function return
     * recursive_call:
     * sw a0, 16(sp)        Save n on the stack
     */
    
    int prevResult = recursiveRISCV(n - 1);  // Recursive call:
    /**
     * addi a0, a0, -1      Compute n-1
     * jal ra, recursiveRISCV     Call recursiveRISCV(n-1)
     * mv t1, a0              Save return value to t1 (prevResult)
     * lw t0, 16(sp)        Restore n from stack
     */
    int result = 0;        // Initialise result for multiplication:
    // li t2, 0             t2 will hold result
    
    // Multiply prevResult by n using addition:
    for (int i = 0; i < n; i++) {  // Loop setup:
        /**
         * li t3, 0           Initialise i = 0 in t3
         * loop_start:
         * bge t3, t0, loop_end     Exit if i >= n (t0)
         */
        
        result += prevResult;  // Add prevResult to result n times:
        /**
         * add t2, t2, t1 # result += prevResult
         * 
         * addi t3, t3, 1     Increment i
         * j loop_start       Jump back to start of loop
         * loop_end:
         */
    }
    
    return result;         // Return result:
    /**
     * mv a0, t2             Move result to a0 (return register)
     * 
     * return_path:
     * Function epilogue:
     * lw ra, 20(sp)         Restore return address
     * addi sp, sp, 24       Deallocate stack frame
     * jalr zero, ra, 0     Return to caller
     */
}

int main() {
    /**
     * addi sp, sp, -64     Allocate stack frame
     * sw ra, 60(sp)        Save return address
     * sw s0, 56(sp)         Save callee-saved registers
     * sw s1, 52(sp)        Save more registers as needed
     */
    
    FILE *csv = fopen("factorial_results.csv", "w");
    
    if (!csv) {
        perror("Error creating CSV file");
        return 1;
    }
    
    // Write CSV header:
    fprintf(csv, "Method,Input,Result,ExecutionTime(s)\n");

    // Test inputs:
    int test_input[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // Original was {3, 6, 7, 8}, addded more values for test purpose.
    /**
     * Array would be stored on stack:
     * li t0, 3
     * sw t0, 0(sp)     test_input[0] = 3
     * li t0, 6
     * sw t0, 4(sp)     test_input[1] = 6
     * li t0, 7
     * sw t0, 8(sp)     test_input[2] = 7
     * li t0, 8
     * sw t0, 12(sp)    test_input[3] = 8
     */
    
    const int num_inputs = sizeof(test_input) / sizeof(test_input[0]);
    // li s1, 4           s1 = num_inputs = 4
    
    // Number of iterations for timing:
    const int iterations = 100000;
    
    // Define array of methods to test:
    struct {
        const char *name;
        int (*func)(int);
    } methods[] = {
        {"Iterative",       iterative_array},
        {"Recursive",       recursive},
        {"IterativeRISCV",  iterativeRISCV},
        {"RecursiveRISCV",  recursiveRISCV}
    };

    const int num_methods = sizeof(methods) / sizeof(methods[0]);
    // li s3, 4      s3 = num_methods = 4
    
    // Test all methods (outer loop):
    for (int m = 0; m < num_methods; m++) {
      /**
       * li t0, 0           Initialise m = 0 in t0
       * outer_loop_start:
       * bge t0, s3, outer_loop_end      Exit if m >= num_methods
       */
        
        // Test all inputs (inner loop):
        for (int i = 0; i < num_inputs; i++) {
          /**
           * li t1, 0        Initialise i = 0 in t1
           * inner_loop_start:
           * bge t1, s1, inner_loop_end    Exit if i >= num_inputs
           */
            
            int input = test_input[i];
            /**
             * Calculate array offset and load input value:
             * slli t2, t1, 2        t2 = i * 4 (to account for the byte offset)
             * add t3, sp, t2       t3 = address of test_input[i] element i.
             * lw t4, 0(t3)          t4 = test_input[i]
             * 
             * Calculate methods with the array offset:
             * slli t5, t0, 3        t5 = m * 8 (struct size)
             * addi t6, sp, 16       t6 = base address of methods array
             * add t6, t6, t5        t6 = address of methods[m]
             */
            
            // Call the function once for the final result:
            int result = methods[m].func(input);
            /**
             * lw t7, 4(t6)         t7 = methods[m].func
             * mv a0, t4            a0 = input
             * jalr ra, t7, 0        Call the function
             * mv s4, a0             s4 = result
             */
            
            // Measuring the time taken for the methods to actually calculate everything. Couldn't use the other method, kept getting zeros.
            double time_taken = measure_time(methods[m].func, input, iterations);
            /**
             * lw a0, 4(t6)         a0 = methods[m].func
             * mv a1, t4            a1 = input
             * mv a2, s2            a2 = iterations
             * jal ra, measure_time     Call measure_time function
             */
            
            fprintf(csv, "%s,%d,%d,%.10f\n", methods[m].name, input, result, time_taken);

            
            printf("%s for n=%d: result=%d, time=%.10f seconds\n",
                  methods[m].name, input, result, time_taken);
                /**
                 *             // la a0, str_console_format # a0 = format string
                 * lw a1, 0(t6)         a1 = methods[m].name
                 * mv a2, t4            a2 = input
                 * mv a3, s4            a3 = result
                 * fmv.d fa0, fa0       fa0 = time_taken
                 * jal ra, printf       Call printf function, can see output in terminal for each version of factorial function/method.
                 * 
                 * addi t1, t1, 1   Increment i
                 * j inner_loop_start  Jump back to inner loop start
                 * inner_loop_end:
                 */
        }
        
        /**
         * addi t0, t0, 1       Increment m
         * j outer_loop_start   Jump back to outer loop start
         * outer_loop_end:
         */
    }
    
    // Close CSV file:
    fclose(csv);
    
    printf("CSV report generated: factorial_results.csv\n");
    
    return 0;
    /**
     * li a0, 0             Set return value to 0
     * 
     * main_exit:
     * lw ra, 60(sp)         Restores return address.
     * lw s0, 56(sp)         Restores saved registers.
     * lw s1, 52(sp)         Restores more registers.
     * addi sp, sp, 64       Deallocate the stack frame.
     * jalr zero, ra, 0      Return to caller, end of.
     */
}
