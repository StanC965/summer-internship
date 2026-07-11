void counter(void)
{
    // 'count' is initialized only once.
    // It keeps its value between function calls.
    static int count = 0;

    count++;
}

void main(void)
{
    counter();   // Count = 1
    counter();   // Count = 2
    counter();   // Count = 3
}

//A static local variable is useful for counting function calls, 
//storing a previous state, or keeping data that should persist throughout the program without making it global.