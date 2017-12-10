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

#ifndef BLOCKCHAIN_GENERAL_HPP_
#define BLOCKCHAIN_GENERAL_HPP_

#include <string>
#include <vector>
#include <ctime>

#define EMPTY_BLOCK

namespace ssybc {

  using BlockIndex = uint64_t;
  using BlockTimeInterval = int64_t;
  using BlockHash = std::string;
  using BlockNonce = uint64_t;
  using Byte = unsigned char;
  using BinaryData = std::vector<Byte>;

  constexpr unsigned char kNumberOfBitsInByte{8};
  constexpr unsigned int kNumberOfBytesInMB{1024 * 1024};

  constexpr union {
    uint32_t i;
    char c[4];
  } bint_ = { 0x01020304 };

  const bool kIsBigEndian{ bint_.c[0] == 1 };

}  // namespace ssybc

#endif  // BLOCKCHAIN_GENERAL_HPP_

