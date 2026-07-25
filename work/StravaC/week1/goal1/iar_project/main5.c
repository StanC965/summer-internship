#define MAX_VALUE(a, b)      (((a) > (b)) ? (a) : (b))
#define AVERAGE_VALUE(a, b)  (((a) + (b)) / 2)

int main(void)
{
    volatile int first_number = 10;
    volatile int second_number = 20;

    volatile int maximum = MAX_VALUE(first_number, second_number);
    volatile int average = AVERAGE_VALUE(first_number, second_number);

    while (1)
    {
    }
}