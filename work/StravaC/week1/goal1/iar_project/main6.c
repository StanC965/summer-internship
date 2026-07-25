
// Variabila este volatile deoarece intr-un program embedded real
// ar putea fi modificata in afara fluxului normal al programului.
// De exemplu, ar putea fi modificata dintr-o intrerupere cand se apasa un buton.
// volatile ii spune compilatorului sa citeasca mereu valoarea din memorie.
volatile unsigned char button_pressed_flag = 0u;

static unsigned int get_call_count(void)
{
    // Variabila este static deoarece vreau sa isi pastreze valoarea
    // intre apelurile functiei.
    // Ea este initializata o singura data.
    // Fara static, variabila s-ar crea din nou la fiecare apel.
    static unsigned int call_counter = 0u;

    call_counter++;

    return call_counter;
}

int main(void)
{
    volatile unsigned int current_count = 0u;

    while (1)
    {
        current_count = get_call_count();

        // Daca flag-ul este setat, il sterg.
        // Intr-o aplicatie reala, flag-ul ar putea fi setat dintr-o intrerupere.
        if (button_pressed_flag != 0u)
        {
            button_pressed_flag = 0u;
        }
    }
}