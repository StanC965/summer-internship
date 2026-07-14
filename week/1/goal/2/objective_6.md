# Week: 1 - Goal : 2


## Objective 6: Architecting S.O.S - polling technique
---

### Task Checklist & Results

| Task ID   | Type         | Status
| :---      | :---         | :--- 
| **[261]** | `CORE`       | [x] Completed 
| **[262]** | `CORE`       | [x] Completed 
| **[263]** | `STRETCH`    | [x] Completed 

---

#### Task 261
> **Question/Prompt:** Yet another step towards writing a more professional code is abstractization. Let us introduce a new LED0 behavior: SOS sequence, which in MORSE language is 3 points, 3 lines, 3 points . . . - - - . . .. Write code to turn on/off the LED0 simulating the SOS signal. First build the POINT and the LINE (with appropriate functions) which are nothing else but abstract behaviors of the LED0 on/off basic functionalities (so the POINT appropriate function will call the LED on/off functions). Then build the SOS behavior (creating appropriate functions) which behavior is nothing else but yet another abstract luminous behavior of the same LED0, build upon the POINT and LINE behaviors previously created (thus calling the functions implementing POINT and LINE).

> **Answer/Explanation:**
> I created the SOS module, which contains the function for the SOS sequence:

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

> This function uses two static functions from the SOS module:

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
> I modified the code in main and reintroduced the logic for button pressing, but this time when the button is pressed the SOS sequence starts playing, and between each full SOS sequence there is a 1 second time delay.

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

> Additionaly, I modified the logic of the SOS module, and introduce a `TIME_UNIT`, to reproduce the effect of an SOS signal better.

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
    // SOS points

    // wait 1 second between sequences
    delay(2 * TIME_UNIT);

    // SOS lines

    // wait 1 second between sequences
    delay(2 * TIME_UNIT);
    
    // SOS points
}
```

---

#### Task 263
> **Question/Prompt:**  Make the SOS message begin when the SW0 button is pressed for the first time. At the second press of the SW0 button, the SOS message must stop. At the next press, SOS starts, and so on. Depending on your "resolution" to poll the state of the SW0 button (e.g. after each point, or after each letter) you might need to hold down pressed SW0 for a longer period of time or less, so that it can be read correctly.

> **Answer/Explanation:**
> In the original code, the microcontroller used blocking delays while the SOS message was playing. This meant that the CPU did not know if the button was pressed in this time period, because it was occupied counting down time. 
>
> In order for the CPU to be aware of button presses, even if the SOS sequence started, I changed the logic from blocking to non-blocking, using polling.

**`main.c`**
```c
volatile uint8_t sos_active = 0;

  while(1){
    button_pressed = button_read(BUTTON_ONBOARD);
    
    if(!button_pressed){
      delay(10 * MILISECOND);
      
      if(!button_read(BUTTON_ONBOARD)){
        // button was confirmed to be pressed
        // toggle the SOS execution flag
        sos_active = !sos_active;
        
        if(!sos_active){
          // if the user turned off SOS by pressing the button, turn of LED
          led_power_off(LED_ONBOARD);
        }
        
        while(!button_read(BUTTON_ONBOARD)){
          // prevent rapid re-triggering if the user keeps holding the 
          // physical button down
          delay(10 * MILISECOND);
        }
      }
    }
    
    if(sos_active){
      // SOS flag active, run current step of the SOS sequence
      sos_update(LED_ONBOARD);
  }
  // delay the loop by exactly 1 milisecond per iteration
  delay(1 * MILISECOND);
 }
```

> I also added a new function that implements the SOS sequence, called `sos_update`.
> This function keeps track of the current step of the SOS sequence by using a static variable to save the values between function calls.

**`sos.c`**
```c
void sos_update(led_id_t led_id){
  static uint8_t current_step = 0;
  static uint32_t state_timer_ms = 0;
  
  // extract the SOS letter associated for the current step
  step_t step = sos_sequence[current_step];
  
  // the SOS letter can be have 2 LED states:
  if(step.led_state){
    // LED state ON
    led_power_on(led_id);
  } else{
    // LED state OFF
    led_power_off(led_id);
  }
  
  // increment the timer of the current state by 1 milisecond
  state_timer_ms += MILISECOND;
  
  uint32_t target_duration = step.duration_units * TIME_UNIT;
  // use the computed target duration to check if current step has reached its time duration
  if(state_timer_ms >= target_duration){
    // if target duration is done
    // reset the timer
    state_timer_ms = 0;
    // go to next state of SOS letter
    current_step++;
    
    if(current_step >= SOS_TOTAL_STEPS){
      // if we reach the last state of the last letter of SOS 
      // reset to initial letter state
      current_step = 0;
    }
  }
  
}
```

> Additionally, I used an array which consists of LED states and their respective duration units.

**`sos.h`**
```c
typedef struct{
  uint8_t led_state;
  uint8_t duration_units;
}step_t;
```

**`sos.c`**
```c
const step_t sos_sequence[] = {
    // S1 - ON & OFF
    {1, 1}, {0, 1},
    // S2 - ON & OFF
    {1, 1}, {0, 1},
    // S3 - ON 
    {1, 1}, 
    // PAUSE BETWEEN LETTERS
    {0, 2},
    
    // O1 - ON & OFF
    {1, 3}, {0, 1},
    // O2 - ON & OFF
    {1, 3}, {0, 1},
    // O3 - ON 
    {1, 3},
    // PAUSE BETWEEN LETTERS
    {0, 2},
    
    // S4 - ON & OFF
    {1, 1}, {0, 1},
    // S5 - ON & OFF
    {1, 1}, {0, 1},
    // S6 - ON &
    {1, 1},

    // PAUSE BETWEEN WORDS
    {0, 7},
}
```

> Shortly, because of polling the microcontroller is constantly checking the state of the button inside a fast loop, instead of waiting:
> - the `while(1)` loop spins incredibly fast (once every single milisecond) and after every loop cycle the CPU interrogates the hardware via `button_read`. Because of this, the CPU will catch a button press very fast.
> - since the `sos_update` function is non-blocking, the CPU is never trapped. It instantly returns to the top of the loop to read the button again.




