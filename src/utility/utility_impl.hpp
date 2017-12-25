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


#ifndef SSYBC_SRC_UTILITY_UTILITY_IMPL_HPP_
#define SSYBC_SRC_UTILITY_UTILITY_IMPL_HPP_

#include "include/ssybc/utility/utility.hpp"
#include "include/ssybc/binary_data_converter/binary_data_converter_default.hpp"

#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <type_traits>
#include <ctime>


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

   template<class T>
    typename std::enable_if<std::is_fundamental<T>::value, std::string>::type Stringify_(const T& t)
   {
     return std::to_string(t);
   }

   template<class T>
    typename std::enable_if<
      !std::is_fundamental<T>::value
      && !std::is_same<T, ssybc::BinaryData>::value,
      std::string>::type  Stringify_(const T& t)
   {
     return std::string(t);
   }

   template<class T>
    typename std::enable_if<std::is_same<T, ssybc::BinaryData>::value, std::string>::type  Stringify_(const T& t)
   {
     return util::HexStringFromBytes(t, " ");
   }
}


// -------------------------------------------------- Public Function -------------------------------------------------


inline ssybc::BlockTimeInterval ssybc::util::UTCTime()
{
  time_t rawtime;
  struct tm ptm;

  time(&rawtime);
  errno_t err{};
  err = gmtime_s(&ptm, &rawtime);
//  auto const ptm_ptr = gmtime_r(&rawtime, &ptm);
  return static_cast<BlockTimeInterval>(mktime(&ptm));
}


template<typename T>
std::string ssybc::util::ToString(T const &value)
{
  return Stringify_(value);
}


