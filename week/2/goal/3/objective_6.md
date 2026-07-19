# Week: 2 - Goal : 3


## Objective 6: Ambient Light Application

---

### Task Checklist & Results

| Task ID   | Type       | Status 
| :---      | :---       | :---                    
| **[361]** | `CORE`     | [x] Completed 
| **[362]** | `CORE`     | [x] Completed 
| **[363]** | `STRETCH`  | [x] Completed 
| **[364]** | `OPTIONAL` | [x] Completed 
| **[365]** | `OPTIONAL` | [x] Completed 
| **[366]** | `OPTIONAL` | [x] Completed 

--- 

#### Task 361
> **Question/Prompt:** Establish the middle point of the readings range and turn on LED0 if readings are above that point.

> **Answer/Explanation:**

**`main.c`**
```c
extern volatile uint8_t light_sensor_value;

#define LIGHT_SENSOR_MIDPOINT (127U)

void main(void)
{
  led_init();
  adc_init();

  __enable_interrupt();

  while (1)
  {
    adc_start_conversion();
    // if the sensor value is lower than the constant
    // then the sensor intercepted light
    if (light_sensor_value < LIGHT_SENSOR_MIDPOINT)
    {
      led_power_on(LED_ONBOARD);
    } // its dark, turn off the light
    else
    { 
      led_power_off(LED_ONBOARD);
    }
  }
}
```

--- 

#### Task 362
> **Question/Prompt:** Take 4 readings intervals (1 corresponding to complete dark, 2 semi-dark, 3 semi-light, 4 full light) and turn on LED1,2,3 as follows:

| ADC readings interval  | Light intensity correspondence     | LEDs state
| :---                   | :---                               | :---                    
| 1                      | full dark                          | all off
| 2                      | semi-dark                          | LED1 on
| 3                      | semi-light                         | LED1,2 on
| 4                      | full light                         | LED1,2,3 on

> **Answer/Explanation:**

**`main.c`**
```c
extern volatile uint8_t light_sensor_value;

#define LIGHT_SENSOR_FULL_DARK  (255U)
#define LIGHT_SENSOR_SEMI_DARK  (170U)
#define LIGHT_SENSOR_SEMI_LIGHT (85U)
#define LIGHT_SENSOR_FULL_LIGHT (0U)

void main(void)
{
  led_init();
  adc_init();

  __enable_interrupt();

  while (1)
  {
    adc_start_conversion();
    // FULL LIGHT
    if (light_sensor_value < LIGHT_SENSOR_SEMI_LIGHT)
    {
      led_power_on(LED_OLED1_1);
      led_power_on(LED_OLED1_2);
      led_power_on(LED_OLED1_3);
    }
    //SEMI LIGHT
    else if (light_sensor_value >= LIGHT_SENSOR_SEMI_LIGHT && light_sensor_value < LIGHT_SENSOR_SEMI_DARK)
    {
      led_power_on(LED_OLED1_1);
      led_power_on(LED_OLED1_2);
    }
    // SEMI DARK
    else if (light_sensor_value >= LIGHT_SENSOR_SEMI_DARK && light_sensor_value < LIGHT_SENSOR_FULL_DARK)
    {
      led_power_on(LED_OLED1_1);
    }
    // FULL DARK
    else
    {
      led_power_off(LED_OLED1_1);
      led_power_off(LED_OLED1_2);
      led_power_off(LED_OLED1_3);
    }
  }
}
```

--- 

#### Task 363
> **Question/Prompt:** Now it's time to be interested of another key performance indicator in embedded systems: power consumption. On the main board, near the SW0 button, there is a current measurement header. How you can measure the current in a circuit? Since we do not have in our Internship online setup the possibility to measure the current consumption we will rely on datasheet information:
>
> - disable the digital input buffer (if it is powered then it consumes current) for the analog pin (the pin with connected sensor to it)
> - enable the ADC peripheral only when you are wishing to make a conversion, otherwise shut it down (disable)

> **Answer/Explanation:**
> To measure the current in a circuit we use an ammeter connected in series with the load. 
> Alternatively, we can measure the voltage drop across a known shunt resistor places accross the header pins and use Ohm's law to calculate the current consumption. 

--- 

#### Task 364
> **Question/Prompt:** Implement the 10bit convertion resolution and check if you observe any sensitivity to ADC. Some of the questions you might have: What changes should I do to register settings to implement 10bit resolution? How can I get the result now? Does data type change? Would be easier to have the result right aligned or left aligned? Should I change the prescaler as chapter 27.4 is telling me?

