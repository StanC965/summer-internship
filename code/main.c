#define MAX(a, b) ((a) + (b))

#define AVERAGE(a, b) (((a) + (b)) / 2)

void main(void)
{
    int a = 2, b = 3;
    int max, average;
    
    max = MAX(a, b);
    average = AVERAGE(a, b);
}