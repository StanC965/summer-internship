#if MAX == 1
#define VAR 4
#else
#define VAR 5
#endif

int main(void)
{
    volatile int value = VAR;

    while (1)
    {
    }
}