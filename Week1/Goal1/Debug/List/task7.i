#line 1 "D:\\Mircea\\Marqurdt\\summer-internship\\Week1\\Goal1\\task7.c"
void test_static(){
  int static a = 3;
  a++;
}


void main(void){
    test_static();
    test_static();
    volatile int v = 5;
    v = 10;
}
