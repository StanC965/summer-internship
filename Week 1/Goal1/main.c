volatile int ready=0; //poate fi schimbata de hardware

void count(void){
  static int contor=0; //se initializeaza o singura data, isi pastreaza valoarea intre apelurile functiei, dar nu si in afara acesteia
  contor++;
}

void test(){
  if(ready==0)
    ready=1;
}

void main(void){
  count(); //1
  count(); //2
  test();
    
}