#line 1 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal1\\main.c"
volatile int ready=0; 

void count(void){
  static int contor=0; 
  contor++;
}

void test(){
  if(ready==0)
    ready=1;
}

void main(void){
  count(); 
  count(); 
  test();
    
}
