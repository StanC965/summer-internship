# 1.What pin is OC0A? #
Preluat din datasheet:" OC0A: Output Compare Match A output. The PB3 pin can serve as an external output for the
Timer/Counter0 Output Compare. The pin has to be configured as an output (DDRB3 set “1”)
to serve this function. The OC0A pin is also the output pin for the PWM mode timer function."

Ce inseamna? :

la fiecare ciclu de ceas hardware-ul compara timer 0 cu valoarea din OCR0A, daca sunt egale se pune 1  pe acest bit
Programul se poate folosi de acest bit pentru a genera o intrerupere , dupa care il pune iara in 0 pentru a urmari urmatoarea egalare.

# 2.Which led is connected to it ? #

Din datasheet:

"PB3 AIN1 (Analog Comparator Negative Input)
OC0A (Timer/Counter 0 Output Compare Match A Output)
PCINT11 (Pin Change Interrupt 11)"

Ce inseamna?: Pinul este conectat la led-ul pwm de pe placa IOXplained ,acesta difera fata de un simplu led prin faptul ca ruleaza pe baza duty-cycle-urilor 


# 3.Using the Waveform Generator toggle the OC0A pin on match with OCR0A=127. Within the same program, but from inside ISR code, toggle another pin which has LED connected. What do you observe with respect to the two LEDs blinking behavior? #

Putem face asta prin setarea pin-ului 6 pe 1 din TCCR0A;
acuma la fiecare compare match intre timer si OCR0A se va emite un semnal conectat la led-ul 4 ceea ce determina acelasi efect cu led-zero doar ca principiul din spate e diferit:

# LED_ZERO #  
e controlat de software,asta determina o latenta mai mare
# LED_FOUR #
este controalt hardware ,asta determina a latenta foarte mica

Din acest motiv observ ca fesi ambele clipesc la aceeasi frecventa, LED_FOUR este defazat in fata comparativ cu LED_ZERO cu aproximativ 180 de grade (opozitie de faza) adica unda la led-ul conectat hardware a inceput mai repede

# 4.if they are out-of-synch, make them to be turned on/off synchronously (both on, both off) #

 if(on!=0)
      led_TOGGLE(LED_ZERO);   //
    on++;

    pur si simplu dam skip la prima aprindere,astfel intarziem unda 1 suficient de mult cat sa intre in faza cu unda 2 .
    
# 5.How much real time (use ms/miliseconds) can be measured with OCR0A = 127? #

127 * 1024 / 1000000 = 0.130048 s adica  *131ms*  unde 1024 e prescale

# 6.What other real timings you can measure having the same OCR0A = 127? #

putem schimba prescaler-ul adica :
127 * 1024 / 1000000 =130.048ms
127 * 256 / 1000000 =32.512ms
127 * 64 / 1000000 =8.128ms
127 * 8 / 1000000 =  1.016ms
127 * 1 / 1000000 =  127μs
