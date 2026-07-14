# Week: 1 - Goal : 2


## Objective 6: Architecting S.O.S - polling technique
---

### Task Checklist & Results

| Task ID   | Type         | Status
| :---      | :---         | :--- 
| **[261]** | `CORE`       | [x] Completed 
| **[262]** | `CORE`       | [x] Completed 
| **[263]** | `STRETCH`    | [] Completed 

---

#### Task 261
> **Question/Prompt:** Yet another step towards writing a more professional code is abstractization. Let us introduce a new LED0 behavior: SOS sequence, which in MORSE language is 3 points, 3 lines, 3 points . . . - - - . . .. Write code to turn on/off the LED0 simulating the SOS signal. First build the POINT and the LINE (with appropriate functions) which are nothing else but abstract behaviors of the LED0 on/off basic functionalities (so the POINT appropriate function will call the LED on/off functions). Then build the SOS behavior (creating appropriate functions) which behavior is nothing else but yet another abstract luminous behavior of the same LED0, build upon the POINT and LINE behaviors previously created (thus calling the functions implementing POINT and LINE).

> **Answer/Explanation:**
> I created the sos module, which contains the function for the sos sequence:

**`sos.c`** 
```c
void sos_play(led_id_t led_id){
    sos_point(led_id);
    sos_point(led_id);
    sos_point(led_id);

    delay(SECOND);

    sos_line(led_id);
    sos_line(led_id);
    sos_line(led_id);

    delay(SECOND);
    
    sos_point(led_id);
    sos_point(led_id);
    sos_point(led_id);
}
```

> This function uses two static functions from the sos module:

**`sos.c`** 
```c
static void sos_point(led_id_t led_id){
    led_blink_custom(led_id, 1, SECOND / 2, SECOND / 2);
}

static void sos_line(led_id_t led_id){
    led_blink_custom(led_id, 1, SECOND * 2, SECOND / 2);
}
```

> I chose to create a custom led blinking function that makes the led blink repeateadly for a number of times, with customizable durations between LED on and off.

**`led.c`** 
```c
void led_blink_custom(led_id_t led_id, uint8_t times, uint32_t on_time, uint32_t off_time){
    if(led_id < LED_COUNT){
        for(uint8_t i = 0; i < times; i++){
            led_power_on(led_id);
            delay(on_time);

            led_power_off(led_id);
            delay(off_time);
        }
    }
}
```

---

#### Task 262
> **Question/Prompt:**  Code to launch the SOS signaling at the press of the SW0 button. The complete SOS sequence runs indefinitely with a 1 second break between the smaller sequences (see graph).

> **Answer/Explanation:**
> I modified the code in main and reintroduced the logic for button pressing, but this time when the button is pressed the sos sequence starts playing, and between each full sos sequence there is a 1 second time delay.

**`main.c`** 
```c
 uint8_t button_pressed;
  
  while(1){
    button_pressed = button_read(BUTTON_ONBOARD);
    
    if(!button_pressed){
      delay(10 * MILISECOND);
      
      button_pressed = button_read(BUTTON_ONBOARD);
      
      if(!button_pressed){
        while(1){
          sos_play(LED_ONBOARD);
          delay(SECOND);
        }
      }
    }
  }
```

> Additionaly, I modified the logic of the sos module, and introduce a `TIME_UNIT`, to reproduce the effect of an sos signal better.

**`sos.h`** 
```c
#define TIME_UNIT (SECOND / 2U)
```

**`sos.c`** 
```c
static void sos_point(led_id_t led_id){
    led_blink_custom(led_id, 1, TIME_UNIT, TIME_UNIT);
}

static void sos_line(led_id_t led_id){
    led_blink_custom(led_id, 1, 3 * TIME_UNIT, TIME_UNIT);
}

void sos_play(led_id_t led_id){
    // sos points

    // wait 1 second between sequences
    delay(2 * TIME_UNIT);

    // sos lines
    
    // wait 1 second between sequences
    delay(2 * TIME_UNIT);
    
    // sos points
}
```

---