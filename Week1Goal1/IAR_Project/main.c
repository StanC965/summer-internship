// declarare variabile globale
int a;
int b;
int c;

// definitie functie care aduna doua valori primite ca parametru
int function_sum(int x, int y){
  int sum;
  sum = x+y;
  
  return sum;
}

int main( void )
{
  // atribuire de valori pentru var globale
  a=1;
  b=3;
  
  // utilizarea functiei de adunare cu salvarea valorii retunate in variabila c
  c=function_sum(a,b);
  
  return 0;
}
