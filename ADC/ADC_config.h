/******************************************************************/
// Auther  : Mazen Adeeb                                          //
// Date    : 10/11/2021                                           //
// version : 0.0.1                                                //
// Driver  : ADC_driver                                           //
/******************************************************************/

# ifndef ADC_CONFIG_H
# define ADC_CONFIG_H

# define ADC_u32TIMEOUT     20000


/*ADMUX REG BITS*/
# define ADC_REFS1          7
# define ADC_REFS0          6 
# define ADC_ADLAR          5

/*ADCSRA REG BIT*/
# define ADC_ADEN           7
# define ADC_ADSC           6
# define ADC_ADATE          5
# define ADC_ADIF           4
# define ADC_ADIE           3
# define ADC_ADPS2          2
# define ADC_ADPS1          1
# define ADC_ADPS0          0


/*ADC Options*/

/*Power source options*/
// 1- ADC_VOLTAGE_AREF
// 2- ADC_VOLTAGE_AVCC
// 3- ADC_VOLTAGE_INTER
# define ADC_POWER_SOURCE  ADC_VOLTAGE_INTER

/*Left ADJUSTMENT*/
// if you are using 8-bit mode set ADC_LEFT_ADJSTMENT to 1 and only read ADCH
# define ADC_LEFT_ADJSMENT      0 

/*AUTO TRIGGERING */
// 1- ADC_FREE_RUN
// 2- ADC_SINGLE_CONVERTION
# define ADC_MODE          ADC_SINGLE_CONVERTION


# endif