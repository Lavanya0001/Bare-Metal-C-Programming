/*P1_LED_BLINK: Datasheet + Reference Manual*/

#include <stdio.h>
#include "Register_Definitions.h"

void LED_Func()
{	//Enabling RCC for GPIOB port
	RCC_AHB2ENR |= GPIOBEN;

	//First clear the Mode for B0,B1,B5
	GPIOB_MODER &= ~(3U << bit_0);
	GPIOB_MODER &= ~(3U << bit_1);
	GPIOB_MODER &= ~(3U << bit_5);

	//Set the MODE = OUTPUT
	GPIOB_MODER |= (1U << 0);
	GPIOB_MODER &= ~(1U << 1);

	//Set the MODE = OUTPUT
	GPIOB_MODER |= (1U << 2);
	GPIOB_MODER &= ~(1U << 3);

	//Set the MODE = OUTPUT
	GPIOB_MODER |= (1U << 10);
	GPIOB_MODER &= ~(1U << 11);


	GPIOB_ODR |= (USER_BLUE_LED);
	GPIOB_ODR |= (USER_GREEN_LED);
	GPIOB_ODR |= (USER_RED_LED);

}
int main(){
	LED_Func();

	while(1){}
	return 0;
}
