

int contor_apeluri(void)
{
    // O variabila statica locala este initializata o SINGURA data (la compilare).
   
    static int apeluri = 0; 
    
    apeluri++;
    return apeluri;
}

//volatile ii interzice compilatorului sa faca optimizari precum stocarea variabile intr-un registru mai rapid
//astfel de fiecare daca cand se citeste se va citi de la adresa de memorie propri-zisa pentru a se asigura ca nicio intrerupere nu a modificat valoarea.
volatile int senzor_hardware = 0; 

void simulare_intrerupere_hardware(void)
{
  //simulam un interrupt
    senzor_hardware++;
}




int main(void)
{
    // 'static' aici limiteaza vizibilitatea lui 'x '  doar la acest fisier
    static int x = 1; 
    
   
    for(int i = 0; i < 3; i++)
    {
      
        int nr_actual = contor_apeluri();
       
    }
    

    
    
    simulare_intrerupere_hardware(); 
    

    
    return 0;
}