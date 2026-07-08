#define MAX 100

void main (void)
{
  int MAX = 10;
}

// This code will generate an error MAX is replaced with the value 100 
// This can be seen in the generated .i file, where the code becomes int 100 = 10; the MAX macro has been replaced with its value. 
// As a result, the compiler encounters 100 where it expects a variable name, causing a compilation error.