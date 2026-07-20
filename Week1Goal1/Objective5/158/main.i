#line 1 "C:\\Users\\Bibi\\Desktop\\summer-internship\\Week1Goal1\\main.c"


void count_calls(void)
{
    static int counter = 0;  
    counter++;
}


volatile int sensor_flag = 0;

void main(void)
{
    count_calls();
    count_calls();  
    while(1)
    {
        if (sensor_flag != 0)
        {

        }
    }
}
