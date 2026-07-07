//153 
#if MAX == 1
#define VAR 4
#else
#define VAR 5
#endif

void main( void )
{
    int test = VAR; 
}

// MAX is treated as 0 because it is not defined => test = var = 5