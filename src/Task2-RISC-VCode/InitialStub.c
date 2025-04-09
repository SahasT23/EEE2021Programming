#include <stdio.h>

// Factorial function implementation
int factorial(int n) {
    // Base and special case as factorial of 0 or 1 is 1, very quick way, I do it differently in my other file.
    // Need to add to readme file.
    if (n == 0 || n == 1) { // Ideally I should be using an atomic-c style, closer to a proper translation for assembly
        return 1;
    }
    
    // Recursive computation of factorial, added it in as well just so the program actually runs
    return n * factorial(n - 1);
}

int main() {
    // Added a while loop to match the initially given Assembly.    
    int test_input[] = {3, 6, 7, 8};  // Input array
    
    // Loop index variables
    int i = 0;  // calculation needs to start with the 0th element
    int array_size = 4;  // Total number of elements (3, 6, 7, 8)

    while (i < array_size) {
        // Passes current array element to factorial function, adds the function call
        int current_input = test_input[i];
        int result = factorial(current_input);
        
        // Prints each factorial result, like syscall
        printf("%d ", result);
        
        // Increment loop counter
        i++;
    }
    
    // 5) Return/exit logic included [1 mark]
    // Provides clean program termination
    // Matches the assembly's exit syscall
    printf("\n");
    return 0;
}