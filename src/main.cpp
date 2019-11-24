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

#include <board.hpp>
#include <osshs/bootloader.hpp>
#include <osshs/status_led_controller.hpp>
#include <modm/architecture/interface/interrupt.hpp>

using StatusIndicator = osshs::StatusLedController<modm::platform::Timer2, osshs::board::StatusLed, osshs::board::SystemClock>;

MODM_ISR(TIM2)
{
	modm::platform::Timer2::acknowledgeInterruptFlags(modm::platform::GeneralPurposeTimer::InterruptFlag::Update);
	StatusIndicator::update();
}

int
main()
{
	osshs::Bootloader::initialize();

	if(osshs::Bootloader::shouldLoadApplication())
	{
		if(osshs::Bootloader::checkApplication())
		{
			osshs::Bootloader::deinitialize();
			osshs::Bootloader::loadApplication();
			return 0;
		}

		osshs::board::initialize();
		StatusIndicator::initialize(StatusIndicator::Status::APPLICATION_ERROR);
	}
	else
	{
		osshs::board::initialize();
		StatusIndicator::initialize();
	}

	while(true);

	return 0;
}
