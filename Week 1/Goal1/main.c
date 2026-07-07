#define max(a,b) (((a)>(b))? a:b); //paranteza pentru fiecare parametru pentru a respecta ordinea operatiilor
#define average(a,b) (((a)+(b))/2.0);

void main(void){
   int a=max(2,3); // a=3
   double b=average(5,7); //b=6
}