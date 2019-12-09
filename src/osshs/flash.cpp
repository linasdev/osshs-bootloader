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

#include <osshs/log/logger.hpp>
#include <osshs/flash.hpp>
#include <modm/platform.hpp>

namespace osshs
{
		bool
		Flash::isLocked()
		{
			return FLASH->CR & FLASH_CR_LOCK;
		}

		bool
		Flash::unlock()
		{
			OSSHS_LOG_INFO("Unlocking flash.");

			FLASH->KEYR = KEY1;
			FLASH->KEYR = KEY2;

			if (isLocked())
			{
				OSSHS_LOG_ERROR("Unlocking flash failed.");
				return false;
			}

			OSSHS_LOG_INFO("Unlocking flash succeeded.");
			return true;
		}

		void
		Flash::lock()
		{
			OSSHS_LOG_INFO("Locking flash.");

			FLASH->CR |= FLASH_CR_LOCK;
		}

		uint16_t
		Flash::readHalfWord(uint32_t address)
		{
			uint16_t value = *reinterpret_cast<uint16_t *>(address);

			OSSHS_LOG_DEBUG("Reading half word from flash(address = `0x%08x`, value = `0x%04x`).", address, value);

			return value;
		}

		bool
		Flash::writeHalfWord(uint32_t address, uint16_t value)
		{
			OSSHS_LOG_DEBUG("Writing half word to flash(address = `0x%08x`, value = `0x%04x`).", address, value);

			FLASH->CR |= FLASH_CR_PG;

			*reinterpret_cast<volatile uint16_t *>(address) = value;

			while(FLASH->SR & FLASH_SR_BSY);

			if (readHalfWord(address) == value)
				return true;

			OSSHS_LOG_ERROR("Writing half word to flash failed(address = `0x%08x`, value = `0x%04x`).", address, value);
			return false;
		}
}