> **Answer/Explanation:**
> Answering the questions:
> -  I need to change the alignment bit inside ADMUX. This currently sets the ADC left adjust bit. In order to read the full 10 bit value cleanly, I need to clear the ADLAR bit.
>
> - Right alignment is much easier, because the 10 bit value is structured as a normal integer in memory: the 8 lower bits fill ADCL and the remaining upper 2 bits are assigned to ADCH.
> - Left alignment requires manual shifting because the 10 bit span across both registers with trailing zeros at the bottom of ADCL. 
> 
> - The data type changes from uint8_t to uint16_t, because 10 bits yield greater values than 8 bits.
>
> - To get the results, I must read ADCL first, then ADCH second, because the CPU locks the ADC hardware completely when it reads ADCL, to prevent new conversions from overwriting the data when reading the register.
>
> - I set the prescaler to 64 since the datasheet states that for ADC to hit its maximum 10 bit resolution accuracy, the internal ADC clock frequency must be kept between 50kHz and 200 kHz.

| Ambient light condition   | AVCC (8 bit)          | AVCC (10 bit)              
| :---                      | :---                  | :---                              
| light (flashlight)        | 0x07 (7)              | 0x0540 ( 1344)            
| dark (covered)            | 0xFF (255)            | 0xED40 (60736)            
| normal room light         | 0xC6 (198)            | 0x0BC0 ( 3008)           

> The 10 bit resolution offers a more precise reading and captures a larger range of the hardware without having to clip the values like it previously did for the 8 bit AVCC and internal references. 

> For the implementation, I used conditional compilation using the C preprocessor directives to be able to distinguish between 10 bit resolution (this clears the ADLAR bit) and 8 bit resolution (this sets the ADLAR bit for left alignment):

**`adc.h`**
```c
#ifdef ADC_RESOLUTIN_10_BIT
    typedef uint16_t adc_result_t;
#else    
    typedef uint8_t adc_result_t;
#endif
}
```

**`adc.c`**
```c
adc_result_t adc_get_conversion_result(void)
{
#ifdef ADC_RESOLUTION_10_BIT
    return ADC;
#else
    return ADCH;
#endif
}
```

> And additionally, I used conditional compilation to clear or set the bits of ADLAR in the functions for the reference voltages:

**`adc.c`**
```c
#ifdef ADC_RESOLUTION_10_BIT
    ADMUX &= ~BIT_MASK(ADLAR);
#else
    ADMUX |= BIT_MASK(ADLAR);
#endif
}
```

--- 

#### Task 365
> **Question/Prompt:** Imagine that your software driver module will be used by your colleagues into their projects. At the time you write the code you do not know what resolution they will need, 8bit or 10bit. It will depend on their particular application. Therefore your job is to implement a solution offering them the possibility to choose between 8bit or 10bit resolution. Make use of conditional compilation.

> **Answer/Explanation:**
> In order to switch between the 8 or 10 bit resolution, they need to define the resolution in the `adc.h` file. Right now I use the 10 bit resolution, but that can be changed to 8 bit if needed, because all of the configurations required to use only ADCH were implemented in task 364.

**`adc.h`**
```c
#ifdef ADC_RESOLUTIN_10_BIT
    typedef uint16_t adc_result_t;
#else    
    typedef uint8_t adc_result_t;
#endif
}
```

--- 

#### Task 366
> **Question/Prompt:** Measure the code size for the newly added ADC driver module so that your colleagues are informed. Include a table with the functions available and the two options on resolution (8bit, 10bit).

> **Answer/Explanation:**
> The ADC drive is composed of 2 files, `adc.c` and `adc.h`, which in total are 8.09 KB (8,293 bytes).

| Function Interface                 | Architectural / Register Impact Changes 
| :---                               | :--- 
| `adc_init()`                       | Static inline execution layout remains identical. 
| `adc_select_avcc_voltage()`        | Toggles `ADLAR` high (8-bit) vs. clearing `ADLAR` (10-bit). 
| `adc_select_internal_voltage()`    | Toggles `ADLAR` high (8-bit) vs. clearing `ADLAR` (10-bit). 
| `adc_select_input_channel()`       | Identical masking operation on `ADMUX` channel bits. 
| `adc_configure_control_settings()` | Aggregates control registers; invariant under resolution. 
| `adc_set_prescaler_64()`           | Invariant under resolution; runs safely at a factor of 64. 
| `adc_enable_interrupt()`           | Flips the `ADIE` bit inside `ADCSRA` register blocks. 
| `adc_enable()`                     | Activates the core physical ADC blocks via `ADEN`. |
| `adc_disable_digital_input()`      | Cuts off the digital input buffer inside `DIDR0`. |
| `adc_start_conversion()`           | Triggers single hardware conversions via `ADSC`. |
| `adc_get_conversion_result()`      | **8-bit:** Returns single `ADCH` byte register.<br>**10-bit:** Synthesizes `ADCL` + `ADCH` via a 16-bit word read. |

---

## References & Resources
* AVR Microcontroller with Core Independent Peripherals and PicoPower technology (ATmega324PB)