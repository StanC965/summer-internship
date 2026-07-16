 # On timer TC1, 16 bits counter, implement and document the minimum and the maximum real time you can obtain using this timer. The same for minimum and maximum signal frequencies when applied to a toggling LED. What is the advantage of using a timer on 16 bits instead of a timer on 8 bits? #

 minimum : OCR1A =0;
 maximum : OCR1A=TOP=65535;

 prescalers[5] :  1,8,64,256,1024

 answer:  Time=(OCR1A+1)*prescaler[i]/Fclock ,i este intre 0 si 4 :

# MIN: #
0+1 =1

 deci i=0:1/1000000=10^(-6) secunde ( o microsecunda)
 i=1 :  8/1000000=8 microsecunde
 i=2 :  64/1000000=64 microsecunde
 i=3 :  256/1000000=256 microsecunde=0.256 milisecunde
 i=4 :  1024/1000000= 1.024 milisecunde

# MAX: # 
 (65535+1)prescaler[i]/Fclock 

 i=0 :  65536/1000000=2^16/10^6= 0.065556 secunde =65.556 milisecunde
 i=1 :  65536*8 /1000000= 524288 microsecunde= 0.524288 secunde
 i=2 :  65536*64/1000000= 419400 microsecunde=4.19400 secunde
 i=3 :  65536*256/1000000= 1677700 secunde=16.7770 secunde
 i=4:   65536*1024/1000000=67.10 secunde


MIN time= 0 microsecunda => Tmin= 1/(10^6) => FREQ MIN=>   1/(2*Tmin=) 0.5 Mhz

MAX time= 67.10 secunde => Tmax= 1/67.10 =0.01490 secunde =>f=1/(2*Tmax​)=  2$f_{min} = *0.00745Hz*

1.Avantajul unui timer pe 16 bits este faptul putem lucra cu durate mai mari de masura ,ceea ce ne permite sa avem intreruperi exacte carenu necesita numararea unui contor de overflow,ceea ce ne permite mai mult timp fara interventie software.
2.De asemenea prezitna si functia de input capture,care ne ajuta sa masuram duratele dintre doua frecvente diferite spre exemplu 
3.Are rezolutie mai mare pentru PWM => precizie mai mare
4.e mai mare sansa sa ai o frecventa exacta ,fara rotrunjiri care ar provoca desincronizari in timp