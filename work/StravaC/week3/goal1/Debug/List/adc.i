#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\adc.c"











 










typedef unsigned char adc_uint8_t;

extern void adc_init(void);

extern void adc_start_conversion(void);

extern adc_uint8_t adc_is_data_ready(void);

extern adc_uint8_t adc_is_conversion_running(void);

extern adc_uint8_t adc_get_data(void);

