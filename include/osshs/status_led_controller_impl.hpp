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

#ifndef OSSHS_STATUS_LED_CONTROLLER_HPP
	#error "Don't include this file directly, use 'status_led_controller.hpp' instead!"
#endif

namespace osshs
{
	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	typename StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::Status StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::status;

	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	uint16_t StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::counter = 0;

	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	void
	StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::initialize(Status status)
	{
		setStatus(status);
		enable();
	}

	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	void
	StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::enable()
	{
		TIMER::enable();

		// Interrupt every 100ms
		TIMER::template setPeriod<SYSTEM_CLOCK>(100000);
		TIMER::setMode(TIMER::Mode::UpCounter);

		TIMER::enableInterruptVector(true, 10);
		TIMER::enableInterrupt(TIMER::Interrupt::Update);

		TIMER::applyAndReset();
		TIMER::start();
	}

	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	void
	StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::disable()
	{
		TIMER::pause();

		TIMER::disableInterrupt(TIMER::Interrupt::Update);
		TIMER::enableInterruptVector(false, 10);

		TIMER::disable();
	}

	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	void
	StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::setStatus(Status status)
	{
		StatusLedController::status = status;
	}

	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	void
	StatusLedController<TIMER, STATUS_LED, SYSTEM_CLOCK>::update()
	{
		switch(status)
		{
			// 3 long blinks
			case Status::BOOTLOADER_ACTIVE:
				counter = counter % 55;
				
				// Long blink
				if (counter == 0)
					STATUS_LED::set();
				if (counter == 10)
					STATUS_LED::reset();
				
				// Long blink
				if (counter == 15)
					STATUS_LED::set();
				if (counter == 25)
					STATUS_LED::reset();
				
				// Long blink
				if (counter == 30)
					STATUS_LED::set();
				if (counter == 40)
					STATUS_LED::reset();
				break;

			// 1 long and 2 short blinks
			case Status::APPLICATION_ERROR:
				counter = counter % 39;
				
				// Long blink
				if (counter == 0)
					STATUS_LED::set();
				if (counter == 10)
					STATUS_LED::reset();

				// Short blink
				if (counter == 15)
					STATUS_LED::set();
				if (counter == 17)
					STATUS_LED::reset();

				// Short blink
				if (counter == 22)
					STATUS_LED::set();
				if (counter == 24)
					STATUS_LED::reset();
				break;
			
			// 1 short and 2 long blinks
			case Status::BOOTLOADER_ERROR:
				counter = counter % 47;
				
				// Short blink
				if (counter == 0)
					STATUS_LED::set();
				if (counter == 2)
					STATUS_LED::reset();
				
				// Long blink
				if (counter == 7)
					STATUS_LED::set();
				if (counter == 17)
					STATUS_LED::reset();
				
				// Long blink
				if (counter == 22)
					STATUS_LED::set();
				if (counter == 32)
					STATUS_LED::reset();
				break;
			
			// Always on
			default:
				STATUS_LED::set();
				break;
		}

		counter++;
	}
}
