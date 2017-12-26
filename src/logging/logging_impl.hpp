/**********************************************************************************************************************
 *
 * Copyright (c) 2017-2018 Shuyang Sun
 *
 * License: MIT
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *********************************************************************************************************************/


#ifndef SSYBC_SRC_LOGGING_LOGGING_HPP_
#define SSYBC_SRC_LOGGING_LOGGING_HPP_

#include "include/ssybc/general/general.hpp"
#include "include/ssybc/logging/logging.hpp"

namespace ssybc {
  namespace logging {

    static LoggerVerbosity global_logger_verbosity_{ LoggerVerbosity::kNoTest };

  }  // namespace logging
}  // namespace ssybc


// --------------------------------------------------- Public Method --------------------------------------------------


void ssybc::logging::SetLoggerVerbosityLevel(LoggerVerbosity const verbosity)
{
  global_logger_verbosity_ = verbosity;
}


ssybc::logging::Logger::Logger(LoggerVerbosity const verbosity):
  verbosity_{ verbosity }
{ EMPTY_BLOCK }


template<typename ...Args>
inline std::ostream & ssybc::logging::Logger::operator<<(Args && ...args) const
{
  return std::cout;  // TODO
}


#endif  // SSYBC_SRC_LOGGING_LOGGING_HPP_
