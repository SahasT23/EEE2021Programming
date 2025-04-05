.data
test_input: .word 3 6 7 8    # Array of input values to calculate factorial for

.text
main:
	add t0, x0, x0            # Initialize t0 (loop counter/index) to 0
	addi t1, x0, 4            # Set t1 to 4 (number of elements in test_input array)
	la t2, test_input         # Load address of test_input array into t2

main_loop:
	beq t0, t1, main_exit     # If t0 == t1 (processed all elements), exit the loop
	slli t3, t0, 2            # t3 = t0 * 4 (scale index by 4 bytes per word)
	add t4, t2, t3            # t4 = address of test_input[t0] (base + offset)
	lw a0, 0(t4)              # Load value at address t4 into a0 (argument for factorial)

	# Save all registers that will be used by the factorial function
	addi sp, sp, -20          # Allocate 20 bytes on the stack using the pointer.
	sw t0, 0(sp)              # Save t0 (loop counter)
	sw t1, 4(sp)              # Save t1 (array size)
	sw t2, 8(sp)              # Save t2 (array base address)
	sw t3, 12(sp)             # Save t3 (byte offset)
	sw t4, 16(sp)             # Save t4 (current element address)

	jal ra, factorial         # Call factorial function, return address saved in ra

	# Restore saved registers from stack
	lw t0, 0(sp)              # Restore t0 (loop counter)
	lw t1, 4(sp)              # Restore t1 (array size)
	lw t2, 8(sp)              # Restore t2 (array base address)
	lw t3, 12(sp)             # Restore t3 (byte offset)
	lw t4, 16(sp)             # Restore t4 (current element address in array)
	addi sp, sp, 20           # Deallocates the stack space

	# Print the factorial result
	addi a1, a0, 0            # Move factorial result from a0 to a1 (argument for print)
	addi a0, x0, 1            # Set a0 to 1 (system call code for print integer)
	ecall                     # Make system call to print the integer

	# Print a space character
	addi a1, x0, ' '          # Load space character into a1
	addi a0, x0, 11           # Set a0 to 11 (system call code for print character)
	ecall                     # Make system call to print the space

	addi t0, t0, 1            # Increment loop counter
	jal x0, main_loop         # Jump back to main_loop
	
main_exit:  
	addi a0, x0, 10           # Set a0 to 10 (system call code for exit)
	ecall                     # Make system call to exit program

# Iterative implementation of factorial function
factorial:
	# Handle base cases
	blt a0, x0, error_case    # If n < 0, jump to error_case
	beq a0, x0, return_one    # If n = 0, jump to return_one (0! = 1)
	
	# Initialize variables for factorial calculation
	addi t0, x0, 1            # t0 = 1 (result accumulator, starts at 1)
	addi t1, x0, 1            # t1 = 1 (loop counter i, starts at 1)
	
factorial_loop:
	bgt t1, a0, factorial_done  # If i > n, exit loop and return result
	
	# Multiply result by i (without using mul instruction)
	# We'll implement t0 = t0 * t1 using repeated addition
	add t2, x0, x0            # t2 = 0 (temporary product result)
	add t3, x0, t0            # t3 = t0 (copy of current factorial result)
	add t5, x0, t1            # t5 = t1 (copy of current counter)
	
mult_loop:
	beq t5, x0, mult_done     # If t5 == 0, multiplication is complete
	add t2, t2, t3            # t2 += t3 (add t0 to product t5 times)
	addi t5, t5, -1           # Decrement t5 counter
	j mult_loop               # Repeat until t5 reaches 0
	
mult_done:
	add t0, x0, t2            # Update factorial result with product
	addi t1, t1, 1            # Increment counter (i++)
	j factorial_loop          # Continue to next iteration
	
factorial_done:
	add a0, t0, x0            # Set a0 to the final factorial result
	jalr x0, ra, 0            # Return to caller
	
error_case:
	addi a0, x0, -1           # Set a0 to -1 (indicating error for negative input)
	jalr x0, ra, 0            # Return to caller
	
return_one:
	addi a0, x0, 1            # Set a0 to 1 (0! = 1 by definition)
	jalr x0, ra, 0            # Return to caller