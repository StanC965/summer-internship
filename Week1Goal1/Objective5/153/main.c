// 153 - undefined macro in #if is treated as 0
#if MAX == 1
#define VAR 4
#else
#define VAR 5
#endif
void main( void )
{
    int test = VAR;
}
// MAX is not defined, so it is treated as 0 => #if is false => VAR = 5
