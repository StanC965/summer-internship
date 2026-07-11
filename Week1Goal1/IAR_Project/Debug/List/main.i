void counter(void)
{
    
    
    static int count = 0;

    count++;
}

void main(void)
{
    counter();   
    counter();   
    counter();   
}
