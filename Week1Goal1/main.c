// 157 - macros for max and average
#define max(a, b) ((a) > (b) ? (a) : (b))
#define average(a, b) (((a) + (b)) / 2)

void main(void)
{
    int x = 5;
    int y = 8;

    int biggest = max(x, y);
    int avg = average(x, y);

}