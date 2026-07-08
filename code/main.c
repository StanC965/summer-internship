typedef struct{
  char name[50];
  unsigned char age;
  unsigned char height;
} Student;

void main(void)
{
  Student student_1 = { "Alice", 21, 170};
  Student student_2 = { "Bob", 21, 180};
}