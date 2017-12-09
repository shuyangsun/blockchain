/******************************************************************************
 *
 * Copyright (c) 2017-2018 Shuyang Sun
 *
 * License: MIT
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/


#include "utility/utility.hpp"

std::string ssybc::util::DateTimeStringFromTimeStamp(BlockTimeInterval const time_stamp, std::string const time_format)
{
  struct tm ptm {};
  errno_t err{};
  err = gmtime_s(&ptm, &time_stamp);

  size_t const buffer_size{ 30 };
  char buffer[buffer_size];
  memset(buffer, 0, buffer_size * sizeof(char));
  strftime(buffer, sizeof(buffer), time_format.c_str(), &ptm);
  return std::string(buffer);
}

std::string ssybc::util::DateTimeStringFromTimeStamp(BlockTimeInterval const time_stamp)
{
  return DateTimeStringFromTimeStamp(time_stamp, "%Y-%m-%dT%H:%M:%SUTC");
}
