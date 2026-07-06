//SFR_B_N(0x25, TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
//offsetul este primul dupa vine registrul pe care il am , apoi sunt bitii registrului
//Concluzia la SFR_B_N(0xB1,TCCR2B,FOC2A,FOC2B,-,-,WGM22,CSS22,CSS21,CSS20)


/*
SFR_B_N(0x08,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)
adresa sa, registrul , cel mai sumnificativ bit, ..., cel mai nesemnificativ
SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)
adresa sa, registrul , cel mai sumnificativ bit, ..., cel mai nesemnificativ
SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
adresa sa, registrul , cel mai sumnificativ bit, ..., cel mai nesemnificativ

*/