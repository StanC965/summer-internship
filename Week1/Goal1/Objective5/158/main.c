// tells the compiler not to optimize this variable by caching it in a CPU register. 
// it forces the CPU to read its actual value directly from RAM every single time
volatile int sensor_data = 0;

int count_calls(void)
{
    // keeps its value alive even after the function finishes.
    // used to remember information between function calls
    static int counter = 0;
    
    counter++;
    return counter;
}

int main(void)
{
    int total_runs = 0;
    
    while(1)
    {
        total_runs = count_calls();
        
        if (sensor_data == 1)
        {
            total_runs++;
        }
    }
}