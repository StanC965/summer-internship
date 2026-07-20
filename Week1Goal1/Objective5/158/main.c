// 158 - static and volatile keyword usage
// 'static' local variable keeps its value between function calls
void count_calls(void)
{
    static int counter = 0;  
    counter++;
}

// 'volatile' prevents the compiler from optimizing accesses to this variable
volatile int sensor_flag = 0;

void main(void)
{
    count_calls();
    count_calls();  // counter is now 2 (value was retained)
    while(1)
    {
        if (sensor_flag != 0)
        {

        }
    }
}
