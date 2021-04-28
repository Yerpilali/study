//----------------------------------------------------------------------------------------------------------------------------------------------
//
//Цель: разработать программу реализующую мигание светодиода
//
//Решаемые проектом задачи:
//	1. Реализовать мигание светодиода
//	5. Реализовать управление временем задержки используя микропереключатели SW3 и SW4
//----------------------------------------------------------------------------------------------------------------------------------------------

#include "main.h"	//Заголовчоный файл с описанием подключаемых библиотечных модулей

//main обязательная функция для исполнегия кода пользователя
//После подачи питания или щелчка кнопкой "reset" стартует Загрузкчик, который выполняет начальную настройку основых регистров микроконтроллера 
//В завершение работы Загрузчик передаёт управление микроконтроллером функции main                
int main(void)
{
	uint32_t half_period;																				//Половина периода мигания светодиода
	uint32_t n;																									//Степень коэффициента базовой задержки: K=2^n
	//Конфигурирование портов GPIO 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;													//Включение тактирования порта B: RCC_AHBENR_GPIOBEN=0x00040000
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER8_0;  //Переключение линий 0,8 порта B в режим "Output"
	GPIOB->MODER&=~( GPIO_MODER_MODER12 | GPIO_MODER_MODER13);	//Переключаем линий 12(SW4),13(SW3) порта B в режим "Input"
	GPIOB->ODR |=0x100;																					//Разрешение работы cdtnjlbjljd на стенде с помощбю установки логической "1" на выводе РВ.8
	half_period = 50000;																				//Задание величины базовой задержки
	//Реализация процесса мигания светодиода
	while(1)
	{
		n=((GPIOB->IDR)&0x3000)>>12;															//Определение степени коэффициента базовой задержки
		GPIOB->BSRR=0x1;																					//Зажигание светодиода на выводе PB.0
		delay(half_period<<n);																		//Задержка после включения светодиода 
		GPIOB->BSRR=0x10000;																			//Выключение светодиода 
		delay(half_period<<n);																		//Задержка после выключения светодиода
	}
}
//функция задержки: count - количество элементарных периодов задержки с длительностью примерно 2,5 мкс
void delay(uint32_t count)
{
	volatile uint32_t i;																				//объявляем неоптимизируемую переменную
	for (i = 0;i<count;i++);																		//выполнение пустых циклов для реализации програмной задержки
}
//Руководство пользователя:
//	1. для запуска загруженной программы удалите перемычку "boot" на стенде и нажмите кнопку "reset"
//	2. В управлении частотой мигания светодиода используйте микропереключатели SW3(старший	разряд) и SW4 (младший разряд)
//	3. Примерная частота мигания: 00 - 4 Гц; 01 - 2 Гц; 10 - 1 Гц; 11 - 0.5 Гц
//	4. Интервал между переключениями светодиода задается с помощью программной задержки
