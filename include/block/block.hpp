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

#ifndef BLOCKCHAIN_BLOCK_BLOCK_HPP_
#define BLOCKCHAIN_BLOCK_BLOCK_HPP_

#include "include/general.hpp"
#include "include/binary_data_converter/binary_data_converter_default.hpp"
#include "include/hash_calculator/hash_calculator_sha256.hpp"

namespace ssybc {

  template<
    typename BlockContent,
    template<typename> class BinaryDataConverterTemplate = BinaryDataConverterDefault,
    typename HashCalculator = SHA256Calculator>
  class Block {

  public:

    Block() = delete;
    Block(
      BlockIndex const block_index,
      BlockTimeInterval const time_stamp,
      BlockHash const previous_hash,
      BlockNonce const nonce,
      BlockContent const content);
    Block(const Block &block);
    Block(Block &&block);
    ~Block();

    BlockIndex Index() const final;
    BlockTimeInterval TimeStamp() const final;
    BlockHash PreviousBlockHash() const final;
    BlockNonce Nonce() const final;
    size_t SizeOfContentAsBinaryInBytes() const final;
    BlockContent Content() const final;
    BlockHash Hash() const final;

    BinaryData ToBinaryBlock() const final;
    operator std::string() const final;
    virtual std::string ToString() const;

  private:

    using BinaryDataConverter_ = BinaryDataConverterTemplate<BlockContent>;

    BlockIndex const index_;
    BlockTimeInterval const time_stamp_;
    BlockHash const previous_hash_;
    BlockNonce const nonce_;
    BlockContent const content_;

    BlockHash hash_{};
    BinaryData ContentAsBinary_() const final;
  };

}  // namespace ssybc

#endif  // BLOCKCHAIN_BLOCK_BLOCK_HPP_

