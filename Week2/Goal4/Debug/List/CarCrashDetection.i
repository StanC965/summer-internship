#line 1 "D:\\Mircea\\Marqurdt\\summer-internship\\Week2\\Goal4\\CarCrashDetection.c"
#line 1 "D:\\Mircea\\Marqurdt\\summer-internship\\Week2\\Goal4\\CarCrashDetection.h"



#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"
 
 





  #pragma system_include


#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\ycheck.h"
 
 

 


  #pragma system_include















 





#line 12 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"
#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"
 
 





  #pragma system_include


 









 


 


 




 
#pragma rtmodel = "__dlib_version", "6"

 





 
#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"



























 





  #pragma system_include


 
#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Config_Normal.h"
 
 





  #pragma system_include


#line 18 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Config_Normal.h"

#line 40 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"
   
#line 47 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"

 
#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Product.h"
 
 



























 

#line 43 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Product.h"

#line 51 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Product.h"

#line 61 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Product.h"

#line 70 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Product.h"
























#line 109 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Product.h"



#line 51 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"











 



















 














 


























 








 






 

#line 153 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"









 

#line 172 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"













 
















 








 
#line 223 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"













 
















 





















 














 








 
#line 311 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"








 
#line 331 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"






 








 















 








 
















 




#line 400 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"





 

#line 414 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"

#line 446 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"







 
#line 461 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"




 









 







 







 
















 


   
#line 518 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"




 










 

#line 542 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"






 










 













 

#line 582 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\DLib_Defaults.h"




 












#line 43 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

















 

#line 81 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

 






 
#line 99 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"













 


   
#line 124 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"





 
#line 142 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"




 
#line 191 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

#line 199 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

#line 206 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

 


 




 





  typedef unsigned long _Wchart;
  typedef unsigned long _Wintt;
#line 238 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

 


 
typedef unsigned int     _Sizet;

 
typedef signed char   __int8_t;
typedef unsigned char  __uint8_t;
typedef signed int   __int16_t;
typedef unsigned int  __uint16_t;
typedef signed long int   __int32_t;
typedef unsigned long int  __uint32_t;

   typedef signed long long int   __int64_t;
   typedef unsigned long long int  __uint64_t;




typedef signed int   __intptr_t;
typedef unsigned int  __uintptr_t;

 
typedef struct _Mbstatet
{  
#line 272 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"
    __uint32_t _Wchar;     
    __uint32_t _State;     


#line 299 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"
} _Mbstatet;






 


 





  typedef struct __va_list
  {
    char  *_Ap;
  } __va_list;
  typedef __va_list __Va_list;
















 