inline std::string ssybc::util::DateTimeStringFromTimeStamp(BlockTimeInterval const time_stamp, std::string const time_format)
{
  struct tm ptm {};
  errno_t err{};
  err = gmtime_s(&ptm, &time_stamp);
//  time_t const ts = static_cast<time_t>(time_stamp);
//  auto const ptm_ptr = gmtime_r(&ts, &ptm);

  SizeT const buffer_size{30};
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
  for (SizeT i{0}; i < kNumberOfBitsInByte; ++i) {
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


inline std::string ssybc::util::BinaryStringFromBytes(BinaryData const &bytes)
{
  return BinaryStringFromBytes(bytes, "");
}


inline std::string ssybc::util::BinaryStringFromBytes(BinaryData const &bytes, std::string const delimiter)
{
  return Join<Byte>(bytes, delimiter, [](Byte byte) { return BinaryStringFromByte(byte);  });
}


inline std::string ssybc::util::HexStringFromBytes(BinaryData const &bytes)
{
  return HexStringFromBytes(bytes, "");
}


inline std::string ssybc::util::HexStringFromBytes(BinaryData const &bytes, std::string const delimiter)
{
  return Join<Byte>(bytes, delimiter, [](Byte byte) { return HexStringFromByte(byte);  });
}


inline ssybc::BlockHash ssybc::util::HashStrippedLeadingZeros(BlockHash const &hash)
{
  auto iter = hash.begin();
  while (*iter == 0) {
    ++iter;
  }
  return BlockHash{iter, hash.end()};
}


inline ssybc::BlockTimeInterval ssybc::util::TrailingTimeStampBeforeNonceFromBinaryData(BinaryData const & binary_data)
{
  BinaryDataConverterDefault<BlockTimeInterval> converter{};
  int const nonce_binary_size = sizeof(BlockNonce);
  int const ts_binary_size = sizeof(BlockTimeInterval);
  auto begin_iter = binary_data.end();
  auto end_iter = binary_data.end();
  std::advance(begin_iter, -1 * (ts_binary_size + nonce_binary_size));
  std::advance(end_iter, -1 * (nonce_binary_size));
  auto const ts_as_binary = BinaryData(begin_iter, end_iter);
  return converter.DataFromBinaryData(ts_as_binary);
}


inline ssybc::BlockNonce ssybc::util::TrailingNonceFromBinaryData(BinaryData const & binary_data)
{
  BinaryDataConverterDefault<BlockNonce> converter{};
  int const nonce_binary_size = sizeof(BlockNonce);
  auto begin_iter = binary_data.end();
  std::advance(begin_iter, -1 * nonce_binary_size);
  auto const nonce_as_binary = BinaryData(begin_iter, binary_data.end());
  return converter.DataFromBinaryData(nonce_as_binary);
}


inline void ssybc::util::UpdateBinaryDataWithTrailingTimeStampBeforeNonce(
  BinaryData & binary_data,
  BlockTimeInterval const time_stamp)
{
  BinaryDataConverterDefault<BlockTimeInterval> ts_converter{};
  BinaryDataConverterDefault<BlockNonce> nonce_converter{};
  auto time_stamp_as_binary = ts_converter.BinaryDataFromData(time_stamp);
  std::size_t const nonce_binary_size{ nonce_converter.BinaryDataFromData(BlockNonce{}).size() };
  std::size_t const time_stamp_binary_size{ time_stamp_as_binary.size() };
  std::size_t const binary_start_idx{ binary_data.size() - time_stamp_binary_size - nonce_binary_size };
  for (size_t i{ 0 }; i < time_stamp_binary_size; ++i) {
    binary_data[binary_start_idx + i] = time_stamp_as_binary[i];
  }
}


inline void ssybc::util::UpdateBinaryDataWithTrailingNonce(BinaryData & binary_data, BlockNonce const nonce)
{
  BinaryDataConverterDefault<BlockNonce> converter{};
  auto nonce_as_binary = converter.BinaryDataFromData(nonce);
  size_t const nonce_binary_size{ nonce_as_binary.size() };
  size_t const binary_start_idx{ binary_data.size() - nonce_binary_size };
  for (size_t i{ 0 }; i < nonce_binary_size; ++i) {
    binary_data[binary_start_idx + i] = nonce_as_binary[i];
  }
}


inline bool ssybc::util::WriteBinaryDataToFileAtPath(BinaryData const & binary_data, std::string const & file_path)
{
  std::fstream file;
  file.open(file_path, std::ios::out | std::ios::binary);
  file.write((char *)(&binary_data.front()), binary_data.size());
  file.close();
  return true;
}


inline ssybc::BinaryData ssybc::util::ReadBinaryDataFromFileAtPath(std::string const & file_path)
{
  std::fstream file;
  file.open(file_path, std::ios::in | std::ios::binary);
  file.seekg(0, std::ios::end);
  auto const file_size = file.tellg();
  file.seekg(0, std::ios::beg);
  char * buffer = new char[file_size];
  file.read(buffer, file_size);
  file.close();
  BinaryData result{ buffer, buffer + file_size };
  delete[] buffer;
  return result;
}


template<typename T>
inline T ssybc::util::ByteSwap(T const value)
{
  SizeT const num_bytes{ sizeof(T) };
  if (num_bytes <= 1) {
    return value;
  }
  T mask_on_value{ static_cast<T>(0b11111111) };
  T mask_on_result{ static_cast<T>(static_cast<T>(0b11111111) << ((num_bytes - 1) * kNumberOfBitsInByte)) };
  T result{ static_cast<T>(0) };
  for (SizeT i{ 0 }; i < num_bytes; ++i) {
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
inline std::vector<T> ssybc::util::ConcatenateMoveDestructive(std::vector<std::vector<T>> &vectors)
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
  std::vector<T> const &vec,
  std::string delimiter,
  const std::function<std::string(T)>& map_func)
{
  std::string result{};
  for (SizeT i{ 0 }; i < vec.size(); ++i) {
    result += map_func(vec[i]);
    if (i < vec.size() - 1) {
      result += delimiter;
    }
  }
  return result;
}


#endif  // SSYBC_SRC_UTILITY_UTILITY_IMPL_HPP_
