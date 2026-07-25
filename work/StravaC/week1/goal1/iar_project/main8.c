#include <iom324pb.h>

int main(void)
{
    volatile unsigned int a = 1u;
    volatile unsigned int b = 257u;
    volatile unsigned int c = 0u;

    c = a + b;
    
    //little endian

    while (1)
    {
    }
}