struct student {
    char name[50];          
    unsigned char age;      
    unsigned char height;   
};

int main(void)
{
    struct student me = {
        .name = "Sebi",
        .age = 23, 
        .height = 180 
    };

    return 0;
}