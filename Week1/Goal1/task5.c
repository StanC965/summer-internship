#define MAX(i, limit) do \
{ \
    i++;\
} while(i < limit)
//pentru a nu se bloca in while am mai pus acolo conditia
void main(void)
{
  //am definit i ul pentru ca altfel compara mereu 0 cu 3
  
    int i = 0;
    MAX(i,3);
}