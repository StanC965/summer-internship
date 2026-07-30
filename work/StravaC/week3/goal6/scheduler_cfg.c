#include "iom324pb.h"

#include "adc.h"
#include "button.h"
#include "gpio.h"
#include "pwm.h"
#include "scheduler_cfg.h"

/*
Hyundai Elantra dashboard illumination prototype.

Hardware:
- SW0: PC6, active-low
- TEMT6000: PA4 / ADC4
- Day LED: OLED1 LED1, PB3 / OC0A
- Night LED: OLED1 LED2, PB4 / OC0B
- OLED1 mounted on EXT4

Each stable SW0 press repeats the headlights-on scenario:
1. turn both illumination LEDs off;
2. acquire five initial ambient-light samples;
3. calculate the perceived light level;
4. select Day or Night mode;
5. apply Hyundai's 2-second entry phase;
6. continue adapting illumination slowly after entry phase.
*/

/*
TEMT6000 conversion:

High light intensity = low ADC voltage/value.
Low light intensity  = high ADC voltage/value.

The perceived-light scale is:

0   = very dark
100 = very bright

light_level =
    ((1023 - ADC_value) * 100) / 1023
*/

/*
Table 741.1:

Perceived light 0-20:
Night mode, absolute PWM = 15%

Perceived light 21-40:
Night mode, absolute PWM = 20%

Perceived light 41-50:
Day mode, absolute PWM = 42%

Perceived light 51-70:
Day mode, absolute PWM = 80%

Perceived light 71-100:
Day mode, absolute PWM = 90%
*/

/*
Table 741.2:

One entry-phase point is applied every 200 ms.

Time [s]:
0.0  0.2  0.4  0.6  0.8  1.0
1.2  1.4  1.6  1.8  2.0

Night relative steps:
0, 1, 1, 3, 7, 16, 16, 14, 12, 10, 8

Day relative steps:
0, 4, 7, 16, 44, 59, 59, 55, 50, 45, 40

Entry PWM requested by Hyundai:

PWM = absolute entry level + relative step

The result is saturated to 100%.
*/

/*
Engineering decisions after the entry phase:

- ADC is sampled every 100 ms.
- Illumination target is recalculated periodically.
- PWM changes slowly by 1% every 500 ms.
- Day/Night mode uses hysteresis:
    switch to Day at light level >= 43
    switch to Night at light level <= 38
- Values between 39 and 42 keep the previous mode.

This prevents visual flicker and aggressive reactions
to short ambient-light variations.
*/

#define APP_ZERO                         (0U)
#define APP_ONE                          (1U)

#define APP_SW0_PIN                      (6U)

#define APP_ADC_MAX_VALUE                (1023U)
#define APP_LIGHT_LEVEL_MAX              (100U)

#define APP_INITIAL_SAMPLE_COUNT         (5U)

#define APP_ENTRY_POINT_COUNT            (11U)

#define APP_ENTRY_PERIOD_TICKS           (2U)

#define APP_PWM_MAXIMUM                  (100U)

#define APP_DAY_THRESHOLD_HIGH           (43U)
#define APP_NIGHT_THRESHOLD_LOW          (38U)

#define APP_PWM_SMOOTH_STEP              (1U)

typedef unsigned char app_uint8_t;
typedef unsigned int app_uint16_t;
typedef unsigned long app_uint32_t;

typedef enum
{
    APP_MODE_NIGHT = 0,
    APP_MODE_DAY
} app_mode_t;

typedef enum
{
    APP_STATE_WAITING_FOR_SW0 = 0,
    APP_STATE_INITIAL_MEASUREMENT,
    APP_STATE_ENTRY_PHASE,
    APP_STATE_CONTINUOUS_CONTROL
} app_state_t;

static const app_uint8_t
    app_night_relative_steps[
        APP_ENTRY_POINT_COUNT
    ] =
{
     0U,
     1U,
     1U,
     3U,
     7U,
    16U,
    16U,
    14U,
    12U,
    10U,
     8U
};

static const app_uint8_t
    app_day_relative_steps[
        APP_ENTRY_POINT_COUNT
    ] =
{
     0U,
     4U,
     7U,
    16U,
    44U,
    59U,
    59U,
    55U,
    50U,
    45U,
    40U
};

static button_t app_sw0_button;

static app_state_t app_state;
static app_mode_t app_mode;

static app_uint8_t app_light_level;

static app_uint8_t app_absolute_pwm;
static app_uint8_t app_current_pwm;
static app_uint8_t app_target_pwm;

static app_uint8_t app_initial_sample_counter;
static app_uint32_t app_initial_adc_sum;

static app_uint8_t app_entry_index;
static app_uint8_t app_entry_100ms_counter;

static void app_start_headlights_scenario(void);

static void app_process_adc_result(
    app_uint16_t adc_value
);

static app_uint8_t app_adc_to_light_level(
    app_uint16_t adc_value
);

static app_mode_t app_get_mode_from_light_level(
    app_uint8_t light_level
);

static app_uint8_t app_get_absolute_pwm(
    app_uint8_t light_level
);

