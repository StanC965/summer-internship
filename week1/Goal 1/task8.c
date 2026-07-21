struct student{
char nume[20];
unsigned char varsta;
unsigned char inaltime;

};
void main(void){
  struct student eu={
  .nume= "Nelutu",
  .varsta = 21,
  .inaltime = 178,
  };
  int h = eu.varsta;
  
}