# How i implemented the solution for 741 # 

Initially i thought about doing it like this: 
1.press buttons on OLED1 ->> transmit to main board,then main board utilises the loophole on IO1,which transmits to main board,main board turns off and on  the LEDs on OLED1,but it didn't seem to make sense to me so i found a better way:

Since there are one  rx and one  tx pin on OLED board(header EXT 1) , precisely PINs 13 and 14 , i could form a loophole with these two to create my own serial communication . But the whole OLED board was already connected (occupying redundantly PIN 13 and PIN 14) so i took 19 female-male jumper wires and 1 female-female jumper wire(for the loophole) and connected the main board to the OLED, it worked fine. Now once data is transmitted the moment it is read on PIN 13 the main board executes those actions(set,reset,toggle), those actions are sent as hex codes of course defined inside the header module of the UART, specially made by me.