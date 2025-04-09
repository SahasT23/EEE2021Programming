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
	addi sp, sp, -20          # Allocate 20 bytes on the stack
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
	lw t4, 16(sp)             # Restore t4 (current element address)
	addi sp, sp, 20           # Deallocate stack space

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

# Recursive implementation of factorial function
factorial:
	# Save return address and s0 on the stack
	addi sp, sp, -8           # Allocate 8 bytes on stack (2 words)
	sw ra, 4(sp)              # Save return address
	sw s0, 0(sp)              # Save s0 (will use to store n)
	
	# Handle base cases
	blt a0, x0, error_case    # If n < 0, jump to error_case
	beq a0, x0, return_one    # If n = 0, jump to return_one (0! = 1)
	
	# Save n for later use
	add s0, a0, x0            # s0 = n (save the current value)
	
	# Calculate (n-1)!
	addi a0, a0, -1           # a0 = n - 1
	jal ra, factorial         # Recursive call to factorial(n-1)
	
	# At this point, a0 contains factorial(n-1)
	# Need to calculate n * factorial(n-1)
	
	# Multiply a0 by s0 (without using mul instruction)
	# We'll implement a0 = a0 * s0 using repeated addition
	add t0, x0, x0            # t0 = 0 (result accumulator)
	add t1, x0, a0            # t1 = a0 (copy of (n-1)!)
	add t2, x0, s0            # t2 = s0 (copy of n)
	
mult_loop:
	beq t2, x0, mult_done     # If t2 == 0, multiplication is complete
	add t0, t0, t1            # t0 += t1 (add (n-1)! to result n times)
	addi t2, t2, -1           # Decrement counter
	j mult_loop               # Repeat until t2 reaches 0
	
mult_done:
	add a0, x0, t0            # Set a0 to the multiplication result (n * (n-1)!)
	
	# Restore saved registers and return
	lw s0, 0(sp)              # Restore s0
	lw ra, 4(sp)              # Restore return address
	addi sp, sp, 8            # Deallocate stack space
	jalr x0, ra, 0            # Return to caller
	
error_case:
	addi a0, x0, -1           # Set a0 to -1 (indicating error for negative input)
	lw s0, 0(sp)              # Restore s0
	lw ra, 4(sp)              # Restore return address
	addi sp, sp, 8            # Deallocate stack space
	jalr x0, ra, 0            # Return to caller
	
return_one:
	addi a0, x0, 1            # Set a0 to 1 (0! = 1 by definition)
	lw s0, 0(sp)              # Restore s0
	lw ra, 4(sp)              # Restore return address
	addi sp, sp, 8            # Deallocate stack space
	jalr x0, ra, 0            # Return to caller