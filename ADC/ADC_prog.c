/******************************************************************/
// Auther  : Mazen Adeeb                                          //
// Date    : 10/11/2021                                           //
// version : 0.0.1                                                //
// Driver  : ADC_driver                                           //
/******************************************************************/

#include "std_types.h"
#include "bit_math.h"

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"

#include "DIO_interface.h"

static u8 ADC_u8BusyFlag = 0;

static void (*ADC_pfNotification)(u16) = NULL;

void ADC_voidInit(void)
{
    /* 1- Select Vref = AVCC
       2- Right Adjust
       3- Select clk
       4- Disable Auto trigger
       5- prescaler 46
       6- Enable ADC
    */
    // Select Vref
    #if ADC_POWER_SOUECE ==  ADC_VOLTAGE_INTER
    SET_BIT(ADC_u8_ADMUX_reg, ADC_REFS1);
    SET_BIT(ADC_u8_ADMUX_reg, ADC_REFS0);
    #elif ADC_POWER_SOUECE ==  ADC_VOLTAGE_AVCC
    CLEAR_BIT(ADC_u8_ADMUX_reg, ADC_REFS1);
    SET_BIT(ADC_u8_ADMUX_reg, ADC_REFS0);
    #elif ADC_POWER_SOUECE ==  ADC_VOLTAGE_AREF
    CLEAR_BIT(ADC_u8_ADMUX_reg, ADC_REFS1);
    CLEAR_BIT(ADC_u8_ADMUX_reg, ADC_REFS0);
    #endif

    // Select Right adjusment
    #if ADC_LEFT_ADJSMENT == 0 
    CLEAR_BIT(ADC_u8_ADMUX_reg, ADC_ADLAR);
    #else 
    SET_BIT(ADC_u8_ADMUX_reg, ADC_ADLAR);
    #endif

    // ADC MODE --> 1-ADC_FREE_RUN    2-ADC_SINGLE_CONVERTION 
    #if ADC_MODE == ADC_SINGLE_CONVERTION
    CLEAR_BIT(ADC_u8_ADCSRA_reg, ADC_ADATE);
    #elif ADC_MODE == ADC_FREE_RUN
    CLEAR_BIT(ADC_u8_ADCSRA_reg, ADC_ADATE);
    #endif

    // Select Clk
    SET_BIT(ADC_u8_ADCSRA_reg, ADC_ADPS2);
    SET_BIT(ADC_u8_ADCSRA_reg, ADC_ADPS1);
    CLEAR_BIT(ADC_u8_ADCSRA_reg, ADC_ADPS0);

    // Enable ADC
    SET_BIT(ADC_u8_ADCSRA_reg, ADC_ADEN);
}

u8 ADC_u8GetDigitalValueSyncNonBlocking(u8 copy_u8ChannelNumber, u16 *copy_pu16ReturnedValue)
{
    u32 Local_counter = 0;
    u8 Local_errorState = STD_Sucesses;

    if ((copy_u8ChannelNumber < 32) && (copy_pu16ReturnedValue != NULL))
    {
        /*Clear ADCMUX*/
        ADC_u8_ADMUX_reg &= 0b11100000;
        /*Select channel*/
        ADC_u8_ADMUX_reg |= copy_u8ChannelNumber;
        /*Start Convertion*/
        SET_BIT(ADC_u8_ADCSRA_reg, ADC_ADSC);
        /*Wait till flag is raised*/
        while (!GET_BIT(ADC_u8_ADCSRA_reg, ADC_ADIF) && (Local_counter < ADC_u32TIMEOUT))
        {
            Local_counter++;
        }
        if (Local_counter < ADC_u32TIMEOUT)
        {
            /*Clear Flag After raised*/
            SET_BIT(ADC_u8_ADCSRA_reg, ADC_ADIF);
            /*Read Digital Value*/
            *copy_pu16ReturnedValue = ADC_u16_ADC_REG;
        }
        else
        {
            Local_errorState = STD_Error;
        }
    }
    else
    {
        Local_errorState = STD_Error;
    }

    return Local_errorState;
}

u8 ADC_u8GetDigitalValueASync(u8 copy_u8ChannelNumber, void (*copy_pfNotificationFun)(u16))
{

    u8 Local_errorState = STD_Sucesses;
    if ((copy_u8ChannelNumber < 32) && (copy_pfNotificationFun != NULL) && (ADC_u8BusyFlag == 0))
    {

        /*Set Flag to busy*/
        ADC_u8BusyFlag = 1;
        /*update Global Pointer to a function*/
        ADC_pfNotification = copy_pfNotificationFun;
        /* Enable ADC Interrupt*/
        SET_BIT(ADC_u8_ADCSRA_reg, ADC_ADIE);
        /*Clear ADCMUX*/
        ADC_u8_ADMUX_reg &= 0b11100000;
        /*Select channel*/
        ADC_u8_ADMUX_reg |= copy_u8ChannelNumber;
        /*Start Convertion*/
        SET_BIT(ADC_u8_ADCSRA_reg, 6);
    }
    else
    {
        Local_errorState = STD_Error;
    }
    return Local_errorState;
}

u8 ADC_u8GetADCregVal(u16 *copy_pu16ADCval)
{
    u8 Local_errorState = STD_Sucesses;
    if (copy_pu16ADCval != NULL)
    {

        *copy_pu16ADCval = ADC_u16_ADC_REG;
    }
    else
    {
        Local_errorState = STD_Error;
    }
    return Local_errorState;
}

void __vector_16(void)     __attribute__((signal));
void __vector_16(void)
{
    if (ADC_pfNotification != NULL)
    {
        /*Clear Busy Flag*/
        ADC_u8BusyFlag = 0;
        /*CLear PIE of ADC*/
        CLEAR_BIT(ADC_u8_ADCSRA_reg, ADC_ADIE);
        /*Call Notification function*/
        ADC_pfNotification(ADC_u16_ADC_REG);
    }
}
