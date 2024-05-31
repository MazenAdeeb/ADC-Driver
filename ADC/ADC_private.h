/******************************************************************/
// Auther  : Mazen Adeeb                                          //
// Date    : 10/11/2021                                           //
// version : 0.0.1                                                //
// Driver  : ADC_driver                                           //
/******************************************************************/


# ifndef ADC_private_H
# define ADC_private_H

# define ADC_u8_ADMUX_reg       *((volatile u8*)0x27)
# define ADC_u8_ADCSRA_reg      *((volatile u8*)0x26)
# define ADC_u8_ADCH_reg        *((volatile u8*)0x25)
# define ADC_u8_ADCL_reg        *((volatile u8*)0x24)

# define ADC_u16_ADC_REG         *((volatile u16*)0x24)
# define SFIOR                   *((volatile u8*)0x50)


# define ADC_VOLTAGE_AREF    1
# define ADC_VOLTAGE_AVCC    2
# define ADC_VOLTAGE_INTER   3 

# define ADC_FREE_RUN        1
# define ADC_SINGLE_RUN      0
# endif