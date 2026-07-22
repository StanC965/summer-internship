#ifndef LIGHTING_C
#define LIGHTING_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "lighting.h"
#include <iom324pb.h>
#include "adc.h"
#include "timer.h"
#include "bits.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static const light_band_t light_bands[] = {
    {0, 20, 15, LIGHT_MODE_NIGHT},
    {21, 40, 20, LIGHT_MODE_NIGHT},
    {41, 50, 42, LIGHT_MODE_DAY},
    {51, 70, 80, LIGHT_MODE_DAY},
    {71, 100, 90, LIGHT_MODE_DAY},
};

#define LIGHT_BAND_COUNT (sizeof(light_bands) / sizeof(light_bands[0]))

static const int8_t night_entry_steps[ENTRY_PHASE_STEP_COUNT] =
    {0, 1, 1, 3, 7, 16, 16, 14, 12, 10, 8};

static const int8_t day_entry_steps[ENTRY_PHASE_STEP_COUNT] =
    {0, 4, 7, 16, 44, 59, 59, 55, 50, 45, 40};

static void lighting_set_duty_percent(uint8_t duty_percent)
{
    uint16_t compare_value = ((uint32_t)duty_percent * LIGHTING_PWM_TOP) / 100U;
    OCR1A = compare_value;
    OCR1B = compare_value;
}

static entry_phase_state_t entry_state = ENTRY_PHASE_IDLE;
static uint8_t entry_step_index = 0;
static int16_t current_duty = 0;
static light_mode_t current_mode = LIGHT_MODE_NIGHT;

static uint8_t adc_to_perceived_light(uint16_t adc_raw)
{
    return (uint8_t)(100U - (((uint32_t)adc_raw * 100U) / 1023U));
}

static const light_band_t *lighting_find_band(uint8_t perceived_level)
{
    for (uint8_t i = 0; i < LIGHT_BAND_COUNT; i++)
    {
        if (perceived_level >= light_bands[i].perceived_min &&
            perceived_level <= light_bands[i].perceived_max)
        {
            return &light_bands[i];
        }
    }
    return &light_bands[0];
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void lighting_init(void)
{
    TCCR1A = BIT_MASK(COM1A1) | BIT_MASK(COM1B1) | BIT_MASK(WGM11);
    TCCR1B = BIT_MASK(WGM13) | BIT_MASK(WGM12) | BIT_MASK(CS11);
    ICR1 = LIGHTING_PWM_TOP;

    lighting_set_duty_percent(0);

    TIMSK1 |= BIT_MASK(TOIE1);
}

void lighting_trigger_entry_phase(void)
{
    adc_start_conversion();
    while (ADCSRA & (BIT_MASK(ADSC)))
    {
    }

    uint16_t adc_raw = adc_get_data();
    uint8_t perceived_level = adc_to_perceived_light(adc_raw);

    const light_band_t *band = lighting_find_band(perceived_level);
    current_mode = band->mode;
    current_duty = band->absolute_entry_percent;

    lighting_set_duty_percent((uint8_t)current_duty);

    entry_step_index = 0;
    entry_state = ENTRY_PHASE_RUNNING;
}

void lighting_entry_phase_update(void)
{
    if (entry_state != ENTRY_PHASE_RUNNING)
    {
        return;
    }

    entry_step_index++;
    if (entry_step_index >= ENTRY_PHASE_STEP_COUNT)
    {
        entry_state = ENTRY_PHASE_IDLE;
        return;
    }

    int8_t step = (current_mode == LIGHT_MODE_NIGHT)
                      ? night_entry_steps[entry_step_index]
                      : day_entry_steps[entry_step_index];

    current_duty += step;
    if (current_duty > 100)
    {
        current_duty = 100;
    }
    if (current_duty < 0)
    {
        current_duty = 0;
    }

    lighting_set_duty_percent((uint8_t)current_duty);
}

#endif /* LIGHTING_C */
