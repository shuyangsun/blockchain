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

#ifndef SSYBC_INCLUDE_SSYBC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_INTERFACE_HPP_
#define SSYBC_INCLUDE_SSYBC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_INTERFACE_HPP_

#include "include/ssybc/general/general.hpp"

namespace ssybc {

  template<typename DataType>
  class BinaryDataConverterInterface {
  public:

    virtual BinaryData BinaryDataFromData(DataType const &data) const = 0;
    virtual DataType DataFromBinaryData(BinaryData const &binary_data) const = 0;

    virtual ~BinaryDataConverterInterface() { EMPTY_BLOCK }
  };

}  // namespace ssybc

#endif  // SSYBC_INCLUDE_SSYBC_BINARY_DATA_CONVERTER_BINARY_DATA_CONVERTER_DEFAULT_HPP_

