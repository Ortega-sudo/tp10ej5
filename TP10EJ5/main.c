/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: mateo
 *
 * Created on October 21, 2020, 11:56 AM
 */
#include "port.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * 
 */


int main(int argc, char** argv) 

{   
    char a;
    char c;
    int n=0;
    
    
    printf("Ingrese Q para salr del programa, ingrese un numero del 0 al 7 para cambiar el estado del led correspondiente, presione S para apagar los leds encedidos, presione C para encender los leds apagados, presione T para invertir el estado de los leds.\n");
    while( (c = getchar()) != 'q')  
        {
         
        if(c =='c')         // Si se presiono 'C' enciendo todos los bits
            maskon(ON,a);
        else if(c== 's')    // Si se presiono 'S' se apago todos los bits 
            maskoff(OFF, a);
        else if((c >='0') && (c <= '7')) // Si se presiono un numero del 0 al 7 altero el valor del bit que corresponda
            bitToggle((c-'0'), a); 
        else if (c == 't')           //invierte el estado de todo el puerto
        {
            for (n ; n<=7; ++n) 
            bitToggle(n,a);
        }
        
        else // mensaje de error
            printf("Error, vuelva a ingresar un valor.\n");
        
        //printf("Estado del puerto A:\n0 1 2 3 4 5 6 7\n%d %d %d %d %d %d %d %d\n", a.bit0, a.bit1, a.bit2, a.bit3, a.bit4, a.bit5, a.bit6, a.bit7);
        
        }
    return (EXIT_SUCCESS);
}

   
/*for (n ; n<=7; ++n) 
 *      bitToggle(n,a);
 */
