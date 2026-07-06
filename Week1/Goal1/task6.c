#define max(a,b)\
  if(a < b)\
     a = b;\
       
#define average(a,b) ((a+b)/2)


void main(void){
    int a = 3,b=7;
    max(a,b);
    int x = average(a,b);
}