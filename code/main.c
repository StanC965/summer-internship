// the static keyword has two properties, depending on what type of variables it is applied on 
// for global variables, it limits the scope of the variable to the file it was declared in

// this means that variable a can be accessed only in this source file 
static int a = 10;

void count(void){
  // for local variables, it can extend their lifetime
  // normally a local variable is created when a function is called and destroyed after the function ends
  
  // in this case, counter is initialized only once, and it keeps its value even after the function 
  static int counter = 0;
  counter++;
}

void main(void)
{
  // the volatile keyword is used to stop the compiler from optimizing a variable 
  // the compiler's primary goal is to make the code as small as possible and as fast as possible
  // in this project we set the compiler to make no code optimization
  // if the compiler would've been set to optimize the code,
  // then we could use the volatile keyword to alert the compiler what variables it shouldn't optimize
  
  // e.g. we can use volatile for a flag that is updated by the ISR
  
  while(1){
    count();
  }
}