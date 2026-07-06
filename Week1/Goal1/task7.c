void test_static(){
  int static a = 3;
  a++;
}


void main(void){
    test_static();
    test_static();
    //se initializeaza o singura data
    volatile int v = 5;
    v = 10;
    //se schimba in memorie, nu doar in cache
}