.data
test_input: .word 3 6 7 8    # Initial values for the factorial calculation
# This array contains 4 elements: [3, 6, 7, 8], in my other file (FactorialAndLAternatives.c), I used more data for a better curve. 

.text
main:
    add t0, x0, x0            # Initialise the loop counter (t0) to 0, starting at 3.
    addi t1, x0, 4            # Store array size (t1 = 4 elements).
    la t2, test_input         # Load the base address of test_input array into t2.

main_loop:
    beq t0, t1, main_exit     # Exit loop when counter reaches array size (4), exits after finding 8.
    slli t3, t0, 2            # Calculate the byte offset (index * 4) for word array.
    add t4, t2, t3            # Calculate element address: base + byte offset.
    lw a0, 0(t4)              # Load current array element into argument register a0

    # Preserve caller-saved registers before function call
    addi sp, sp, -20          # Allocates 20 bytes (5 registers * 4 bytes ) on stack
    sw t0, 0(sp)              # Save loop counter
    sw t1, 4(sp)              # Save array size
    sw t2, 8(sp)              # Save array base address
    sw t3, 12(sp)             # Save byte offset
    sw t4, 16(sp)             # Save current element address

    jal ra, factorial         # Jump to factorial function, saving return address in ra

    # Restore saved registers after function return
    lw t0, 0(sp)              # Restore loop counter
    lw t1, 4(sp)              # Restore array size
    lw t2, 8(sp)              # Restore array base address
    lw t3, 12(sp)             # Restore byte offset
    lw t4, 16(sp)             # Restore current element address
    addi sp, sp, 20           # Deallocate stack space

    # Print factorial result
    addi a1, a0, 0            # Move factorial result from a0 to a1 (print argument)
    addi a0, x0, 1            # Set system call code 1 (print integer)
    ecall                     # Execute system call to print integer

    # Print space separator between results
    addi a1, x0, ' '          # Load ASCII space character (0x20) into a1
    addi a0, x0, 11           # Set system call code 11 (print character)
    ecall                     # Execute system call to print space

    addi t0, t0, 1            # Increment loop counter
    jal x0, main_loop         # Unconditional jump back to loop start

main_exit:
    addi a0, x0, 10           # Set system call code 10 (exit)
    ecall                     # Exit program


# Iterative factorial implementation (without mul instruction)
# Input: a0 = n
# Output: a0 = n! or -1 for error
factorial:
    # Handle special cases first
    blt a0, x0, error_case    # If n < 0: invalid input, return error
    beq a0, x0, return_one    # If n == 0: 0! = 1 (base case ocvered)

    # Initialize calculation variables
    addi t0, x0, 1            # t0 = accumulator for result (starts at 1)
    addi t1, x0, 1            # t1 = loop counter (i), starts at 1

factorial_loop:
    bgt t1, a0, factorial_done  # Exit loop when i > input n
    # Multiply accumulator (t0) by current i (t1) using repeated addition
    # (This implements t0 = t0 * t1 without mul instruction)
    add t2, x0, x0            # t2 = temporary product (initialize to 0)
    add t3, x0, t0            # t3 = current accumulator value (to add repeatedly)
    add t5, x0, t1            # t5 = number of additions needed (current i value)

mult_loop:
    beq t5, x0, mult_done     # Exit when addition counter reaches 0
    add t2, t2, t3            # Add current accumulator value to product
    addi t5, t5, -1           # Decrement addition counter
    jal x0, mult_loop          # Repeat addition

mult_done:
    add t0, x0, t2            # Update accumulator with multiplication result
    addi t1, t1, 1            # Increment loop counter i
    jal x0, factorial_loop     # Continue factorial calculation

factorial_done:
    add a0, t0, x0            # Move final result to return register a0
    jalr x0, ra, 0            # Return to caller using saved return address

error_case:
    addi a0, x0, -1           # Return -1 for invalid negative input
    jalr x0, ra, 0

return_one:
    addi a0, x0, 1            # Return 1 for 0! case
    jalr x0, ra, 0