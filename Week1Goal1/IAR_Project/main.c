volatile int buttonPressed = 0;

// Assume this function is called by an interrupt
void buttonInterrupt(void)
{
    buttonPressed = 1;
}

void main(void)
{
    while (!buttonPressed)
    {
        // Wait until the interrupt changes the variable.
        // 'volatile' tells the compiler not to optimize
        // repeated reads of buttonPressed.
    }
}

//volatile is used for variables whose value may change outside the program's normal flow (e.g., hardware registers, interrupt service routines, or another thread).