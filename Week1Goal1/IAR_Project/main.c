#define MAX(i, limit) do \
{ \
    if (i < limit) \
    { \
        i++; \
    } \
} while(1)

void main(void)
{
  int c=0;
    MAX(c,3);
}

// the initial code as seen in .i file will try to  increment 0 a constant 
// to make this code work i replaced 0 with a variable c that can be changed
// it will increment the c until it will reach the limit and after that it will stay into an infinite loop checking the value of c