static void app_start_entry_phase(void);

static void app_apply_entry_point(void);

static void app_apply_selected_output(
    app_uint8_t duty_cycle
);

static void app_update_continuous_target(void);

static void app_smooth_pwm(void);

void scheduler_cfg_init(void)
{
    gpio_init();
    pwm_init();
    adc_init();

    button_init(
        &app_sw0_button,
        &DDRC,
        &PORTC,
        &PINC,
        APP_SW0_PIN
    );

    app_state =
        APP_STATE_WAITING_FOR_SW0;

    app_mode =
        APP_MODE_NIGHT;

    app_light_level =
        APP_ZERO;

    app_absolute_pwm =
        APP_ZERO;

    app_current_pwm =
        APP_ZERO;

    app_target_pwm =
        APP_ZERO;

    app_initial_sample_counter =
        APP_ZERO;

    app_initial_adc_sum =
        APP_ZERO;

    app_entry_index =
        APP_ZERO;

    app_entry_100ms_counter =
        APP_ZERO;

    pwm_set_duty_cycle_percent(
        PWM_CHANNEL_DAY_LED,
        APP_ZERO
    );

    pwm_set_duty_cycle_percent(
        PWM_CHANNEL_NIGHT_LED,
        APP_ZERO
    );

    pwm_start();
}

void scheduler_task_10ms(void)
{
    button_debounce_task(
        &app_sw0_button
    );

    if (
        button_was_pressed(
            &app_sw0_button
        ) ==
        BUTTON_EVENT_DETECTED
    )
    {
        app_start_headlights_scenario();
    }
}

void scheduler_task_50ms(void)
{
    /*
    Not used by this application.
    */
}

void scheduler_task_100ms(void)
{
    app_uint16_t adc_value;

    /*
    Get the previous conversion result, if available.
    */

    if (
        adc_is_data_ready() ==
        ADC_DATA_READY
    )
    {
        adc_value =
            adc_get_data();

        app_process_adc_result(
            adc_value
        );
    }

    /*
    Start a new conversion continuously after
    the first SW0 press.
    */

    if (
        app_state !=
        APP_STATE_WAITING_FOR_SW0
    )
    {
        adc_start_conversion();
    }

    /*
    Entry phase advances every 200 ms.

    Scheduler task = 100 ms
    2 executions * 100 ms = 200 ms
    */

    if (
        app_state ==
        APP_STATE_ENTRY_PHASE
    )
    {
        app_entry_100ms_counter++;

        if (
            app_entry_100ms_counter >=
            APP_ENTRY_PERIOD_TICKS
        )
        {
            app_entry_100ms_counter =
                APP_ZERO;

            app_apply_entry_point();
        }
    }
}

void scheduler_task_500ms(void)
{
    if (
        app_state ==
        APP_STATE_CONTINUOUS_CONTROL
    )
    {
        app_update_continuous_target();
        app_smooth_pwm();
    }
}

void scheduler_task_1000ms(void)
{
    /*
    Not used by this application.
    */
}

static void app_start_headlights_scenario(void)
{
    /*
    Each SW0 press repeats the complete scenario.
    */

    app_state =
        APP_STATE_INITIAL_MEASUREMENT;

    app_initial_sample_counter =
        APP_ZERO;

    app_initial_adc_sum =
        APP_ZERO;

    app_entry_index =
        APP_ZERO;

    app_entry_100ms_counter =
        APP_ZERO;

    app_current_pwm =
        APP_ZERO;

    app_target_pwm =
        APP_ZERO;

    pwm_set_duty_cycle_percent(
        PWM_CHANNEL_DAY_LED,
        APP_ZERO
    );

    pwm_set_duty_cycle_percent(
        PWM_CHANNEL_NIGHT_LED,
        APP_ZERO
    );

    adc_start_conversion();
}

static void app_process_adc_result(
    app_uint16_t adc_value
)
{
    if (
        app_state ==
        APP_STATE_INITIAL_MEASUREMENT
    )
    {
        app_initial_adc_sum +=
            adc_value;

        app_initial_sample_counter++;

        if (
            app_initial_sample_counter >=
            APP_INITIAL_SAMPLE_COUNT
        )
        {
            app_uint16_t average_adc;

            average_adc =
                (app_uint16_t)(
                    app_initial_adc_sum /
                    APP_INITIAL_SAMPLE_COUNT
                );

            app_light_level =
                app_adc_to_light_level(
                    average_adc
                );

            app_mode =
                app_get_mode_from_light_level(
                    app_light_level
                );

            app_absolute_pwm =
                app_get_absolute_pwm(
                    app_light_level
                );

            app_start_entry_phase();
        }
    }
    else if (
        app_state ==
        APP_STATE_ENTRY_PHASE ||
        app_state ==
        APP_STATE_CONTINUOUS_CONTROL
    )
    {
        /*
        Keep the latest measured light level available.
        Mode is locked during entry phase.
        */

        app_light_level =
            app_adc_to_light_level(
                adc_value
            );
    }
}

