#line 1 "C:\\Users\\Stefan\\summer-internship\\W1G1\\IAR_Exercises\\main.c"


int contor_apeluri(void)
{
    
   
    static int apeluri = 0; 
    
    apeluri++;
    return apeluri;
}



volatile int senzor_hardware = 0; 

void simulare_intrerupere_hardware(void)
{
  
    senzor_hardware++;
}




int main(void)
{
    
    static int x = 1; 
    
   
    for(int i = 0; i < 3; i++)
    {
      
        int nr_actual = contor_apeluri();
       
    }
    

    
    
    simulare_intrerupere_hardware(); 
    

    
    return 0;
}
