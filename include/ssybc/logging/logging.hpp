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

#ifndef SSYBC_INCLUDE_SSYBC_LOGGING_LOGGING_HPP_
#define SSYBC_INCLUDE_SSYBC_LOGGING_LOGGING_HPP_

#include "include/ssybc/general/general.hpp"

#include <iostream>

namespace ssybc {

namespace logging {

// ------------------------------------------------------- Enum -------------------------------------------------------


  enum LoggerVerbosity: unsigned int {
    kNoTest = 0,
    kDebug,
    kInfo,
    kWarning
  };


// --------------------------------------------------- Public Class ---------------------------------------------------
  

  class Logger {
  public:

    Logger(LoggerVerbosity const verbosity);
    LoggerVerbosity Verbosity() const;

  private:
    LoggerVerbosity const verbosity_;
  };

  
// -------------------------------------------------- Public Function -------------------------------------------------


  void SetLoggerVerbosityLevel(LoggerVerbosity const verbosity);

  template<typename ...Args>
  std::ostream &operator<<(Logger const &logger, Args&&... args);
  std::ostream &operator<<(Logger const &logger, std::ostream& (*pf)(std::ostream&));


}  // namespace logging

}  // namespace ssybc

#include "src/logging/logging_impl.hpp"

#endif  // SSYBC_INCLUDE_SSYBC_LOGGING_LOGGING_HPP_

