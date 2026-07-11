struct Student
{
    char name[30];
    unsigned char age;
    unsigned char height;
};


void main(void)
{
    struct Student student = {
        "Viorel",
        25,
        180
    };
}
