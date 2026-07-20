# 622 — CORE — Check on the boards (user guides, schematics) to what pins you can output a PWM signal and if those pins have LEDs connected !!! Not all pins can support/output PWM signals. #

Pe baza la imaginea prezentata in acest folder putem deduce numarul pinilor care pot contine functionalitatea de PWM be baza existentei unui modul de comparatie cu un OCRxA sau OCRxB ,unde x este  1 sau 2 :

Timer 0 (8-bit): PB3 si PB4
Timer 1 (16-bit): PD4 si PD5
Timer 2 (8-bit): PD6 si PD7
Timer 3 (16-bit): PB6 si PB7
Timer 4 (16-bit): PC4 si PE4

Dintre toate singurii pini care sunt conectat la niste led-uri sunt :
PB3 (IO xplained) la acel LED
PD4 si PD5 care sunt conectati la 8 si 7 adica la LED2 si LED1 ,deci PD5->LED1  si PD4->LED2 

chestiile astea le-am determinat pe baza la schematicele hardware