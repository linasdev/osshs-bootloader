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

#ifndef OSSHS_FLASH_HPP
#define OSSHS_FLASH_HPP

#include <cstdint>
#include <memory>

#define OSSHS_FLASH_KEY_RDPRT 0x00A5
#define OSSHS_FLASH_KEY1 			0x45670123
#define OSSHS_FLASH_KEY2 			0xCDEF89AB

#define OSSHS_FLASH_ORIGIN    0x08000000
#define OSSHS_FLASH_PAGE_SIZE 0x0400

namespace osshs
{
	class Flash
	{
	public:
		/**
		 * @brief Check if flash is locked.
		 * @note Writing to flash is only possible if it is unlocked.
		 * @return Whether or not the FLASH_CR register is locked.
		 */
		static bool
		isLocked();
		
		/**
		 * @brief Unlock flash.
		 * @note Writing to flash is only possible if it is unlocked.
		 * @return Whether or not unlocking succeeded.
		 */
		static bool
		unlock();

		/**
		 * @brief Lock flash.
		 * @note Writing to flash is only possible if it is unlocked.
		 */
		static void
		lock();

		/**
		 * @brief Read a value from flash.
		 * @param address Address where the value should be read from.
		 * @return Value read from flash.
		 */
		static uint16_t
		readHalfWord(uint32_t address);

		/**
		 * @brief Write a value to flash.
		 * @note The page in which the address resides must be erased before writing to it.
		 * @param address Address where the value should be written to.
		 * @param value Value to write.
		 * @return Whether or not writing succeeded.
		 */
		static bool
		writeHalfWord(uint32_t address, uint16_t value);

		/**
		 * @brief Erase a page.
		 * @note Required for writing to any address within the page.
		 * @param address Origin address of any page.
		 * @return Whether or not erasing succeeded.
		 */
		static bool
		erasePage(uint32_t address);

		/**
		 * @brief Read a whole page from flash.
		 * @note The size of the buffer provided must be OSSHS_FLASH_PAGE_SIZE.
		 * @param address Origin address of any page.
		 * @param buffer A std::unique_ptr<uint8_t[]> to a buffer that will contain the page read. 
		 * @return Whether or not reading succeeded.
		 */
		static bool
		readPage(uint32_t address, std::unique_ptr<uint8_t[]> &buffer);

		/**
		 * @brief Erase and write a whole page to flash.
		 * @note The size of the buffer provided must be OSSHS_FLASH_PAGE_SIZE.
		 * @param address Origin address of any page.
		 * @param buffer A std::unique_ptr<uint8_t[]> to a buffer that contains the page to be written.
		 * @return Whether or not writing succeeded.
		 */
		static bool
		writePage(uint32_t address, std::unique_ptr<uint8_t[]> &buffer);

	private:
		/**
		 * @brief Reverse the order of bits of a word.
		 * @param value Original value.
		 * @return Reflected value.
		 */
		static uint32_t
		reflectWord(uint32_t value);
	};
}

#endif  // OSSHS_FLASH_HPP
