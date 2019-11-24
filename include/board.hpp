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

#ifndef OSSHS_BOARD_HPP
#define OSSHS_BOARD_HPP

#include <modm/platform.hpp>

namespace osshs
{
	namespace board
	{
		using namespace modm::literals;

		using StatusLed = modm::platform::GpioInverted<modm::platform::GpioOutputC13>;

		struct SystemClock
		{
			static constexpr uint32_t Frequency = 72_MHz;
			static constexpr uint32_t Ahb = Frequency;
			static constexpr uint32_t Apb1 = Frequency / 2;
			static constexpr uint32_t Apb2 = Frequency;

			static constexpr uint32_t Adc  = Apb2;

			static constexpr uint32_t Spi1 = Apb2;
			static constexpr uint32_t Spi2 = Apb1;
			static constexpr uint32_t Spi3 = Apb1;

			static constexpr uint32_t Usart1 = Apb2;
			static constexpr uint32_t Usart2 = Apb1;
			static constexpr uint32_t Usart3 = Apb1;
			static constexpr uint32_t Uart4  = Apb1;
			static constexpr uint32_t Uart5  = Apb1;

			static constexpr uint32_t Can    = Apb1;

			static constexpr uint32_t I2c1   = Apb1;
			static constexpr uint32_t I2c2   = Apb1;

			static constexpr uint32_t Apb1Timer = Apb1 * 2;
			static constexpr uint32_t Apb2Timer = Apb2 * 1;
			static constexpr uint32_t Timer1  = Apb2Timer;
			static constexpr uint32_t Timer2  = Apb1Timer;
			static constexpr uint32_t Timer3  = Apb1Timer;
			static constexpr uint32_t Timer4  = Apb1Timer;
		};

		inline void
		initialize()
		{
			modm::platform::Rcc::enableExternalCrystal();
			modm::platform::Rcc::enablePll(modm::platform::Rcc::PllSource::ExternalCrystal, 9);
			modm::platform::Rcc::setFlashLatency<SystemClock::Frequency>();
			modm::platform::Rcc::enableSystemClock(modm::platform::Rcc::SystemClockSource::Pll);
			modm::platform::Rcc::setAhbPrescaler(modm::platform::Rcc::AhbPrescaler::Div1);
			modm::platform::Rcc::setApb1Prescaler(modm::platform::Rcc::Apb1Prescaler::Div2);
			modm::platform::Rcc::setApb2Prescaler(modm::platform::Rcc::Apb2Prescaler::Div1);
			modm::platform::Rcc::updateCoreFrequency<SystemClock::Frequency>();

			modm::platform::SysTickTimer::initialize<SystemClock>();

			StatusLed::setOutput(modm::Gpio::Low);
		}
	}
}

#endif	// OSSHS_BOARD_HPP