typedef struct
{



    __int32_t _Off;     

  _Mbstatet _Wstate;
} _Fpost;





 


 

  
   
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_StaticGuard(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_StaticGuard(void);

#line 373 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

  typedef void *__iar_Rmtx;

  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Initdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Dstdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Lockdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlockdynamiclock(__iar_Rmtx *);

  
#line 406 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"

#line 446 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\yvals.h"






 
#line 13 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"
#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\ysizet.h"
 
 





  #pragma system_include


#line 1 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\ycheck.h"
 
 

 


  #pragma system_include















 





#line 12 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\ysizet.h"


 



  typedef _Sizet size_t;




typedef unsigned char __tiny_size_t; typedef unsigned int __near_size_t; typedef unsigned char __tinyflash_size_t; typedef unsigned int __flash_size_t; typedef unsigned int __eeprom_size_t; typedef unsigned char __io_size_t; typedef unsigned int __ext_io_size_t; typedef unsigned long __generic_size_t;




#line 14 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"

 

#pragma rtmodel="__dlib_full_locale_support",   "0"



#line 30 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"
  
    __intrinsic __nounwind size_t __iar_Mbcurmax(void);
  




 













 


  typedef _Wchart wchar_t;


typedef struct
{  
  int quot;
  int rem;
} div_t;

typedef struct
{  
  long quot;
  long rem;
} ldiv_t;


  typedef struct
  {  
    long long quot;
    long long rem;
  } lldiv_t;


#line 88 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"

 
  
  __intrinsic __nounwind int             atexit(void (*)(void));

    __intrinsic __nounwind          int  at_quick_exit(void (*)(void)) ;
    __intrinsic __noreturn __nounwind void _Exit(int) ;
    __intrinsic __noreturn __nounwind void quick_exit(int) ;

  __intrinsic __noreturn __nounwind void   exit(int);
   __intrinsic __nounwind        char * getenv(const char *);
  __intrinsic __nounwind          int    system(const char *);




               __intrinsic __nounwind void *    aligned_alloc(size_t, size_t);

          __intrinsic __noreturn __nounwind void  abort(void) ;
  _Pragma("function_effects = no_state, always_returns")     __intrinsic __nounwind int       abs(int);
               __intrinsic __nounwind void *    calloc(size_t, size_t);
  _Pragma("function_effects = no_state, always_returns")     __intrinsic __nounwind div_t     div(int, int);
               __intrinsic __nounwind void      free(void *);
  _Pragma("function_effects = no_state, always_returns")     __intrinsic __nounwind long      labs(long);
  _Pragma("function_effects = no_state, always_returns")     __intrinsic __nounwind ldiv_t    ldiv(long, long);

    _Pragma("function_effects = no_state, always_returns")   __intrinsic __nounwind long long llabs(long long);
    _Pragma("function_effects = no_state, always_returns")   __intrinsic __nounwind lldiv_t   lldiv(long long, long long);

  _Pragma("function_effects = no_state, always_returns")     __intrinsic __nounwind double    fabs(double);
  _Pragma("function_effects = no_state, always_returns")     __intrinsic __nounwind float     fabsf(float);
  _Pragma("function_effects = no_state, always_returns")     __intrinsic __nounwind long double fabsl(long double);
               __intrinsic __nounwind void *    malloc(size_t);
  _Pragma("function_effects = no_write(1), always_returns")    __intrinsic __nounwind int       mblen(const char *, size_t);

    _Pragma("function_effects = no_read(1), no_write(2), always_returns")  __intrinsic __nounwind size_t mbstowcs(wchar_t *restrict,
                                                const char *restrict, size_t);
    _Pragma("function_effects = no_read(1), no_write(2), always_returns") __intrinsic __nounwind   int    mbtowc(wchar_t *restrict,
                                              const char *restrict, size_t);

               __intrinsic __nounwind int    rand(void);
               __intrinsic __nounwind void   srand(unsigned int);
               __intrinsic __nounwind void * realloc(void *, size_t);

               __intrinsic __nounwind void * __iar_realloc_in_place(void *, size_t);

  _Pragma("function_effects = no_write(1), no_read(2), always_returns") __intrinsic __nounwind long          strtol(const char *restrict,
                                                 char **restrict, int);
  _Pragma("function_effects = no_write(1), no_read(2), always_returns") __intrinsic __nounwind unsigned long strtoul(const char *, char **, int);

    _Pragma("function_effects = no_read(1), no_write(2), always_returns")  __intrinsic __nounwind size_t wcstombs(char *restrict,
                                               const wchar_t *restrict,
                                               size_t);
    _Pragma("function_effects = no_read(1), always_returns")     __intrinsic __nounwind int    wctomb(char *, wchar_t);


    _Pragma("function_effects = no_write(1), no_read(2), always_returns") __intrinsic __nounwind long long strtoll(const char *, char **, int);
    _Pragma("function_effects = no_write(1), no_read(2), always_returns") __intrinsic __nounwind unsigned long long strtoull(const char *,
                                                          char **, int);


#line 167 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"


  typedef int _Cmpfun(const void *, const void *);
  _Pragma("function_effects = no_write(1,2), always_returns")  __intrinsic void * bsearch(const void *,
                                                       const void *, size_t,
                                                       size_t, _Cmpfun *);
                __intrinsic void   qsort(void *, size_t, size_t,
                                                     _Cmpfun *);
               __intrinsic void     __qsortbbl(void *, size_t,
                                                          size_t, _Cmpfun *);
  _Pragma("function_effects = no_write(1), always_returns")    __intrinsic __nounwind double             atof(const char *);
  _Pragma("function_effects = no_write(1), always_returns")    __intrinsic __nounwind int                atoi(const char *);
  _Pragma("function_effects = no_write(1), always_returns")    __intrinsic __nounwind long               atol(const char *);

     _Pragma("function_effects = no_write(1), always_returns") __intrinsic __nounwind long long        atoll(const char *);
     _Pragma("function_effects = no_write(1), no_read(2), always_returns") __intrinsic __nounwind float         strtof(const char *restrict,
                                                    char **restrict);
     _Pragma("function_effects = no_write(1), no_read(2), always_returns") __intrinsic __nounwind long double   strtold(const char *, char **);

  _Pragma("function_effects = no_write(1), no_read(2), always_returns") __intrinsic __nounwind double           strtod(const char *restrict,
                                                    char **restrict);

    _Pragma("function_effects = no_state, always_returns")   __intrinsic __nounwind int              __iar_DLib_library_version(void);




  
  #pragma inline=no_body
  int abs(int i)
  {       
    return i < 0 ? -i : i;
  }

  #pragma inline=no_body
  long labs(long i)
  {  
    return i < 0 ? -i : i;
  }


    #pragma inline=no_body
    long long llabs(long long i)
    {  
      return i < 0 ? -i : i;
    }

  


#line 274 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"

#line 313 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"

#line 324 "D:\\Mircea\\Marqurdt\\logic\\avr\\inc\\dlib\\c\\stdlib.h"












 
#line 5 "D:\\Mircea\\Marqurdt\\summer-internship\\Week2\\Goal4\\CarCrashDetection.h"




extern unsigned char GetCarCrashDetectionStatus(void);

#line 2 "D:\\Mircea\\Marqurdt\\summer-internship\\Week2\\Goal4\\CarCrashDetection.c"

static unsigned char __CarCrashEventStatus;

unsigned char GetCarCrashDetectionStatus(void)
{
  __CarCrashEventStatus=(0u);
   
  __CarCrashEventStatus=rand()%2; 
  return __CarCrashEventStatus;
}
