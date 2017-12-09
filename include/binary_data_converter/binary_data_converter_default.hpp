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

#ifndef BLOCKCHAIN_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_HPP_
#define BLOCKCHAIN_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_HPP_

#include "include/binary_data_converter/binary_data_converter_interface.hpp"

#include <exception>

namespace ssybc {

  template<typename DataType>
  class BinaryDataConverterDefault: public virtual BinaryDataConverterInterface<DataType> {
  public:
    BinaryData BinaryDataFromData(DataType const data) const override final;
  };

  // ------------------------ Specialization Declaration ------------------------

  template<>
  BinaryData BinaryDataConverterDefault<unsigned char>::BinaryDataFromData(unsigned char const data) const;
  template<>
  BinaryData BinaryDataConverterDefault<char>::BinaryDataFromData(char const data) const;
  template<>
  BinaryData BinaryDataConverterDefault<unsigned short>::BinaryDataFromData(unsigned short const data) const;

}  // namespace ssybc

#include "src/binary_data_converter/binary_data_converter_default_impl.hpp"

#endif  // BLOCKCHAIN_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_HPP_

