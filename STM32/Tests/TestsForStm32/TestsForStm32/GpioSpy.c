#include "GpioSpy.h"

bool aBtnState = false;
bool bBtnState = false;

static Node *pGpioList = NULL;

EmulatedGpioStatesStruct emulatedGpio = {0};

Status USER_GPIO_PushCommand(StateStruct *pCmd)
{
	if (pCmd == NULL) 
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(&pGpioList, *pCmd);

	return OK;
}

Status USER_GPIO_HandOverLocalList(Node **pMasterList)
{
	if (pMasterList == NULL)
	{
		return INVALID_PARAMETERS;
	}

	StateStruct temp;

	while (pGpioList != NULL)
	{
	temp = List_Pop(&pGpioList);
	List_PushBack(pMasterList, temp);
	}

	return OK;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_TIM_Base_Start_IT(&htim2);
	if ((GPIO_Pin & (A_BTN_Pin | B_BTN_Pin)) && ((aBtnState == false) || (bBtnState == false)))
	{

		if (GPIO_Pin & A_BTN_Pin)
		{
			aBtnState = true;
		}

		if (GPIO_Pin & B_BTN_Pin)
		{
			bBtnState = true;
		}
	}
}

GPIO_PinState HAL_GPIO_ReadPin(uint8_t GPIOx, uint16_t GPIO_Pin)
{
	if (GPIOx == A_BTN_GPIO_Port && GPIO_Pin == A_BTN_Pin)
	{
		return emulatedGpio.buttonA;
	}

	else if (GPIOx == B_BTN_GPIO_Port && GPIO_Pin == B_BTN_Pin)
	{
		return emulatedGpio.buttonB;
	}

	else if (GPIOx == A_CODE_0_GPIO_Port && GPIO_Pin == A_CODE_0_Pin)
	{
		return emulatedGpio.codeA0;
	}

	else if (GPIOx == A_CODE_1_GPIO_Port && GPIO_Pin == A_CODE_1_Pin)
	{
		return emulatedGpio.codeA1;
	}

	else if (GPIOx == B_CODE_0_GPIO_Port && GPIO_Pin == B_CODE_0_Pin)
	{
		return emulatedGpio.codeB0;
	}

	else if (GPIOx == B_CODE_1_GPIO_Port && GPIO_Pin == B_CODE_1_Pin)
	{
		return emulatedGpio.codeB1;
	}
}

void HAL_GPIO_WritePin(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) 
{
	switch (GPIOx) 
	{
		case GPIOA: 
		{
			switch (GPIO_Pin) 
			{
				case A_RELE_Pin: 
				{
					emulatedGpio.releA = PinState;
				}
				break;

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
				case PHET_Pin:
				{
					emulatedGpio.phet = PinState;
				}
				break;

				case DIR1_RELE_Pin:
				{
					emulatedGpio.releDir1 = PinState;
				}
				break;

				case A_LED_GREEN_Pin:
				{
					emulatedGpio.ledGreenA = PinState;
				}
				break;

				case A_LED_BLUE_Pin:
				{
					emulatedGpio.ledBlueA = PinState;
				}
				break;

				case B_LED_GREEN_Pin:
				{
					emulatedGpio.ledGreenB = PinState;
				}
				break;

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
				case B_RELE_Pin:
				{
					emulatedGpio.releB = PinState;
				}
				break;

				case DIR0_RELE_Pin:
				{
					emulatedGpio.releDir0 = PinState;
				}
				break;

				case B_LED_BLUE_Pin:
				{
					emulatedGpio.ledBlueB = PinState;
				}
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
		case A_RELE_Pin:
		{
			emulatedGpio.releA = !emulatedGpio.releA;
		}
		break;

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
		case PHET_Pin:
		{
			emulatedGpio.phet = !emulatedGpio.phet;
		}
		break;

		case DIR1_RELE_Pin:
		{
			emulatedGpio.releDir1 = !emulatedGpio.releDir1;
		}
		break;

		case A_LED_GREEN_Pin:
		{
			emulatedGpio.ledGreenA = !emulatedGpio.ledGreenA;
		}
		break;

		case A_LED_BLUE_Pin:
		{
			emulatedGpio.ledBlueA = !emulatedGpio.ledBlueA;
		}
		break;

		case B_LED_GREEN_Pin:
		{
			emulatedGpio.ledGreenB = !emulatedGpio.ledGreenB;
		}
		break;

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
		case B_RELE_Pin:
		{
			emulatedGpio.releB = !emulatedGpio.releB;
		}
		break;

		case DIR0_RELE_Pin:
		{
			emulatedGpio.releDir0 = !emulatedGpio.releDir0;
		}
		break;

		case B_LED_BLUE_Pin:
		{
			emulatedGpio.ledBlueB = !emulatedGpio.ledBlueB;
		}
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