#line 1 "C:\\MQ_Summer_Internship\\Project\\summer-internship\\code\\main.c"




static int a = 10;

void count(void){
  
  
  
  
  static int counter = 0;
  counter++;
}

void main(void)
{
  while(1){
    count();
  }
}
