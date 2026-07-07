#define MAX(i, limit) do \
{ \
    if (i < limit) \
    { \
        i++; \          // 0 ++ 
    } \
} while(1)

void main(void)
{
    MAX(0,3);
}

// eroor : expression must be a modifiable lvalue 
