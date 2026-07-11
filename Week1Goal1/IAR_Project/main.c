int a;
int b;
int c;


int function_sum(int x, int y){
  int sum;
  sum = x+y;
  
  return sum;
}

int main( void )
{
  
  a=1;
  b=257;
  
  
  c=function_sum(a,b);
  
  return 0;
}

// the arhitecture of ATMega324PB microcontroller is little endian
// the firstbyte 0x02 is stored at the lowest adress and then the byte 0x01