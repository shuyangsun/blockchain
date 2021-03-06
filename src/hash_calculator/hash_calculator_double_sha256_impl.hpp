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

#ifndef SSYBC_SRC_HASH_CALCULATOR_HASH_CALCULATOR_DOUBLE_SHA256_IMPL_HPP_
#define SSYBC_SRC_HASH_CALCULATOR_HASH_CALCULATOR_DOUBLE_SHA256_IMPL_HPP_


#include "include/ssybc/hash_calculator/hash_calculator_double_sha256.hpp"
#include "include/ssybc/hash_calculator/hash_calculator_sha256.hpp"
#include "include/ssybc/binary_data_converter/binary_data_converter_default.hpp"
#include "include/ssybc/utility/utility.hpp"


auto ssybc::DoubleSHA256Calculator::SizeOfHashInBytes() const -> SizeT
{
  return SHA256Calculator().SizeOfHashInBytes();
}


ssybc::BlockHash ssybc::DoubleSHA256Calculator::GenesisBlockPreviousHash() const
{
  return SHA256Calculator().GenesisBlockPreviousHash();
}


ssybc::BlockHash ssybc::DoubleSHA256Calculator::Hash(ssybc::BinaryData const data) const
{
  BlockHash const first_level_hash{ SHA256Calculator().Hash(data) };
  BinaryData const binary_hash{ BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(first_level_hash) };
  BlockHash const result{ SHA256Calculator().Hash(binary_hash) };
  return result;
}


#endif  // SSYBC_SRC_HASH_CALCULATOR_HASH_CALCULATOR_DOUBLE_SHA256_IMPL_HPP_

