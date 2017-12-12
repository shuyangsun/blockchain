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

#ifndef SSYBC_SRC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_IMPL_HPP_
#define SSYBC_SRC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_IMPL_HPP_

#include "include/ssybc/binary_data_converter/binary_data_converter_default.hpp"
#include "include/ssybc/utility/utility.hpp"

#include <algorithm>

// --------------------------------------------------- Helper Method --------------------------------------------------


namespace ssybc {
  template<typename T>
  BinaryData BinaryDataFromPrimitiveTypeIntegerData_(T const data);
  template<typename T>
  BinaryData BinaryDataFromPrimitiveTypeFloatData_(T const data);
  template<typename T>
  T PrimitiveTypeIntegerDataFromBinaryData_(BinaryData const &binary_data);
  template<typename T>
  T PrimitiveTypeFloatDataFromBinaryData_(BinaryData const &binary_data);
}


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename DataType>
inline auto ssybc::BinaryDataConverterDefault<DataType>::BinaryDataFromData(DataType const data) const -> BinaryData
{
  throw std::logic_error(
    "Cannot convert object of type \"" + std::string(typeid(DataType).name()) + "\" to binary data, "
    "template specilization implementation required."
  );
}


template<typename DataType>
inline auto ssybc::BinaryDataConverterDefault<DataType>::DataFromBinaryData(BinaryData const &data) const -> DataType
{
  throw std::logic_error(
    "Cannot extract object of type \"" + std::string(typeid(DataType).name()) + "\" from binary data, "
    "template specilization implementation required."
  );
}


// --------------------------------------- To Binary Specialization Definition ----------------------------------------


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned char>::BinaryDataFromData(
  unsigned char const data) const -> BinaryData
{
  return { static_cast<Byte>(data) };
}


template<>
inline auto ssybc::BinaryDataConverterDefault<char>::BinaryDataFromData(char const data) const -> BinaryData
{
  auto tmp_byte = static_cast<Byte const>(data);
  return {tmp_byte};
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned short>::BinaryDataFromData(
  unsigned short const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<short>::BinaryDataFromData(short const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned int>::BinaryDataFromData(
  unsigned int const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<int>::BinaryDataFromData(int const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned long>::BinaryDataFromData(
  unsigned long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long>::BinaryDataFromData(long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned long long>::BinaryDataFromData(
  unsigned long long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long long>::BinaryDataFromData(long long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeIntegerData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<float>::BinaryDataFromData(float const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeFloatData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<double>::BinaryDataFromData(double const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeFloatData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long double>::BinaryDataFromData(
  long double const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeFloatData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<std::string>::BinaryDataFromData(
  std::string const data) const -> BinaryData
{
  auto c_string = data.c_str();
  SizeT const result_size{ data.size() };
  auto byte_ptr = reinterpret_cast<Byte const*>(c_string);
  return BinaryData(byte_ptr, byte_ptr + result_size);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<ssybc::BinaryData>::BinaryDataFromData(
  BinaryData const data) const -> BinaryData
{
  return data;
}


// -------------------------------------- From Binary Specialization Definition ---------------------------------------


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned char>::DataFromBinaryData(
  BinaryData const &binary_data) const -> unsigned char
{
  return binary_data.front();
}


template<>
inline auto ssybc::BinaryDataConverterDefault<char>::DataFromBinaryData(
  BinaryData const &binary_data) const -> char
{
  return static_cast<char>(binary_data.front());
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned short>::DataFromBinaryData(
  BinaryData const &binary_data) const -> unsigned short
{
  return PrimitiveTypeIntegerDataFromBinaryData_<unsigned short>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<short>::DataFromBinaryData(
  BinaryData const &binary_data) const -> short
{
  return PrimitiveTypeIntegerDataFromBinaryData_<short>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned int>::DataFromBinaryData(
  BinaryData const &binary_data) const -> unsigned int
{
  return PrimitiveTypeIntegerDataFromBinaryData_<unsigned int>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<int>::DataFromBinaryData(
  BinaryData const &binary_data) const -> int
{
  return PrimitiveTypeIntegerDataFromBinaryData_<int>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned long>::DataFromBinaryData(
  BinaryData const &binary_data) const -> unsigned long
{
  return PrimitiveTypeIntegerDataFromBinaryData_<unsigned long>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long>::DataFromBinaryData(
  BinaryData const &binary_data) const -> long
{
  return PrimitiveTypeIntegerDataFromBinaryData_<long>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned long long>::DataFromBinaryData(
  BinaryData const &binary_data) const -> unsigned long long
{
  return PrimitiveTypeIntegerDataFromBinaryData_<unsigned long long>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long long>::DataFromBinaryData(
  BinaryData const &binary_data) const -> long long
{
  return PrimitiveTypeIntegerDataFromBinaryData_<long long>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<float>::DataFromBinaryData(
  BinaryData const &binary_data) const -> float
{
  return PrimitiveTypeFloatDataFromBinaryData_<float>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<double>::DataFromBinaryData(
  BinaryData const &binary_data) const -> double
{
  return PrimitiveTypeFloatDataFromBinaryData_<double>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long double>::DataFromBinaryData(
  BinaryData const &binary_data) const -> long double
{
  return PrimitiveTypeFloatDataFromBinaryData_<long double>(binary_data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<std::string>::DataFromBinaryData(
  BinaryData const &binary_data) const -> std::string
{
  SizeT const string_len{ binary_data.size() };
  return std::string(binary_data.begin(), binary_data.end());
}


template<>
inline auto ssybc::BinaryDataConverterDefault<ssybc::BinaryData>::DataFromBinaryData(
  BinaryData const &binary_data) const -> BinaryData
{
  return binary_data;
}


// --------------------------------------------------- Helper Method --------------------------------------------------


template<typename T>
inline auto ssybc::BinaryDataFromPrimitiveTypeIntegerData_(T const data) -> BinaryData
{
  SizeT const result_size{ sizeof(data) };
  auto data_little_endian = util::ToLittleEndian(data);
  auto byte_ptr = reinterpret_cast<Byte const*>(&data_little_endian);
  return BinaryData(byte_ptr, byte_ptr + result_size);
}


template<typename T>
inline auto ssybc::BinaryDataFromPrimitiveTypeFloatData_(T const data) -> BinaryData
{
  // TODO: handle big Endian.
  SizeT const result_size{ sizeof(data) };
  auto byte_ptr = reinterpret_cast<Byte const*>(&data);
  return BinaryData(byte_ptr, byte_ptr + result_size);
}


template<typename T>
inline T ssybc::PrimitiveTypeIntegerDataFromBinaryData_(BinaryData const &binary_data)
{
  BinaryData const binary_data_endian_converted =
    kIsBigEndian ? util::ByteSwap(binary_data) : binary_data;
  Byte const *byte_ptr{&binary_data_endian_converted.front()};
  auto data_ptr = reinterpret_cast<T const *>(byte_ptr);
  return *data_ptr;
}


template<typename T>
inline T ssybc::PrimitiveTypeFloatDataFromBinaryData_(BinaryData const &binary_data)
{
  // TODO: handle big Endian.
  Byte const *byte_ptr{ &(binary_data.front()) };
  auto data_ptr = reinterpret_cast<T const *>(byte_ptr);
  return *data_ptr;
}


#endif  // SSYBC_SRC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_IMPL_HPP_
