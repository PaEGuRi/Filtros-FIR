/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K42
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

//Se incluyen los .h necesarios para las librerias
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/adcc.h"
#include "cola.h"
#include "funciones.h"
#include <xc.h>

volatile char VGAIADC = 0; //Se declara la bandera para la interrupcion del ADC
int valorADC; //Variable donde se guarda el valor de la conversion 
static const uint8_t lookuphexa[16] = {'0', '1', '2', '3', '4', '5', '6', '7','8','9','A','B', 'C', 'D', 'E', 'F'};
//Tabla para la conversion a Hex-ASCII

void MiInterrupcionADC(void) { //Funcion para la interrupcion del ADC
    // add your ADC interrupt custom code
    // or set custom function using TMR2_SetInterruptHandler()
    VGAIADC = 1; //Se sube la bandera
    valorADC = ADCC_GetConversionResult(); //Se pide el valor obtenido de la conversion 
    IO_RD1_Toggle();
}

/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    TMR2_Initialize();
    ADCC_Initialize();
    UART1_Initialize();
    SPI1_Initialize();
    SPI1_Open();
    INTERRUPT_Initialize();

    ADCC_SetADIInterruptHandler(MiInterrupcionADC); //Se llama a la interrupcion

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();


    // select the A/D channel
    ADPCH = channel_AND6;


    while (1) {

        if (VGAIADC == 1) { //Se pregunta si la bandera de la interrupcion esta arriba 
            
            LDAC_SetHigh(); //Se enciende el pin del LDAC
            VGAIADC = 0; //Se baja la bandera de la interrupcion
            DAC_CS_SetLow(); //Se baja el pin del DAC_CS

            UART1_Write(lookuphexa[ADRESH & 0b1111]); // Se emplea la funcion UART1_Write y se divide el numero en 3 partes
                                                      // se emplea la tabla de lookup realizando operaciones
            UART1_Write(lookuphexa[(ADRESL >> 4)  & 0b1111]);
            UART1_Write(lookuphexa[ADRESL & 0b1111]);
            UART1_Write(','); //Se envia una coma

            int conversion = FilterFIR(valorADC); //La variable entera 'conversion' toma el valor del llamado de la funcion FilterFIR 
            
            UART1_Write(lookuphexa[(conversion >> 8)&0x0f]); //Se escribe en la transmision el valor de con la tabla loookup y la funcion
            UART1_Write(lookuphexa[(conversion >> 4)&0x0f]);
            UART1_Write(lookuphexa[(conversion)&0x0f]);
            UART1_Write('\n'); //Se imprime un salto de linea

            SPI1_ExchangeInfo(((conversion >> 8) | 0b11110000), (conversion)); //Se envia al DAC el valor conversion con los bits de config
            LDAC_SetLow(); //Se apaga el pin del LDAC

        }

    }
}
/**
 End of File
 */

