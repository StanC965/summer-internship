#include "iom324pb.h"

#include "adc.h"

void main(void)
{
    adc_uint8_t app_light_value;

    app_light_value = 0U;

    adc_initialize();
    adc_start_conversion();

    while (ADC_TRUE)
    {
        if (adc_is_result_ready() == ADC_RESULT_READY)
        {
            app_light_value = adc_get_result();

            /*
            Porneste urmatoarea conversie numai dupa ce
            rezultatul precedent a fost preluat.
            */
            adc_start_conversion();
        }
    }
}