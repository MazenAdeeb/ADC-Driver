/******************************************************************/
// Auther  : Mazen Adeeb                                          //
// Date    : 10/11/2021                                           //
// version : 0.0.1                                                //
// Driver  : ADC_driver                                           //
/******************************************************************/

# ifndef ADC_INTERFACE_H
# define ADC_INTERFACE_H


/*Macros for chanel*/

# define ADC_u8_CHANNEL0        0
# define ADC_u8_CHANNEL1        1
# define ADC_u8_CHANNEL2        2
# define ADC_u8_CHANNEL3        3
# define ADC_u8_CHANNEL4        4
# define ADC_u8_CHANNEL5        5
# define ADC_u8_CHANNEL6        6
# define ADC_u8_CHANNEL7        7


void ADC_voidInit(void);

u8 ADC_u8GetDigitalValueSyncNonBlocking(u8 copy_u8ChannelNumber, u16 *copy_pu16ReturnedValue);

u8 ADC_u8GetDigitalValueASync(u8 copy_u8ChannelNumber, void (*copy_pfNotificationFun)(u16));
u8 ADC_u8GetADCregVal (u16 *copy_pu16ADCval);
# endif