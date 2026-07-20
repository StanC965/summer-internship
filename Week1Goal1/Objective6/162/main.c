// 162 - endianness check 
void main( void )
{
    int a = 1, b = 257;
    volatile int sum = 0; // i couldnt see it in the memory bcs it was stored in a CPU register, now it will be stored in SRAM bcs of volatile
    sum = a + b;  
    
    while(1)
    {
    }
    
    // sum = 258 => 0x0102 and in memory we see 02 01 => little endian
}
