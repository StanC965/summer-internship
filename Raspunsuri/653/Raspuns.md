
# BINARY OPERATIONS #

gpio_set_pin                    CODE   0x00000364  Pub   Code  gpio             

gpio_reset_pin                  CODE   0x00000378  Pub   Code  gpio   
                                                                           void gpio_set_pin(volatile unsigned char *PORT, gpio_uint8_t bit)
                                                                                                {   
                                                                                                     *PORT |= (1 << bit);  
                                                                                                }

                                                                        void gpio_reset_pin(volatile unsigned char *port, gpio_uint8_t bit)
                                                                                        {
                                                                                            (*port) &= ~(1 << bit);                 
                                                                                        }
                                                                                       
gpio_toggle_pin                 CODE   0x0000038E  Pub   Code  gpio

gpio_set_direction              CODE   0x000003A2  Pub   Code  gpio

# SWITCH IMPLEMENTATION #

button_get_press_sw0            CODE   0x00000384  Pub   Code  button
gpio_set_pin                    CODE   0x00000390  Pub   Code  gpio
gpio_reset_pin                  CODE   0x000003E6  Pub   Code  gpio
_..X_EEPROM_END                 CODE   0x000003FF  Pub         ?ABS_ENTRY_MOD [0]
gpio_toggle_pin                 CODE   0x0000043C  Pub   Code  gpio
                                                                                                     
       switch(bit) {
        case 0: *PORT |= 0x01; break;
        case 1: *PORT |= 0x02; break;
        case 2: *PORT |= 0x04; break;
        case 3: *PORT |= 0x08; break;
        case 4: *PORT |= 0x10; break;
        case 5: *PORT |= 0x20; break;
        case 6: *PORT |= 0x40; break;
        case 7: *PORT |= 0x80; break;
    }

   Ref by:   Segment part 18
      gpio_set_pin         0x00000390  Pub  Ref by:   adc_init_LIGHT (adc)
                                                      adc_start_conversie (adc)
                                                      buttons_initialize (button)
                                                      led_Set (led)
                                                      setup (main)
                                                      pwm_init_LED (pwm)
    --------------------------------------------------
       Segment part 12, CODE
       Address: CODE 0x000003E6 Size: 0x56 Align: 2(1)
       Ref by:   Segment part 19
      gpio_reset_pin       0x000003E6  Pub  Ref by:   led_Reset (led)
                                                      leds_initialize (led)
                                                      adc_init_LIGHT (adc)



functions proposed for measuring	implementation with switch — CODE	implementation with switch — DATA*	implementation with binary operators — CODE	implementation with binary operators — DATA*

functions proposed for measuring :                                                    gpio_set_pin               AND               gpio_reset_pin     
                                                                                                                  |
implementation with switch — CODE                                                       0x56 = 86bytes            |                 0x56 = 86bytes  
implementation with switch — DATA*                                                          0                     |                  0
implementation with binary operators — CODE	                                               0x14=20                |                 0X16=22BYTES       
implementation with binary operators — DATA*                                                 0                    |                  0              