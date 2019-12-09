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
#define OSSHS_STATUS_LED_CONTROLLER_HPP

#include <modm/platform.hpp>

namespace osshs
{
	template<typename TIMER, typename STATUS_LED, typename SYSTEM_CLOCK>
	class StatusLedController
	{
	public:
		enum class Status : uint32_t
		{
			BOOTLOADER_ACTIVE,
			APPLICATION_ERROR,
			BOOTLOADER_ERROR
		};

		/**
		 * @brief Enable the status led timer.
		 */
		static void
		enable();

		/**
		 * @brief Disable the status led timer.
		 */
		static void
		disable();

		/**
		 * @brief Set current status.
		 * @param status Status to set.
		 */
		static void
		setStatus(Status status);

		/**
		 * @brief Update status animations.
		 * @note Should be called from the timer interrupt setup by enable().
		 */
		static void
		update();
	private:
		static Status status;
		static uint16_t counter;
  };
}

#include <osshs/status_led_controller_impl.hpp>

#endif  // OSSHS_STATUS_LED_CONTROLLER_HPP
