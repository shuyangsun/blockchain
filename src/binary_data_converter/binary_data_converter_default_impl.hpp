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

#ifndef BLOCKCHAIN_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_IMPL_HPP_
#define BLOCKCHAIN_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_IMPL_HPP_

#include "include/binary_data_converter/binary_data_converter_default.hpp"
#include "include/utility/utility.hpp"

namespace ssybc {
  template<typename T>
  BinaryData BinaryDataFromPrimitiveTypeData_(T const data);
}


template<typename DataType>
inline auto ssybc::BinaryDataConverterDefault<DataType>::BinaryDataFromData(DataType const data) const -> BinaryData
{
  throw std::logic_error("Cannot convert object of type \"" + typeid(DataType) + "\" to BinaryData.");
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned char>::BinaryDataFromData(unsigned char const data) const -> BinaryData
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
inline auto ssybc::BinaryDataConverterDefault<unsigned short>::BinaryDataFromData(unsigned short const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<short>::BinaryDataFromData(short const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned int>::BinaryDataFromData(unsigned int const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<int>::BinaryDataFromData(int const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned long>::BinaryDataFromData(unsigned long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long>::BinaryDataFromData(long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<unsigned long long>::BinaryDataFromData(unsigned long long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long long>::BinaryDataFromData(long long const data) const -> BinaryData
{
  return BinaryDataFromPrimitiveTypeData_(data);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<float>::BinaryDataFromData(float const data) const -> BinaryData
{
  size_t const result_size{ sizeof(data) };
  auto byte_ptr = reinterpret_cast<Byte const*>(&data);
  return BinaryData(byte_ptr, byte_ptr + result_size);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<double>::BinaryDataFromData(double const data) const -> BinaryData
{
  size_t const result_size{ sizeof(data) };
  auto byte_ptr = reinterpret_cast<Byte const*>(&data);
  return BinaryData(byte_ptr, byte_ptr + result_size);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<long double>::BinaryDataFromData(long double const data) const -> BinaryData
{
  size_t const result_size{ sizeof(data) };
  auto byte_ptr = reinterpret_cast<Byte const*>(&data);
  return BinaryData(byte_ptr, byte_ptr + result_size);
}


template<>
inline auto ssybc::BinaryDataConverterDefault<std::string>::BinaryDataFromData(std::string const data) const -> BinaryData
{
  auto c_string = data.c_str();
  size_t const result_size{ data.size() };
  auto byte_ptr = reinterpret_cast<Byte const*>(c_string);
  return BinaryData(byte_ptr, byte_ptr + result_size + 1);
}

template<typename T>
inline auto ssybc::BinaryDataFromPrimitiveTypeData_(T const data) -> BinaryData
{
  size_t const result_size{ sizeof(data) };
  auto data_big_endian = util::ToBigEndian(data);
  auto byte_ptr = reinterpret_cast<Byte const*>(&data_big_endian);
  return BinaryData(byte_ptr, byte_ptr + result_size);
}


#endif  // BLOCKCHAIN_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_IMPL_HPP_

