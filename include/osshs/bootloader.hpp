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

#ifndef OSSHS_BOOTLOADER_HPP
#define OSSHS_BOOTLOADER_HPP

#define OSSHS_BOOTLOADER_APPLICATION_ORIGIN 0x08004000
#define OSSHS_BOOTLOADER_APPLICATION_LENGTH 0x00020000

#define OSSHS_BOOTLOADER_RAM_ORIGIN 0x20000000
#define OSSHS_BOOTLOADER_RAM_LENGTH 0x00005000

namespace osshs
{
	class Bootloader
	{
	public:
		/**
		 * @brief Initialize the bootloader.
		 */
		static void
		initialize();

		/**
		 * @brief Check whether or not the bootloader should load the application.
		 * @return Whether or not the bootloader should load the application.
		 */
		static bool
		shouldLoadApplication();

		/**
		 * @brief Set whether or not the bootloader should load the application on next boot.
		 * @param loadApplication Value to set.
		 */
		static void
		setLoadApplication(bool loadApplication = true);

		/**
		 * @brief Check if the application has a valid stack pointer.
		 * @return Whether or not the applicaion has a valid stack pointer.
		 */
		static bool
		checkApplication();

		/**
		 * @brief Load the application.
		 * @note deinitialize() should be called before loading the application.
		 */
		static void
		loadApplication();

		/**
		 * @brief Deinitialize the bootloader.
		 */
		static void
		deinitialize();
	};
}

#endif  // OSSHS_BOOTLOADER_HPP
