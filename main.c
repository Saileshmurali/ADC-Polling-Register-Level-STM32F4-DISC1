#include "stm32f4xx.h"
void ADC_Init(void);
void ADC_Enable(void);
void ADC_Start(int);
void ADC_Init (void)
{
//1. Enable ADC and GPIO clock
	RCC->APB2ENR |= (1<<8);  // enable ADC1 clock
	RCC->AHB1ENR |= (1<<0);  // enable GPIOA clock

//2. Set the pre-scalar in the Common Control Register (CCR)
	ADC->CCR |= 1<<16;  		 // PCLK2 divide by 4, works at 4MHz

//3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)
	ADC1->CR1 = (1<<8);    // SCAN mode enabled
	ADC1->CR1 &= ~(1<<24);   // 12 bit RES

//4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
	ADC1->CR2 |= (1<<1);     // enable continuous conversion mode
	ADC1->CR2 |= (1<<10);    // EOC after each conversion
	ADC1->CR2 &= ~(1<<11);   // Data Alignment RIGHT

//5. Set the Sampling Time for the channels
	ADC1->SMPR2 &= ~(1<<0);  // Sampling time of 3 cycles for channel 0

//6. Set the Regular channel sequence length in ADC_SQR1
	ADC1->SQR1 &= ~(1<<20);   // SQR1_L =0 for 1 conversion

//7. Set the Respective GPIO PIN in the Analog Mode
	GPIOA->MODER |= (3<<0);  // analog mode for PA 0 (channel 0)
}

uint16_t ADC_VAL=0;

int main ()
{

	ADC_Init ();
	ADC1->CR2 |= 1<<0;   // ADON =1 enable ADC1
	uint32_t delay = 10000;
	while (delay--);//Wait sometime for ADC to start
	while (1)
	{
		ADC1->SQR3 = 0;
		ADC1->SQR3 |= (0<<0);//give the corresponding channel of ADC used in conversion
		ADC1->SR = 0;        // clear the status register
		ADC1->CR2 |= (1<<30);  // start the conversion
		while (!(ADC1->SR & (1<<1)));  // wait for EOC flag to set
		ADC_VAL=ADC1->DR;
	}

}
