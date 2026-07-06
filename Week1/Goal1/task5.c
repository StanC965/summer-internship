#define MAX(i, limit) do 
{ 
    if (i < limit) 
    { 
        i++; 
    } 
} while(1)

void main(void)
{
    MAX(0,3);
}