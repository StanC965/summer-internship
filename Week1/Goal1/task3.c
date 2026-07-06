#define MAX 10
void main (void)
{
  int x=2;
  //se redefineste MAX cu 55 pentru restul fisierului
  //#undef MAX se poate pune si asta pentru mai multa corectitudine
  #define MAX 55
  x=MAX;
}