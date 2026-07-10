int a = 1;
int b = 257;
int sum = 0;

int main(void)
{
    sum = a + b; // 02 01 in memory -> liitle endian
    return sum; 
}