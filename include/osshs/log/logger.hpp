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

#ifndef OSSHS_LOGGER_HPP
#define OSSHS_LOGGER_HPP

#include <modm/debug/logger.hpp>

#ifndef DISABLE_LOGGING
	#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

	#define OSSHS_ENABLE_LOGGER(device, behavior) \
		modm::IODeviceWrapper<device, behavior> loggerDevice; \
		modm::log::Logger osshs::log::logger(loggerDevice);

	#define OSSHS_LOG_ERROR(format, args...)   osshs::log::Logger::log(osshs::log::Level::ERROR  , __FILENAME__, __LINE__, format, ##args);
	#define OSSHS_LOG_WARNING(format, args...) osshs::log::Logger::log(osshs::log::Level::WARNING, __FILENAME__, __LINE__, format, ##args);
	#define OSSHS_LOG_INFO(format, args...)    osshs::log::Logger::log(osshs::log::Level::INFO   , __FILENAME__, __LINE__, format, ##args);
	#define OSSHS_LOG_DEBUG(format, args...)   osshs::log::Logger::log(osshs::log::Level::DEBUG  , __FILENAME__, __LINE__, format, ##args);

	#define OSSHS_LOG_FLUSH() osshs::log::Logger::flush();
	#define OSSHS_LOG_SET_LEVEL(level) osshs::log::Logger::setLevel(level);

	namespace osshs
	{
		namespace log
		{
			extern modm::log::Logger logger;

			enum class Level : uint8_t
			{
				DISABLED,
				ERROR,
				WARNING,
				INFO,
				DEBUG
			};

			class Logger
			{
				public:
					/**
					 * @brief Set current logger level.
					 * @param level One of: osshs::log::DEBUG, osshs::log::INFO, osshs::log::WARNING, osshs::log::ERROR or osshs::log::DISABLED.
					 */
					static void
					setLevel(Level level);

					/**
					 * @brief Write a log message. Should not be called directly, instead use the predefined macros.
					 * @param level One of: osshs::log::DEBUG, osshs::log::INFO, osshs::log::WARNING, osshs::log::ERROR or osshs::log::DISABLED.
					 * @param file File from which the message was logged. Usually __FILENAME__.
					 * @param line Line from which the message was logged. Usually __LINE__.
					 * @param format Log message format.
					 * @param args Log message format arguments.
					 */
					template<typename... ARGS>
					static void
					log(Level level, const char *filename, uint32_t line, const char *format, ARGS... args);

					/**
					 * @brief Flush the underlying stream.
					 */
					static void
					flush();
				private:
					static Level level;
			};
		}
	}

	#include <osshs/log/logger_impl.hpp>
#else  // DISABLE_LOGGING
	#define OSSHS_ENABLE_LOGGER(device, behavior)

	#define OSSHS_LOG_ERROR(format, args...)
	#define OSSHS_LOG_WARNING(format, args...)
	#define OSSHS_LOG_INFO(format, args...)
	#define OSSHS_LOG_DEBUG(format, args...)

	#define OSSHS_LOG_FLUSH()
	#define OSSHS_LOG_SET_LEVEL(level)
#endif  // DISABLE_LOGGING

#endif  // OSSHS_LOGGER_HPP
