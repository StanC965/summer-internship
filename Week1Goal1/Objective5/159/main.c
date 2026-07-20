// 159 - define and initialize a student structure
struct student
{
    char name[20];        // array for name
    unsigned char age;    // age
    unsigned char height; // height (cm)
};

void main(void)
{
    struct student s = { "Bianca", 22, 165 };
}
