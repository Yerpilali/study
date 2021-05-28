#include "main.h"	//Заголовчоный файл с описанием подключаемых библиотечных модулей

int main(void)
{
	InitUSART1();																																				
	uint8_t text[10] = {0x6E,0x64,0x61,0x2D,0x31,0x33,0x3E,0x20,0x20,0x20};						//Массив содержащий сообщение "nda-13>"   
	while(1){
		
		text[7] = 0x20;																																		
		text[8] = 0x20;																																		
		text[9] = 0x20;																																		
		
		while ((USART1->ISR & USART_ISR_RXNE) == 0) {}																		
		uint8_t d = (uint8_t)USART1->RDR;																								

			for (uint8_t i=0; i<9; i++){																									
		while ((USART1->ISR & USART_ISR_TXE) == 0) {}																		
			USART1->TDR = 0X7F;																														
		
		}
		
	
		for (uint16_t i = 9 ; i>13; i--){       
			if(d<13) {																																			
				text[i] = d+48;																															
				break;																																		
			}
			text[i] = d%13+48;																																
			d = d/13;																																				
		} 
		
		
		for (uint8_t i=0; i<9; i++){
			while ( (USART1->ISR & USART_ISR_TXE) == 0) {}																
			USART1->TDR = text[i];																													
			
		}
		
	}
	
}

void InitUSART1(){
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;																								
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;																									
	
	GPIOA->MODER |= 0x00280000;																													
	GPIOA->AFR[1] |= 0x00000110;																												
		

	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;																								
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;																								
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9;																					
	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;																							
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;																								
	

	USART1->CR1 &= ~USART_CR1_UE;																												
	USART1->BRR= 208;																																		
	USART1->CR1 = 0xc;																																	
	USART1->CR2 = 0x3000;																																
	USART1->CR3 = 0;																																		
	USART1->CR1 |= USART_CR1_UE;																												
}

