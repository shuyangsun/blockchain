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


#ifndef BLOCKCHAIN_UTILITY_UTILITY_IMPL_HPP_
#define BLOCKCHAIN_UTILITY_UTILITY_IMPL_HPP_

#include "include/utility/utility.hpp"

#include <unordered_map>
#include <algorithm>


 // ----------------------------------------------------- Helper ------------------------------------------------------


namespace ssybc{
   static std::unordered_map<Byte, char> kIntToHexCharMap {
    { 0, '0' },
    { 1, '1' },
    { 2, '2' },
    { 3, '3' },
    { 4, '4' },
    { 5, '5' },
    { 6, '6' },
    { 7, '7' },
    { 8, '8' },
    { 9, '9' },
    { 10, 'a' },
    { 11, 'b' },
    { 12, 'c' },
    { 13, 'd' },
    { 14, 'e' },
    { 15, 'f' }
  };
}


// -------------------------------------------------- Public Function -------------------------------------------------


inline ssybc::BlockTimeInterval ssybc::util::UTCTime()
{
  time_t rawtime;
  struct tm ptm;

  time(&rawtime);
  errno_t err{};
  err = gmtime_s(&ptm, &rawtime);
  return static_cast<BlockTimeInterval>(mktime(&ptm));
}


inline std::string ssybc::util::DateTimeStringFromTimeStamp(BlockTimeInterval const time_stamp, std::string const time_format)
{
  struct tm ptm {};
  errno_t err{};
  err = gmtime_s(&ptm, &time_stamp);

  size_t const buffer_size{30};
  char buffer[buffer_size];
  memset(buffer, 0, buffer_size * sizeof(char));
  strftime(buffer, sizeof(buffer), time_format.c_str(), &ptm);
  return std::string(buffer);
}


inline std::string ssybc::util::DateTimeStringFromTimeStamp(BlockTimeInterval const time_stamp)
{
  return DateTimeStringFromTimeStamp(time_stamp, "%Y-%m-%dT%H:%M:%SUTC");
}


inline std::string ssybc::util::BinaryStringFromByte(Byte const byte)
{
  std::string result{"00000000"};
  Byte mask{0b00000001};
  for (size_t i{0}; i < kNumberOfBitsInByte; ++i) {
    if ((byte & mask) > 0) {
      result[kNumberOfBitsInByte - 1 - i] = '1';
    }
    mask <<= 1;
  }
  return result;
}


inline std::string ssybc::util::HexStringFromByte(Byte const byte)
{
  std::string result{"00"};
  Byte mask{ 0b00001111 };
  Byte const higher_address_value{ static_cast<Byte const>(byte & mask) };
  result[1] = kIntToHexCharMap[higher_address_value];
  mask = 0b11110000;
  Byte const lower_address_value{ static_cast<Byte const>((byte & mask) >> 4) };
  result[0] = kIntToHexCharMap[lower_address_value];
  return result;
}


inline std::string ssybc::util::BinaryStringFromBytes(BinaryData const bytes)
{
  return BinaryStringFromBytes(bytes, "");
}


inline std::string ssybc::util::BinaryStringFromBytes(BinaryData const bytes, std::string const delimiter)
{
  return Join<Byte>(bytes, delimiter, [](Byte byte) { return BinaryStringFromByte(byte);  });
}


inline std::string ssybc::util::HexStringFromBytes(BinaryData const bytes)
{
  return HexStringFromBytes(bytes, "");
}


inline std::string ssybc::util::HexStringFromBytes(BinaryData const bytes, std::string const delimiter)
{
  return Join<Byte>(bytes, delimiter, [](Byte byte) { return HexStringFromByte(byte);  });
}

template<typename T>
inline T ssybc::util::ByteSwap(T const value)
{
  size_t const num_bytes{ sizeof(T) };
  if (num_bytes <= 1) {
    return value;
  }
  T mask_on_value{ static_cast<T>(0b11111111) };
  T mask_on_result{ static_cast<T>(0b11111111 << ((num_bytes - 1) * kNumberOfBitsInByte)) };
  T result{ static_cast<T>(0) };
  for (size_t i{ 0 }; i < num_bytes; ++i) {
    int shift_amount{ static_cast<int>((num_bytes - 2 * i - 1) * kNumberOfBitsInByte) };
    bool const to_left{ shift_amount > 0 };
    if (!to_left) {
      shift_amount = -shift_amount;
    }
    T tmp_val{};
    if (to_left) {
      tmp_val = static_cast<T>((value & mask_on_value) << shift_amount);
    }
    else {
      tmp_val = static_cast<T>((value & mask_on_value) >> shift_amount);
    }
    result |= (tmp_val & mask_on_result);
    mask_on_result >>= kNumberOfBitsInByte;
    mask_on_value <<= kNumberOfBitsInByte;
  }
  return result;
}


template<>
inline ssybc::BinaryData ssybc::util::ByteSwap(BinaryData const value)
{
  BinaryData result = value;
  std::reverse(result.begin(), result.end());
  return result;
}


template<typename T>
inline T ssybc::util::ToLittleEndian(T const value)
{
  return kIsBigEndian ? ByteSwap(value) : value;
}


template<typename T>
inline std::vector<T> ssybc::util::ConcatenateMoveDestructive(std::vector<std::vector<T>> const &vectors)
{
  BinaryData result{};
  for (auto &vec : vectors) {
    result.insert(
      result.end(),
      std::make_move_iterator(vec.begin()),
      std::make_move_iterator(vec.end())
    );
  }
  return result;
}


template<typename T>
std::string ssybc::util::Join(
  std::vector<T> const vec,
  std::string delimiter,
  const std::function<std::string(T)>& map_func)
{
  std::string result{};
  for (size_t i{ 0 }; i < vec.size(); ++i) {
    result += map_func(vec[i]);
    if (i < vec.size() - 1) {
      result += delimiter;
    }
  }
  return result;
}


#endif  // BLOCKCHAIN_UTILITY_UTILITY_IMPL_HPP_
