#ifndef MOD_H
#define MOD_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific null pointer */
#define MOD_NULL            ((void*)0x00U)

/** \brief  Module specific constant number zero */
#define MOD_ZERO            (0x00U)

/** \brief  Module specific constant number one */
#define MOD_ONE             (0x01U)

/** \brief  Module specific constant number two */
#define MOD_TWO             (0x02U)

/** \brief  Module specific true */
#define MOD_TRUE            (MOD_ONE)

/** \brief  Module specific false */
#define MOD_FALSE           (MOD_ZERO)

/** \brief  Module specific notok */
#define MOD_NOTOK           (MOD_FALSE)

/** \brief  Module specific ok */
#define MOD_OK              (MOD_TRUE)

/** \brief  parameter type unsigned byte (8 bit) */
typedef     unsigned char   mod_uint8_t;

/** \brief  parameter type unsigned word (16 bit) */
typedef     unsigned int    mod_uint16_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void mod_func0(void)

    \brief      [ short function description ]  
    \param[in]  [ input parameter list and description ]
    \param[out] [ output parameter list and description ]
    \return     [ return value description ]
    \details    [ function description ]
*/
extern void mod_func0(void);

/** \fn     void mod_func1(umt_uint8_t parameter_1_u8)

    \brief      [ short function description ]  
    \param[in]  parameter_1_u8 [ description, valid range: [ inferior limit .. superior limit ]  ]
    \param[out] [ output parameter list and description ]
    \return     [ return value description ]
    \details    [ function description ]
*/
extern void mod_func1(mod_uint8_t parameter_1_u8);

#endif