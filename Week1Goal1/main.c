#define MAX 10

void main (void)
{
    int x=2;
    #define MAX 55
    x=MAX;
}

//warning because of the redefinition, x will be 55 