/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "port.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#define INVALID(n,port) ((port=='a'&&n>7)||(port=='A'&&n>7)||(port=='b'&&n>7)||(port=='B'&&n>7)||(port=='d'&&n>15)||(port=='D'&&n>15)||(n<0))
#define MAX1BYTE 255
typedef union
{
    struct portAB
    {
    uint_least8_t portA;
    uint_least8_t portB;
    }portAB;
    uint_least16_t portD;
}portABD_t;
portABD_t ports;

/*****************************************************************************/
/*La funcion bitSet pone el bit "n" del puerto "port" en 1. Si no hubo error */
/*devuelve 0, si hubo error devuelve otra cosa. Revisa si el bit "n" es mayor*/
/*a la capacidad maxima del puerto y revisa que el puerto exista (mayuscula o*/
/*o minuscula). Recibe un int para el bit y un char para el puerto.          */
/*Ej: bitSet(0,'a'), bitSet(7,'D'). El llamado bitSet(8,'a') devuelve error  */
/*****************************************************************************/

int bitSet(int n,char port)
{
    uint_least8_t mask = 0x01;//mascara 00000001
    uint_least16_t mask1 = 0x0001;//el tamaño de las mascaras varia con el puerto
    int errors = 0;//errores en 0
  
    
    if(INVALID(n,port))//revisa que el puerto y el bit sean coherentes
    {
        errors++;//hubo error
    }
    else
    {    
        switch(port)
        {
            case 'a':
            case 'A':
                mask<<=n;//coloca el "1" de la mascara en el bit n
                ports.portAB.portA|=mask;//OR bit a bit con la mascara
                break;
            case 'b':
            case 'B':
                mask<<=n;
                ports.portAB.portB|=mask;
                break;
            case 'd':
            case 'D':           
                mask1<<=n;
                ports.portD |= mask1;
                break;
            default: 
                errors++;//si el puerto no es ninguno de los anteriores hubo error
        }
    }
    return errors;   
}
/*****************************************************************************/
/*La funcion bitClr pone el bit "n" del puerto "port" en 0. Si no hubo error */
/*devuelve 0, si hubo error devuelve otra cosa. Revisa si el bit "n" es mayor*/
/*a la capacidad maxima del puerto y revisa que el puerto exista (mayuscula o*/
/*o minuscula). Recibe un int para el bit y un char para el puerto.          */
/*Ej: bitClr(0,'a'), bitClr(7,'D'). El llamado bitClr(8,'a') devuelve error  */
/*****************************************************************************/
int bitClr(int n,char port)
{
    uint_least8_t mask = 0xFE;//mascara 11111110
    uint_least16_t mask1 = 0xFFFE;//el tamaño de las mascaras varia con el puerto
    int errors = 0;//errores en 0
    if(INVALID(n,port))//revisa que el puerto y el bit sean coherentes
    {
        errors++;//hubo error
    }
    else
    {
        switch(port)
        {
            case 'a':
            case 'A':
                for(int i = 1 ;i<n; i++)
                {
                    mask<<=1;//coloca el "0" de la mascara en el bit n
                    mask +=1;//como completa con 0 le agrego un uno cada vez
                }
                ports.portAB.portA&=mask;
                break;
            case 'b':
            case 'B':
                for(int i = 1;i<n;i++)
                {
                    mask<<=1;
                    mask +=1;
                }
                ports.portAB.portB&=mask;//AND bit a bit con mascara
                break;
            case 'd':
            case 'D':
                for(int i = 1;i<n;i++)
                {
                    mask1<<=1;
                    mask1 +=1;
                }
                ports.portD &= mask1;
                break;
            default: 
                errors++;
        }
    }
    return errors;  
}
/******************************************************************************/
/*La funcion bitGet devuelve el valor del bit "n".                            */
/*Si hubo error devuelve un numero negativo. Revisa si el bit "n" es mayor    */
/*a la capacidad maxima del puerto y revisa que el puerto exista (mayuscula o */
/*o minuscula). Recibe un int para el bit y un char para el puerto.           */
/*Ej: bitGet(0,'a'), bitGet(7,'D'). El llamado bitGet(8,'a') devuelve error   */
/******************************************************************************/
int bitGet(int n,char port)
{
    uint_least8_t mask=0x01;//mascara 00000001
    uint_least16_t mask1 = 0x0001;//el tamaño de las mascaras varia con el puerto
    int errors = 0;
    
    if(INVALID(n,port))//revisa que el puerto y el bit sean coherentes 
    {                               
        errors--;//hubo error
    }
    else
    {
         switch(port)
        {
            case 'a':
            case 'A':
                mask<<=n;//acomodo el "1" en el bit "n"
                errors = (ports.portAB.portA&mask);//AND entre el puerto y la 
                break;  //mascara. Si habia un "1" en el bit-> ans = 2^n
            case 'b':
            case 'B':
                mask<<=n;
                errors=(ports.portAB.portB&mask);
                break;
            case 'd':
            case 'D':
                mask1<<=n;
                errors = ports.portD&mask1;
                break;
            default: 
                errors--;
            
        }
    
    }
    if(errors>0)
    {
        errors=1;
    }
    return errors; //ans<0 -> error | ans>0 -> encendido | ans == 0 -> apagado.
}
/******************************************************************************/
/*La funcion bitToggle invierte el valor del bit "n" del puero "port".        */
/*Si hubo error devuelve un numero distinto a 0. Revisa si el bit "n" es mayor*/
/*a la capacidad maxima del puerto y revisa que el puerto exista (mayuscula o */
/*o minuscula). Recibe un int para el bit y un char para el puerto.           */
/*Ej: bitToggle(0,'a'), bitToggle(7,'D'). El llamado bitToggle(8,'a') devuelve*/
/*error.                                                                      */
/******************************************************************************/
int bitToggle(int n,char port)
{
    uint_least8_t mask=0x01;//mascara 00000001
    uint_least16_t mask1 = 0x0001;
    int errors = 0;//errores en 0
    if(INVALID(n,port))
    {
        errors++;//hubo error
    }
    else
    {
        switch(port)
        {
            case 'a':
            case 'A':
                mask<<=n;//acomodo el "1" en el bit "n"
                ports.portAB.portA^=mask;//Exclusive-OR entre mascara y puerto
                break;
            case 'b':
            case 'B':
                mask<<=n;
                ports.portAB.portB^=mask;
                break;
            case 'd':
            case 'D':
                mask1<<=n;
                ports.portD ^= mask1;
                break;
            default: 
                errors++;
        }
    }
    return errors;
}
/*maskOn: Dado un puerto y una máscara, debe prender todos aquellos bits que estén  prendidos  en  la  máscara,  sin  cambiar  el  estado  de  los  restantes. */
int maskon(uint_least16_t mask,char port){
    int on=0;// 0 si no hay error, 1 si hay error de mask, 2 si hay error de puerto
    switch(port){
        case'a':
        case'A':
            if(mask<=MAX1BYTE){
                ports.portAB.portA|=mask;//hago un or entre la mascara y el puerto a, y se lo asigno al puerto a
            }else{
                on=1;//mask no valida
            }
            break;
        case'B':
        case'b':
            if(mask<=MAX1BYTE){
                ports.portAB.portB|=mask;//hago un or entre la mascara y el puerto b, y se lo asigno al puerto b
            }else{
                on=1;//mask no valida
            }
            break;
        case'D':
        case'd':
            ports.portD |= mask;//hago un or entre la mascara y el puerto d, y se lo asigno al puerto d
            break;
        default:
            on=2;
            break;
    }
    return on;
}
/*maskOff: Dado un puerto y una máscara, debe apagar todos aquellos bits que estén  prendidos  en  la  máscara,  sin  cambiar  el  estado  de  los  restantes.*/
int maskoff(uint_least16_t mask,char port){
    int off=0;// 0 si no hay error, 1 si hay error de mask, 2 si hay error de puerto
    switch(port){
        case'a':
        case'A':
            if(mask<=MAX1BYTE){
                ports.portAB.portA&=(~mask);//hago un and entre la mascara negada y el puerto a, y se lo asigno al puerto a
            }else{
                off=1;//mask no valida
            }
            break;
        case'B':
        case'b':
            if(mask<=MAX1BYTE){
                ports.portAB.portB&=(~mask);//hago un and entre la mascara negada y el puerto b, y se lo asigno al puerto b
            }else{
                off=1;//mask no valida
            }
            break;
        case'D':
        case'd':
            ports.portD &= (~mask);//hago un and entre la mascara negada y el puerto d, y se lo asigno al puerto d
            break;
        default:
            off=2;
            break;
    }
    return off;
}
/*maskToggle: Dado un puerto y una máscara, debe cambiar el estado de todos aquellos  bits  que  estén  prendidos  en  la  máscara  al  opuesto,  sin  cambiar  el estado de los restantes.*/
int masktoggle(uint_least16_t mask,char port){
    int toggle=0;// 0 si no hay error, 1 si hay error de mask, 2 si hay error de puerto
    switch(port){
        case'a':
        case'A':
            if(mask<=MAX1BYTE){
                ports.portAB.portA^=mask;//hago un xor entre la mascara y el puerto a, y se lo asigno al puerto a
            }else{
                toggle=1;//mask no valida
            }
            break;
        case'B':
        case'b':
            if(mask<=MAX1BYTE){
                ports.portAB.portB^=mask;//hago un xor entre la mascara y el puerto b, y se lo asigno al puerto b
            }else{
                toggle=1;//mask no valida
            }
            break;
        case'D':
        case'd':
            ports.portD ^= mask;//hago un xor entre la mascara y el puerto d, y se lo asigno al puerto d
            break;
        default:
            toggle=2;
            break;
    }
    return toggle;
}