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

#ifndef SSYBC_INCLUDE_SSYBC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_HPP_
#define SSYBC_INCLUDE_SSYBC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_HPP_

#include "include/ssybc/binary_data_converter/binary_data_converter_interface.hpp"
#include "include/ssybc/binary_content_data/binary_content_data.hpp"

#include <string>
#include <exception>

namespace ssybc {

  template<typename DataType>
  class BinaryDataConverterDefault: public virtual BinaryDataConverterInterface<DataType> {

  public:
 
// --------------------------------------------------- Public Method --------------------------------------------------

    BinaryData BinaryDataFromData(DataType const &data) const override final;
    DataType DataFromBinaryData(BinaryData const &data) const override final;

  };  // BinaryDataConverterDefault


// --------------------------------------- To Binary Specialization Declaration ---------------------------------------

  template<>
  BinaryData BinaryDataConverterDefault<unsigned char>::BinaryDataFromData(unsigned char const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<char>::BinaryDataFromData(char const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<unsigned short>::BinaryDataFromData(unsigned short const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<short>::BinaryDataFromData(short const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<unsigned int>::BinaryDataFromData(unsigned int const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<int>::BinaryDataFromData(int const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<unsigned long>::BinaryDataFromData(unsigned long const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<long>::BinaryDataFromData(long const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<unsigned long long>::BinaryDataFromData(unsigned long long const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<long long>::BinaryDataFromData(long long const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<float>::BinaryDataFromData(float const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<double>::BinaryDataFromData(double const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<long double>::BinaryDataFromData(long double const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<std::string>::BinaryDataFromData(std::string const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<BinaryData>::BinaryDataFromData(BinaryData const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<BinaryContentData>::BinaryDataFromData(BinaryContentData const &data) const;


// -------------------------------------- From Binary Specialization Declaration --------------------------------------


  template<>
  unsigned char BinaryDataConverterDefault<unsigned char>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  char BinaryDataConverterDefault<char>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  unsigned short BinaryDataConverterDefault<unsigned short>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  short BinaryDataConverterDefault<short>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  unsigned int BinaryDataConverterDefault<unsigned int>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  int BinaryDataConverterDefault<int>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  unsigned long BinaryDataConverterDefault<unsigned long>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  long BinaryDataConverterDefault<long>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  unsigned long long BinaryDataConverterDefault<unsigned long long>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  long long BinaryDataConverterDefault<long long>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  float BinaryDataConverterDefault<float>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  double BinaryDataConverterDefault<double>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  long double BinaryDataConverterDefault<long double>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  std::string BinaryDataConverterDefault<std::string>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  BinaryData BinaryDataConverterDefault<BinaryData>::DataFromBinaryData(BinaryData const &data) const;
  template<>
  BinaryContentData BinaryDataConverterDefault<BinaryContentData>::DataFromBinaryData(BinaryData const &data) const;


}  // namespace ssybc

#include "src/binary_data_converter/binary_data_converter_default_impl.hpp"

#endif  // SSYBC_INCLUDE_SSYBC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_HPP_

