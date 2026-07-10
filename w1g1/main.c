/* 152: Suma a doua numere
int main(void) {
    int a = 5; 
    int b = 10; 
    int c = a + b;
    return 0;
}
// Obiectiv 153
#if MAX == 1
    #define VAR 4
#else
    #define VAR 5
#endif
// VAR va fi 5, deoarece MAX nu este definit.
// Obiectiv 154
#define MAX 10
void main(void) {
    int x = 2;
    #define MAX 55
    x = MAX; 
}

// Obiectiv 154
#define MAX 10
void main(void) {
    int x = 2;
    #define MAX 55
    x = MAX; 
}

// Obiectiv 155
#define MAX 100
void main(void) {
    int MAX = 10; 
}


// Obiectiv 156
#define MAX(i, limit) do { if(i < limit) { i++; } } while(0)
void main(void) {
    int i = 0;
    MAX(i, 3);
}


// Obiectiv 157
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define AVG(a, b) (((a) + (b)) / 2)


// Obiectiv 158
static int contor = 0; 
volatile int flag = 0; 
*/


// Obiectiv 159
struct Student {
    char nume[20];
    unsigned char varsta;
    unsigned char inaltime;
};
struct Student s1 = {"Cristian", 20, 180};

int main(void) {
    
    struct Student s1 = {"Cristian", 20, 180};
    
    return 0;
}