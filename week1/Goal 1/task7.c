//in cazul acesta volitaile se foloseste prentu variabiele
//care pot fi schimbate de hardware de expemplu, un senzor e pregatit  
// sa is faca treaba sau de o intrerupere
volatile int gata=0;

void e_gata(){
gata = 1;
}
//in cazul acesta chiar daca variabila este in fuctie
// e va fi incremantat prentu fiecare apel de functie 
//si va fi initializata o singura data
int incrementare(){
static int numar=0;
numar++;
return numar;
}

void main(void)
{
  incrementare();
  e_gata();
  incrementare();
    
}
