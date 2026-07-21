For this problem i added a function  that is supposed to test the bitfield and bitmask way:


void test_bitfield_vs_bitmask(void) {

  PORTB_Bit0=1;

  PORTB |= 0x07;  
}



  PORTB_Bit0=1;
test_bitfield_vs_bitmask:
  00049A   9A28              SBI     0x5,0  // bitfield   49C-49A = 2 bytes of memory   and 2 clocks  




    PORTB |= 0x07;                           //bitmask    
  00049C   B105              IN      R16,PORTB        2 bytes    1 clock
  00049E   6007              ORI     R16 ,0x07         2 bytes    1 clock
  0004A0   B905              OUT     PORTB,R16        2 bytes    1 clock

  de aici rezulta urmatoarele :  un bitmask de 3 operatii ocupa 6 bytes de memorie si 3 clocks 
  in timp ce 3 bitfields ar ocupa 6 bytes de memorie si 6 clocks ,de aici rezulta ca desi spatiul de memorie ocupat e acelasi , viteza la bitmask e dubla 


