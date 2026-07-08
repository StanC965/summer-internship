#ifndef GPIO_H
#define GPIO_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific null pointer */
#define GPIO_NULL            ((void*)0x00U)
#define GPIO_ZERO            (0x00U)
#define GPIO_ONE             (0x01U)

#define GPIO_TRUE            (GPIO_ONE)
#define GPIO_FALSE           (GPIO_ZERO)

#define GPIO_INPUT           (GPIO_TRUE)
#define GPIO_OUTPUT          (GPIO_FALSE)

/** \brief  parameter type unsigned byte (8 bit) */
typedef     unsigned char   gpio_uint8_t;

/** \brief  parameter type unsigned word (16 bit) */
typedef     unsigned int    gpio_uint16_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void set_pin(volatile unsigned char *PORT,unsigned char bit)

    \brief      [ Aceasta functie seteaza un pin de la un port ales pe 1 (HIGH)]  
*/
extern void gpio_set_pin(volatile unsigned char *PORT, gpio_uint8_t bit);

/** \fn     extern void gpio_reset_pin(volatile unsigned char *port, gpio_uint8_t bit);

    \brief      [Aceasta functie seteaza un pin de la un port ales pe 0(LOW)]
*/
extern void gpio_reset_pin(volatile unsigned char *port, gpio_uint8_t bit);


/** \fn     void gpio_toggle_pin(volatile unsigned char *port, gpio_uint8_t bit)
    \brief  Inverseaza starea curenta a unui pin
*/
extern void gpio_toggle_pin(volatile unsigned char *port, gpio_uint8_t bit);

/** \fn     void gpio_set_direction(volatile unsigned char *ddr, gpio_uint8_t bit, gpio_uint8_t intrare)
    \brief  Seteaza directia pinului: GPIO_INPUT (1) sau GPIO_OUTPUT (0)
*/
extern void gpio_set_direction(volatile unsigned char *ddr, gpio_uint8_t bit, gpio_uint8_t intrare);

#endif
