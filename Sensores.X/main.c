
#include "mcc_generated_files/mcc.h"
#include <string.h> /* for memset */
void miTimer0ISR(void); //Generar una interrupcion cada 1s
void rxSerialISR(void); //Genera una interrupcion cuna hay un dato en puerto serial para leer;
volatile uint8_t rxData; //Guarda lectura de puerto serial
unsigned char strNum[8]; // Se recibiran de 2 bytes 2^16 0-65536
uint8_t i=0;
//Variables registra el period de muestro segun labview
uint16_t periodoA=1; //Sensor voltaje (potenciometro)
uint16_t periodoB=1; //Sensor LDR
uint16_t periodoC=1; //Sensor LM35
uint16_t periodoD=1; //Sensor Termistor NTC
uint16_t periodoE=1; //Sensor SHARP

//Variables incrementan cada 1 segundo para controlar periodo de muestreo
uint16_t cont1segA=0; //Sensor voltaje (potenciometro)
uint16_t cont1segB=0; //Sensor LDR
uint16_t cont1segC=0; //Sensor LM35
uint16_t cont1segD=0; //Sensor Termistor NTC
uint16_t cont1segE=0; //Sensor SHARP

void main(void)
{
    SYSTEM_Initialize();
  
    TMR0_SetInterruptHandler (miTimer0ISR);//Interrupción timer0 cada 1s
    EUSART1_SetRxInterruptHandler(rxSerialISR);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    printf("INICIO\n\r");  
    adc_result_t convertedValue; 
    while (1)
    {
        if(cont1segA>=periodoA){
            ADCC_StartConversion(channel_ANA0);
            while(!ADCC_IsConversionDone());
            convertedValue = ADCC_GetConversionResult();
            printf("A%d\r\n", convertedValue);
            cont1segA=0;//Resetea contador 
        }
        if(cont1segB>=periodoB){
            ADCC_StartConversion(channel_ANA1);
            while(!ADCC_IsConversionDone());
            convertedValue = ADCC_GetConversionResult();
            printf("B%d\r\n", convertedValue);
            cont1segB=0;//Resetea contador 
        }
        if(cont1segC>=periodoC){
            ADCC_StartConversion(channel_ANA2);
            while(!ADCC_IsConversionDone());
            convertedValue = ADCC_GetConversionResult();
            printf("C%d\r\n", convertedValue);
            cont1segC=0;//Resetea contador 
        }
        if(cont1segD>=periodoD){
            ADCC_StartConversion(channel_ANA4);
            while(!ADCC_IsConversionDone());
            convertedValue = ADCC_GetConversionResult();
            printf("D%d\r\n", convertedValue);
            cont1segD=0;//Resetea contador 
        }
        if(cont1segE>=periodoE){
            ADCC_StartConversion(channel_ANA5);
            while(!ADCC_IsConversionDone());
            convertedValue = ADCC_GetConversionResult();
            printf("E%d\r\n", convertedValue);
            cont1segE=0;//Resetea contador 
        }
    }
}
void miTimer0ISR(void){//Interrupción cada 1 segundo
    cont1segA++; //Sensor voltaje (potenciometro)
    cont1segB++; //Sensor LDR
    cont1segC++; //Sensor LM35
    cont1segD++; //Sensor Termistor NTC
    cont1segE++; //Sensor SHARP
    //LATAbits.LATA5=~LATAbits.LATA5;
}
void rxSerialISR(void){
    EUSART1_Receive_ISR(); //Gestiona la recepcion rx serial
    if(EUSART1_is_rx_ready())
    {
            rxData = EUSART1_Read();
            if(rxData!=0x0A && i<8){
               strNum[i]=rxData;
               i++;
            }else{ 
                i=0; //Resetea contador de array
                switch(strNum[0])
                {
                    case('A'):
                        periodoA = atoi(&strNum+1);
                        break;
                    case('B'):
                        periodoB = atoi(&strNum+1);
                        break;
                    case('C'):
                        periodoC = atoi(&strNum+1);
                        break;
                    case('D'):
                        periodoD = atoi(&strNum+1);
                        break;
                    case('E'):
                        periodoE = atoi(&strNum+1);
                        break;
                    default:
                        break;
                } 
                
                memset(strNum, 0, 8); //Para poner array con null valores
            }
            

    }
}