#include "GpioSpy.h"

EmulatedGpioStatesStruct emulatedGpio = {0, 0, 0};

void HAL_GPIO_WritePin(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) 
{
	switch (GPIOx) 
	{
		case GPIOA: 
		{
			switch (GPIO_Pin) 
			{
				case A_LED_RED_Pin:
				{
					emulatedGpio.ledRedA = PinState;
				}
				break;
			}
		}
		break;

		case GPIOB:
		{
			switch (GPIO_Pin)
			{
				case B_LED_RED_Pin:
				{
					emulatedGpio.ledRedB = PinState;
				}
				break;

				case MCU_PROG_Pin:
				{
					emulatedGpio.mcuProg = PinState;
				}
				break;
			}
		}
		break;
		case GPIOC:
		{
			switch (GPIO_Pin)
			{
				break;
			}
		}
		break;
	}
}

void HAL_GPIO_TogglePin(uint8_t GPIOx, uint16_t GPIO_Pin)
{
	switch (GPIOx)
	{
	case GPIOA:
	{
		switch (GPIO_Pin)
		{
		case A_LED_RED_Pin:
		{
			emulatedGpio.ledRedA = !emulatedGpio.ledRedA;
		}
		break;
		}
	}
	break;

	case GPIOB:
	{
		switch (GPIO_Pin)
		{

		case B_LED_RED_Pin:
		{
			emulatedGpio.ledRedB = !emulatedGpio.ledRedB;
		}
		break;

		case MCU_PROG_Pin:
		{
			emulatedGpio.mcuProg = !emulatedGpio.mcuProg;
		}
		break;
		}
	}
	break;
	case GPIOC:
	{
		switch (GPIO_Pin)
		{
			break;
		}
	}
	break;
	}
}

//ToDo: Place in different location
void HAL_Delay() 
{
	return;
}