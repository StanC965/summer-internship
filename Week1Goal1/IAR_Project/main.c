#define MAX 10

void main (void)
{
  int x=2;
  #define MAX 55
  x=MAX;
}

// value of x will be 55 the new vlue of MAX