#ifndef MOD_H
#define MOD_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Module specific constant number zero */
#define SOS_FALSE            (0x00U)

/** \brief  Module specific constant number one */
#define SOS_TRUE             (0x01U)


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void letter_S(void)
    \brief      [ Litera S in codul morse ]  
    \param[in]  [ none ]
    \param[out] [ none ]
    \return     [ none ]
    \details    [ Executa secventa de 3 puncte pentru litera S ]
*/
extern void sos_letter_S(void);

/** \fn      void letter_O(void)
    \brief      [ Litera O in codul morse ]  
    \param[in]  [ none ]
    \param[out] [ none ]
    \return     [ none ]
    \details    [ Executa secventa de 3 linii pentru litera O ]
*/
extern void sos_letter_O(void);

/** \fn     void SOS(void)
    \brief      [ Se foloseste de functiile S si O ca sa faca un semnal SOS complet ]  
    \param[in]  [ none ]
    \param[out] [ none ]
    \return     [ none ]
    \details    [ Ruleaza S-O-S cu pauzele standard  ]
*/
extern void sos_pattern(void);

#endif 