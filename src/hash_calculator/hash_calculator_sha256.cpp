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


#include "include/hash_calculator/hash_calculator_sha256.hpp"
#include "include/utility/utility.hpp"
#include "library/sha256/sha256.h"


size_t ssybc::SHA256Calculator::SizeOfHashInBytes() const
{
  return SHA256_BLOCK_SIZE;
}


ssybc::BlockHash ssybc::SHA256Calculator::GenesisBlockPreviousHash() const
{
  return "0000000000000000000000000000000000000000000000000000000000000000";
}


ssybc::BlockHash ssybc::SHA256Calculator::Hash(ssybc::BinaryData const data) const
{
  size_t const data_size{data.size()};
  Byte const * data_ptr{ &data.front() };

  BYTE result[SHA256_BLOCK_SIZE];
  SHA256_CTX ctx;

  sha256_init(&ctx);
  sha256_update(&ctx, data_ptr, data_size);
  sha256_final(&ctx, result);

  auto res_data = BinaryData(result, result + SHA256_BLOCK_SIZE);
  return util::HexStringFromBytes(res_data);
}

