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

#ifndef BLOCKCHAIN_UTILITY_UTILITY_HPP_
#define BLOCKCHAIN_UTILITY_UTILITY_HPP_

#include "include/general.hpp"
#include <vector>
#include <functional>

namespace ssybc {

namespace util {

  std::string DateTimeStringFromTimeStamp(BlockTimeInterval const time_stamp, std::string const time_format);
  std::string DateTimeStringFromTimeStamp(BlockTimeInterval const time_stamp);

  std::string BinaryStringFromByte(Byte const byte);
  std::string HexStringFromByte(Byte const byte);

  std::string BinaryStringFromBytes(BinaryData const bytes);
  std::string BinaryStringFromBytes(BinaryData const bytes, std::string const delimiter);
  std::string HexStringFromBytes(BinaryData const bytes);
  std::string HexStringFromBytes(BinaryData const bytes, std::string const delimiter);

  template<typename T>
  T ByteSwap(T const value);

  template<typename T>
  T ToBigEndian(T const value);
  
  template<typename T>
  std::vector<T> ConcatenateMoveDestructive(std::vector<std::vector<T>> const &vectors);

  template<typename T>
  std::string Join(std::vector<T> const vec, std::string delimiter, const std::function<std::string(T)>& map_func);

}  // namespace util

}  // namespace ssybc

#include "src/utility/utility_impl.hpp"

#endif  // BLOCKCHAIN_UTILITY_UTILITY_HPP_

