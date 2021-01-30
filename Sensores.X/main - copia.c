
#include "mcc_generated_files/mcc.h"
void miTimer0ISR(void);
void rxSerialISR(void);
int contador=0;
uint8_t rxData;
unsigned char temp;

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    //Interrupción timer0 cada 100ms
//    TMR0_SetInterruptHandler (miTimer0ISR);
    EUSART1_SetRxInterruptHandler(rxSerialISR);

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    printf("INICIO\n\r");
    uint8_t contador=0;
    adc_result_t convertedValue;     
 
    while (1)
    {
        //Lectura de potenciometro
//        ADCC_StartConversion(channel_ANA0);
//        while(!ADCC_IsConversionDone());
//        convertedValue = ADCC_GetConversionResult();
//        printf("A%d\r\n", convertedValue);
//        
//        //Lectura LDR
//        ADCC_StartConversion(channel_ANA1);
//        while(!ADCC_IsConversionDone());
//        convertedValue = ADCC_GetConversionResult();
//        printf("B%d\r\n", convertedValue);
//        
//        //Lectura LM35
//        ADCC_StartConversion(channel_ANA2);
//        while(!ADCC_IsConversionDone());
//        convertedValue = ADCC_GetConversionResult();
//        printf("C%d\r\n", convertedValue);
//        
//        //Lectura sensor SHARP
//        ADCC_StartConversion(channel_ANA4);
//        while(!ADCC_IsConversionDone());
//        convertedValue = ADCC_GetConversionResult();
//        printf("D%d\r\n", convertedValue);
        
//        Lectura sensor NTC
//        ADCC_StartConversion(channel_ANA5);
//        while(!ADCC_IsConversionDone());
//        convertedValue = ADCC_GetConversionResult();
//        printf("E:%d\n\r", convertedValue);
        
        
        //LATAbits.LATA5=~LATAbits.LATA5;
        // Logic to echo received data
//            if(EUSART1_is_rx_ready())
//            {
//                rxData = EUSART1_Read();
//                if(EUSART1_is_tx_ready())
//                {
//                    EUSART1_Write(rxData);
//                }
//            }
        __delay_ms(100);

    }
}

void miTimer0ISR(void){
    contador++;
    if(contador>10){
        //LATAbits.LATA5=~LATAbits.LATA5;
        contador=0;
    }
}

void rxSerialISR(void){
// Logic to echo received data
            if(eusart1RxCount!=0)
            {
                rxData = EUSART1_Read();
                if(EUSART1_is_tx_ready())
                {
                    EUSART1_Write(rxData);
                }
            }
}