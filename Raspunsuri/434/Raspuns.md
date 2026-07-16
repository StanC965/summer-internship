# 1.Do the math calculations for minimum and maximum of real time you can natively measure with CTC MODE, all prescalers considered. #
# 2.How can you extend the maximum real time measured in CTC MODE? #
1.
 minimum : OCR0A =0;
 maximum : OCR0A=TOP=255;

 prescalers[5] :  1,8,64,256,1024

 answer:  Time=(OCR0A+1)*prescaler[i]/Fclock ,i este intre 0 si 4 :

# MIN: #
0+1 =1

 deci i=0:1/1000000=10^(-6) secunde ( o microsecunda)
 i=1 :  8/1000000=8 microsecunde
 i=2 :  64/1000000=64 microsecunde
 i=3 :  256/1000000=256 microsecunde=0.256 milisecunde
 i=4 :  1024/1000000= 1.024 milisecunde

# MAX: # 
 (255+1)prescaler[i]/Fclock 

 i=0 :  256/1000000=256 microsecunde=0.256 milisecunde
 i=1 :  256*8 /1000000= 0.256 ms * 8 = 2.048 milisecunde
 i=2 :  256*64/1000000= 2.048 secunde * 8 = 16.384 milisecunde
 i=3 :  256*256/1000000= 16.384 * 4 = 65.536 milisecunde
 i=4:   256*1024/1000000= 65.536 *4 = 262.144 milisecunde 


Pentru un timer de 16 bits pur si simplu inlocuim la MAX acel 255 cu 65555  ,MIN ramane identic


2. Pentru a extinde timpul in CTC putem face urmatoarele lucruri:
Sa alegem cu prescaler mai mare
sa scadem frecventa clock-ului
sa numaram match-urile (la fel ca la numaratul overflow-urilor de la modul normal) si facem o actiune numai la un anumit numar de match-uri
sa alegem OCR0A sa fie egal cu TOP
sa folosim un timer de 16 bits care va mari acel TOP
