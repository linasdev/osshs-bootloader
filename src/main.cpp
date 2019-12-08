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
#include <osshs/log/logger.hpp>
#include <modm/architecture/interface/interrupt.hpp>

using namespace modm::literals;
using StatusIndicator = osshs::StatusLedController<modm::platform::Timer2, osshs::board::StatusLed, osshs::board::SystemClock>;

OSSHS_ENABLE_LOGGER(modm::platform::Usart1, modm::IOBuffer::BlockIfFull);

int
main()
{
	osshs::board::initialize();

	OSSHS_LOG_SET_LEVEL(osshs::log::Level::DEBUG);

	osshs::Bootloader::initialize();
	
	StatusIndicator::enable();
	StatusIndicator::setStatus(StatusIndicator::Status::BOOTLOADER_ACTIVE);

	if(osshs::Bootloader::shouldLoadApplication())
	{
		OSSHS_LOG_INFO("Loading application.");

		if(osshs::Bootloader::checkApplication())
		{
			StatusIndicator::disable();
			osshs::Bootloader::deinitialize();

			OSSHS_LOG_FLUSH();

			osshs::board::deinitialize();
			osshs::Bootloader::loadApplication();
			return 0;
		}

		OSSHS_LOG_ERROR("Application is invalid.");

		StatusIndicator::setStatus(StatusIndicator::Status::APPLICATION_ERROR);
	}

	while(true);

	return 0;
}

MODM_ISR(TIM2)
{
	modm::platform::Timer2::acknowledgeInterruptFlags(modm::platform::GeneralPurposeTimer::InterruptFlag::Update);
	StatusIndicator::update();
}
