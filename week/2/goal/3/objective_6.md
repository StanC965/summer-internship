# Week: 2 - Goal : 3


## Objective 6: Ambient Light Application

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[361]** | `CORE`    | [x] Completed 
| **[362]** | `CORE`    | [x] Completed 

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
    if (light_sensor_value < LIGHT_SENSOR_MIDPOINT)
    {
      led_power_on(LED_ONBOARD);
    }
    else
    {
      led_power_off(LED_ONBOARD);
    }
    // delay(1 * MILISECOND);
  }
}
```

--- 

#### Task 362
> **Question/Prompt:**  Take 4 readings intervals (1 corresponding to complete dark, 2 semi-dark, 3 semi-light, 4 full light) and turn on LED1,2,3 as follows:

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
    if (light_sensor_value < LIGHT_SENSOR_SEMI_LIGHT)
    {
      led_power_on(LED_OLED1_1);
      led_power_on(LED_OLED1_2);
      led_power_on(LED_OLED1_3);
    }
    else if (light_sensor_value >= LIGHT_SENSOR_SEMI_LIGHT && light_sensor_value < LIGHT_SENSOR_SEMI_DARK)
    {
      led_power_on(LED_OLED1_1);
      led_power_on(LED_OLED1_2);
    }
    else if (light_sensor_value >= LIGHT_SENSOR_SEMI_DARK && light_sensor_value < LIGHT_SENSOR_FULL_DARK)
    {
      led_power_on(LED_OLED1_1);
    }
    else
    {
      led_power_off(LED_OLED1_1);
      led_power_off(LED_OLED1_2);
      led_power_off(LED_OLED1_3);
    }
    // delay(1 * MILISECOND);
  }
}
```

---