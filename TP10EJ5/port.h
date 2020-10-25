/***************************************************************************//**
  @file     +port.h+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef PORT
#define PORT

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define ON 0xFF
#define OFF 0x00


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{
    uint8_t bit0    :1;
    uint8_t bit1    :1;
    uint8_t bit2    :1;
    uint8_t bit3    :1;
    uint8_t bit4    :1;
    uint8_t bit5    :1;
    uint8_t bit6    :1;
    uint8_t bit7    :1;
}portA;


typedef union
{
    struct portAB
    {
    uint_least8_t portA;
    uint_least8_t portB;
    }portAB;
    uint_least16_t portD;
}portABD_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
int bitToggle(int, char); // Dado un numero y un puerto, enciende el bit correspondiente.
int maskon(uint_least16_t, char);// Dada una mascara y un puerto, enceinde todos los bits que esten encendidos en la mascara 
int maskoff(uint_least16_t, char); // Dada una mascara y un puerto, apaga todos los bits que esten apagados en la mascara.
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
// +ej: char lcd_goto (int fil, int col);+


/*******************************************************************************
 ******************************************************************************/

#endif // _TEMPLATE_H_
