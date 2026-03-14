//The Basic jump to the new application at newer flash address 0x0808 0000 (512 KB),256 aligned for vector table

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "Register_Definitions.h"

#define SCB_BASE					(0xE000ED00U)
#define SCB_VTOR					*((volatile uint32_t *)(SCB_BASE + 0x08U))

#define APP_ADDRESS					(0x08080000U)
#define VECTOR_TABLE_ADDRESS		(APP_ADDRESS)

void Jump_To_Application(void)
{
	typedef void (*pFunction)(void);
	pFunction jumpToApp;

	// Setting up Stack and Reset Handler pointer
	uint32_t appStackPointer = *((volatile uint32_t *)(APP_ADDRESS + 0));
	uint32_t appResetHandler = *((volatile uint32_t *)(APP_ADDRESS + 4));

	//Disabling the all Maskable Interrupts
	// Change processor state interrupt disable, PRIMASK = 1
	__asm volatile("cpsid i" : : : "memory");

	// Setting up the SCB->VTOR to new APP Address
	SCB_VTOR = VECTOR_TABLE_ADDRESS;

	// Setting up the Main Stack Pointer from the Vector Table.
	//Standard Inline assembly structure
	__asm volatile("msr msp, %0" : : "r" (appStackPointer) : );

	// Setting up the Reset Handler as a function pointer
	// Making it a function pointer
	jumpToApp = (pFunction)appResetHandler;



	// Jump
	jumpToApp();

}

int IsButtonPresses()
{
	// Enabling RCC for GPIOD port
	RCC_AHB2ENR |= GPIODEN;

	// Set the MODE = INPUT
	GPIOD_MODER &= ~(3U << bit_0);

	// Set the PULL UP
	GPIOD_PUPDR |= (1U << 0);
	GPIOD_PUPDR &= ~(1U << 1);


	return (GPIOD_IDR & (1U << 0));
}
int main()
{
	if(IsButtonPresses()){
		// Can wait for an update or Event
		// Or Firmware Update
		while(1);
	}else{
		Jump_To_Application();
	}
	return 0;
}