static app_uint8_t app_adc_to_light_level(
    app_uint16_t adc_value
)
{
    app_uint32_t light_value;

    if (adc_value > APP_ADC_MAX_VALUE)
    {
        adc_value =
            APP_ADC_MAX_VALUE;
    }

    light_value =
        (
            (
                (app_uint32_t)
                (
                    APP_ADC_MAX_VALUE -
                    adc_value
                )
            ) *
            APP_LIGHT_LEVEL_MAX
        ) /
        APP_ADC_MAX_VALUE;

    return (app_uint8_t)light_value;
}

static app_mode_t app_get_mode_from_light_level(
    app_uint8_t light_level
)
{
    if (light_level <= 40U)
    {
        return APP_MODE_NIGHT;
    }

    return APP_MODE_DAY;
}

static app_uint8_t app_get_absolute_pwm(
    app_uint8_t light_level
)
{
    if (light_level <= 20U)
    {
        return 15U;
    }

    if (light_level <= 40U)
    {
        return 20U;
    }

    if (light_level <= 50U)
    {
        return 42U;
    }

    if (light_level <= 70U)
    {
        return 80U;
    }

    return 90U;
}

static void app_start_entry_phase(void)
{
    app_state =
        APP_STATE_ENTRY_PHASE;

    app_entry_index =
        APP_ZERO;

    app_entry_100ms_counter =
        APP_ZERO;

    /*
    Apply the t = 0 entry point immediately.
    */

    app_apply_entry_point();
}

static void app_apply_entry_point(void)
{
    app_uint8_t relative_step;
    app_uint16_t requested_pwm;

    if (
        app_entry_index >=
        APP_ENTRY_POINT_COUNT
    )
    {
        /*
        Entry phase finished after the t = 2 s point.

        Return to the absolute level and continue
        with slow ambient-light adaptation.
        */

        app_state =
            APP_STATE_CONTINUOUS_CONTROL;

        app_current_pwm =
            app_absolute_pwm;

        app_target_pwm =
            app_absolute_pwm;

        app_apply_selected_output(
            app_current_pwm
        );

        return;
    }

    if (app_mode == APP_MODE_DAY)
    {
        relative_step =
            app_day_relative_steps[
                app_entry_index
            ];
    }
    else
    {
        relative_step =
            app_night_relative_steps[
                app_entry_index
            ];
    }

    requested_pwm =
        (app_uint16_t)(
            app_absolute_pwm +
            relative_step
        );

    if (requested_pwm > APP_PWM_MAXIMUM)
    {
        requested_pwm =
            APP_PWM_MAXIMUM;
    }

    app_current_pwm =
        (app_uint8_t)requested_pwm;

    app_apply_selected_output(
        app_current_pwm
    );

    app_entry_index++;
}

static void app_apply_selected_output(
    app_uint8_t duty_cycle
)
{
    if (app_mode == APP_MODE_DAY)
    {
        pwm_set_duty_cycle_percent(
            PWM_CHANNEL_NIGHT_LED,
            APP_ZERO
        );

        pwm_set_duty_cycle_percent(
            PWM_CHANNEL_DAY_LED,
            duty_cycle
        );
    }
    else
    {
        pwm_set_duty_cycle_percent(
            PWM_CHANNEL_DAY_LED,
            APP_ZERO
        );

        pwm_set_duty_cycle_percent(
            PWM_CHANNEL_NIGHT_LED,
            duty_cycle
        );
    }
}

static void app_update_continuous_target(void)
{
    /*
    Mode hysteresis around the Day/Night boundary.

    Night -> Day only at 43 or higher.
    Day -> Night only at 38 or lower.
    */

    if (
        app_mode == APP_MODE_NIGHT &&
        app_light_level >= APP_DAY_THRESHOLD_HIGH
    )
    {
        app_mode =
            APP_MODE_DAY;

        app_current_pwm =
            APP_ZERO;
    }
    else if (
        app_mode == APP_MODE_DAY &&
        app_light_level <= APP_NIGHT_THRESHOLD_LOW
    )
    {
        app_mode =
            APP_MODE_NIGHT;

        app_current_pwm =
            APP_ZERO;
    }
    else
    {
        /*
        Keep the current mode inside the hysteresis area.
        */
    }

    app_target_pwm =
        app_get_absolute_pwm(
            app_light_level
        );
}

static void app_smooth_pwm(void)
{
    if (
        app_current_pwm <
        app_target_pwm
    )
    {
        app_current_pwm +=
            APP_PWM_SMOOTH_STEP;

        if (
            app_current_pwm >
            app_target_pwm
        )
        {
            app_current_pwm =
                app_target_pwm;
        }
    }
    else if (
        app_current_pwm >
        app_target_pwm
    )
    {
        app_current_pwm -=
            APP_PWM_SMOOTH_STEP;

        if (
            app_current_pwm <
            app_target_pwm
        )
        {
            app_current_pwm =
                app_target_pwm;
        }
    }
    else
    {
        /*
        Current PWM already equals the target.
        */
    }

    app_apply_selected_output(
        app_current_pwm
    );
}