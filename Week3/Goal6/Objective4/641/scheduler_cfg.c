#include "scheduler_cfg.h"
#include "pwm.h"
#include "button.h"
#include "adc.h"
#include "led.h"

typedef enum {
    ILLUM_STATE_IDLE,
    ILLUM_STATE_TRIGGERED,
    ILLUM_STATE_RUNNING
} illum_state_t;

static illum_state_t current_state = ILLUM_STATE_IDLE;
static unsigned char previous_sw0_state = 0;
static unsigned char is_day_mode = 0;
static unsigned char absolute_target_pwm = 0;

static unsigned char profile_tick_counter = 0;
static unsigned char step_index = 0;

static const unsigned char night_steps[11] = {0, 1, 1, 3, 7, 16, 16, 14, 12, 10, 8};
static const unsigned char day_steps[11]  = {0, 4, 7, 16, 44, 59, 59, 55, 50, 45, 40};

void scheduler_task_50ms(void)
{
    button_debounce_update();
    
    unsigned char current_sw0 = button_get_sw0_state();
    
    /* 2. Catch rising-edge switch triggers to clear/restart illumination sequences */
    if (current_sw0 == 1 && previous_sw0_state == 0)
    {
        adc_start_conversion();
        current_state = ILLUM_STATE_TRIGGERED;
    }
    previous_sw0_state = current_sw0;
    
    /* 3. If running, trigger periodic ADC samples to track shifting conditions */
    if (current_state == ILLUM_STATE_RUNNING)
    {
        static unsigned char adc_sample_divider = 0;
        if (++adc_sample_divider >= 4) // sample ambient light every 200ms
        {
            adc_sample_divider = 0;
            adc_start_conversion();
        }
    }
}

void scheduler_task_100ms(void)
{
    unsigned long raw_adc_reading;
    unsigned char perceived_light_level;
    unsigned char computed_instant_pwm;
    
    switch (current_state)
    {
        case ILLUM_STATE_TRIGGERED:
            /* Fetch calibrated, inverted 10-bit raw intensity data */
            raw_adc_reading = adc_get_data();
            
            /* Translate 10-bit field safely into a clean 0 - 100 percentage scale */
            perceived_light_level = (unsigned char)((raw_adc_reading * 100UL) / 1023UL);
            
            /* Evaluate structural entry constraints using Table 741.1 */
            if (perceived_light_level <= 20)
            {
                absolute_target_pwm = 15;
                is_day_mode = 0;
            }
            else if (perceived_light_level <= 40)
            {
                absolute_target_pwm = 20;
                is_day_mode = 0;
            }
            else if (perceived_light_level <= 50)
            {
                absolute_target_pwm = 42;
                is_day_mode = 1;
            }
            else if (perceived_light_level <= 70)
            {
                absolute_target_pwm = 80;
                is_day_mode = 1;
            }
            else
            {
                absolute_target_pwm = 90;
                is_day_mode = 1;
            }
            
            /* Apply discrete structural visual feedback to OLED1 board */
            if (is_day_mode)
            {
                led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);  // LED1 Day Mode indicator
                led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
            }
            else
            {
                led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
                led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);  // LED2 Night Mode indicator
            }
            
            /* Clear phase control index registers */
            profile_tick_counter = 0;
            step_index = 0;
            current_state = ILLUM_STATE_RUNNING;
            
            /* Execute first entry step instantly */
            pwm_dc(100);
            break;
            
        case ILLUM_STATE_RUNNING:
            if (step_index < 11)
            {
                /* Execute timing updates at 200ms structural steps (every two 100ms ticks) */
                if (profile_tick_counter == 0)
                {
                    if (is_day_mode)
                    {
                        computed_instant_pwm = (unsigned char)(((unsigned int)absolute_target_pwm * day_steps[step_index]) / 100U);
                    }
                    else
                    {
                        computed_instant_pwm = (unsigned char)(((unsigned int)absolute_target_pwm * night_steps[step_index]) / 100U);
                    }
                    
                    /* Write update directly to OCR0A */
                    pwm_dc(100 - computed_instant_pwm);
                    
                    profile_tick_counter = 1;
                }
                else
                {
                    /* 200ms step complete, advance step pointer index */
                    profile_tick_counter = 0;
                    step_index++;
                }
            }
            else
            {
                /* --- ENTRY PHASE COMPLETE ---
                 * Continuous Closed-Loop Strategy:
                 * Dynamically adjust brightness to real-time light changes.
                 */
                raw_adc_reading = adc_get_data();
                perceived_light_level = (unsigned char)((raw_adc_reading * 100UL) / 1023UL);
                
                /* Closed-loop dynamic scaling logic:
                 * Day Mode: Brighter ambient light requires higher background PWM.
                 * Night Mode: Darker ambient light requires dimmer background PWM to prevent eye strain.
                 */
                if (is_day_mode)
                {
                    /* Dynamic proportional scaling between 40% and 100% duty cycle */
                    if (perceived_light_level < 40) perceived_light_level = 40;
                    pwm_dc(100 - perceived_light_level);
                }
                else
                {
                    /* Inverse comfort curve mapping for low-intensity nighttime conditions */
                    unsigned char baseline_night_pwm = 25 - (perceived_light_level / 2);
                    if (baseline_night_pwm < 5)  baseline_night_pwm = 5;
                    if (baseline_night_pwm > 25) baseline_night_pwm = 25;
                    pwm_dc(100 - baseline_night_pwm);
                }
            }
            break;
            
        default:
            break;
    }
}

void scheduler_task_500ms(void)
{
    
}

void scheduler_task_1000ms(void)
{
    
}