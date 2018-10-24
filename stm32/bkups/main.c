/* GVV Sharma 
 * September 24, 2018
 * Adapted from LCD code for AVR-GCC
 * Augusto Fraga Giachero, 2015
 * Display string on 16x2 HD44780-controlled LCD
 * 
 * Released under GNU GPL
 */

#include "stm32f103xb.h"
#include "lcd.h"
#include "stdlib.h"

/*
 * Delay function:
 * Uses the SysTick timer to wait for
 * an abitrary time in microseconds.
 *
 * The clock source is assumed to be
 * the internal 8MHz RC oscilator
 */
void delay_us(unsigned int time)
{
	/*
	 * (source is 1MHz and the time is specified in us)
	 */
	SysTick->LOAD = 3*time;

	/*
	 * Clears the current value and the count flag
	 */
	SysTick->VAL = 0;

	/*
	 * Waits until the count ends
	 */
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}


/*
 * Performs an analog to digital
 * conversion
 */
uint16_t ADC_Read(unsigned int channel)
{
	/*
	 * Selects the ADC channel
	 */
	ADC1->SQR1 = (1 << ADC_SQR1_L_Pos);
	ADC1->SQR3 = (channel & ADC_SQR3_SQ1_Msk);
	
	/*
	 * Starts the conversion
	 */
	ADC1->CR2 |= ADC_CR2_ADON;

	/*
	 * Waits until the conversion has
	 * finished
	 */
	while((ADC1->SR & ADC_SR_EOS) == 0);

	/*
	 * Returns the acquired value
	 */
	return ADC1->DR;
}

// MAIN PROGRAM
int main(void)
{
	char adstr[6];
	unsigned int ad_acc, i;

	/*
	 * Enable all Ports and Alternate Function clocks
	 * and the ADC clock
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN |
		RCC_APB2ENR_ADC1EN;
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	/*
	 * Enable the high speed external
	 * oscillator
	 */
	RCC->CR |= RCC_CR_HSEON;
	
	/*
	 * Waits until the external oscillator
	 * is ready
	 */
	while((RCC->CR & RCC_CR_HSERDY) == 0);

	/*
	 * PLL Source: HSE
	 * PLL Multiply Factor: 6
	 * USB Prescaler: 1
	 * AHB Prescaler: 2
	 * APB1 Prescaler: 1
	 * APB2 Prescaler: 1
	 * ADC Prescaler: 2
	 */
	RCC->CFGR = RCC_CFGR_PLLMULL6 | RCC_CFGR_PPRE2_DIV1 |
		RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_ADCPRE_DIV2 |
		RCC_CFGR_PLLSRC | RCC_CFGR_HPRE_DIV2 | RCC_CFGR_USBPRE;

	/*
	 * Enable the PLL
	 */
	RCC->CR |= RCC_CR_PLLON;

	/*
	 * Waits until the PLL is ready
	 */
	while((RCC->CR & RCC_CR_PLLRDY) == 0);

	/*
	 * Switch the System clock to the PLL
	 */
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW_PLL) | RCC_CFGR_SW_PLL;

	/*
	 * Updates the SystemCoreClock variable
	 * Now the CPU clock is 3*HSE (24MHz for
	 * an 8MHz oscillator)
	 */
	SystemCoreClockUpdate();
	
	/*
	 * Enable the SysTick Timer with
	 * the CPU clock divided by 8
	 */
	SysTick->CTRL = SysTick_CTRL_ENABLE;

	/*
	 * Enable the Analog to Digital
	 * converter
	 */
	ADC1->CR2 = ADC_CR2_ADON;

	/*
	 * Selects the PA9 as the USART1 RX
	 * Selects the PA10 as the USART1 TX
	 */
//	GPIOA->CRH = (GPIOA->CRH & 0xFFFFF00F) | 0x000004B0;

	/*
	 * Enable the clock for the USART1
	 */
//	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	/*
	 * Adjusts the USART1 bit rate to
	 * 38400 bps (for an 24MHz input clock)
	 */
//	USART1->BRR = 0x271;

	/*
	 * Enable the USART1 Transmitter and
	 * Receiver
	 */
//	USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;

	/*
	 * Starts the ADC calibration
	 */
	ADC1->CR2 |= ADC_CR2_CAL;

	/*
	 * Waits until the calibration has
	 * finished
	 */
	while(ADC1->CR2 & ADC_CR2_CAL);


GPIOA->CRL = (GPIOA->CRL & 0xFF000000) | 0x00333333;//set A0-A5 as outputs

 LCD_Init(); // initialize LCD controller

 while(1)
 {

		/*
		 * Accumulate 32 measures
		 */
		ad_acc = 0;
		for (i = 0; i < 32; i++)
		{
			ad_acc += ADC_Read(0);
		}

		/*
		 * Divide the accumulated measures
		 * by 32 and convert it to a string
		 */
		itoa(ad_acc >> 5, adstr, 10);

		///*
		 //* Prints the analog value through
		 //* the serial port
		 //*/
		//Puts_USART1(adstr);
		//Puts_USART1("\r\n");

		//delay_us(500000); //500ms delay

LCD_Clear();
LCD_Message(adstr); 

delay_us(600000);     // set animation speed 600 ms
}
}
