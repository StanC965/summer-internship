#define MAX 10

int main(void)
{
    volatile int x = 2;

#define MAX 55

    x = MAX;

    while (1)
    {
    }
}