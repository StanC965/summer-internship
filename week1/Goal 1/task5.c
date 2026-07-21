#define MAX(i, limit) do \
{ \
    if (i < limit) \
    { \
        i++; \
    } \
} while(1)
//nu va rula pentru ca primul parametru de la MAX este o constanta,
//si daca am schimba asta si am face o variabila
//dupa am ramane blocat intr-o bucala infinita din cauza lui while(1)
void main(void)
{
    MAX(0,3);
}
