#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"

void gpioConfig(){
	GPIO_InitTypeDef	GPIOInitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	// led config
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIOInitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2;
	GPIOInitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOInitStructure);
	// pot config
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_AN;
	GPIOInitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIOInitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA,&GPIOInitStructure);
}

void adcConfig(){
	ADC_InitTypeDef	ADCInitStructure;
	ADC_CommonInitTypeDef	ADCCommonInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	ADCCommonInitStructure.ADC_Mode=ADC_Mode_Independent;
	ADCCommonInitStructure.ADC_Prescaler=ADC_Prescaler_Div4;

	ADC_CommonInit(&ADCCommonInitStructure);

	ADCInitStructure.ADC_ContinuousConvMode=ENABLE;
	ADCInitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADCInitStructure.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
	ADCInitStructure.ADC_NbrOfConversion=1;
	ADCInitStructure.ADC_Resolution=ADC_Resolution_12b;
	ADCInitStructure.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADCInitStructure);
	ADC_Cmd(ADC1,ENABLE);

}

uint16_t readADC(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC1);
}
uint16_t adcValue=0;



int main(void){
	gpioConfig();
	adcConfig();


  while (1){

	  adcValue=readADC();
	  if(adcValue <11000){
		  GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);


	  }
	  else{
		  GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
	  }

  }
}
