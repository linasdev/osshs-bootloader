/*
 * MIT License
 *
 * Copyright (c) 2019 Linas Nikiperavicius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <osshs/bootloader.hpp>
#include <modm/platform.hpp>

namespace osshs
{
	void
	Bootloader::initialize()
	{
		// Enable the power and backup interface clocks.
		RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;
	}

	bool
	Bootloader::shouldLoadApplication()
	{
		return (BKP->DR1 & 0x1) == 0;
	}

	void
	Bootloader::setLoadApplication(bool loadApplication)
	{
		PWR->CR |= PWR_CR_DBP;

		if (loadApplication)
		{
			BKP->DR1 &= ~0x1;
		}
		else
		{
			BKP->DR1 |= 0x1;
		}

		PWR->CR &= ~PWR_CR_DBP;
	}

	bool
	Bootloader::checkApplication()
	{
		uint32_t stackPointer = *reinterpret_cast<uint32_t *>(OSSHS_BOOTLOADER_APPLICATION_ORIGIN);
		return (stackPointer - OSSHS_BOOTLOADER_RAM_ORIGIN) < OSSHS_BOOTLOADER_RAM_LENGTH;
	}

	void
	Bootloader::loadApplication()
	{
		// Use the application's vector table.
		SCB->VTOR = OSSHS_BOOTLOADER_APPLICATION_ORIGIN;

		// Use the application's stack pointer as the Main Stack Pointer (MSP).
		__asm__ volatile ("MSR msp, %0" : : "r" (*reinterpret_cast<uint32_t *>(OSSHS_BOOTLOADER_APPLICATION_ORIGIN)) : );

		// Call the application's entry point.
		(*reinterpret_cast<void(**)()>(OSSHS_BOOTLOADER_APPLICATION_ORIGIN + 4))();
	}

	void
	Bootloader::deinitialize()
	{
		// Disable the power and backup interface clocks.
		RCC->APB1ENR &= ~(RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);
	}
}
