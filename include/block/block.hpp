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

#include "general.hpp"

namespace ssybc {

  template<typename BlockData, typename HashCalculator>
  class Block {

  public:

    Block(BlockIndex block_index, BlockTimeInterval time_stamp, BlockHash previous_hash, BlockNonce nonce, BlockData data);
    Block(const Block &block);
    Block(Block &&block);
    ~Block();

    BlockIndex Index() const final;
    BlockTimeInterval TimeStamp() const final;
    BlockHash PreviousBlockHash() const final;
    BlockNonce Nonce() const final;
    BlockData Data() const final;
    BlockHash Hash() const final;

    std::string ToString() const final;
    BinaryData ToBinaryData() const final;
    virtual bool IsValid() const = 0;
  
  protected:
    
    virtual std::string StringFromData_(const BlockData &data) const = 0;
    virtual BinaryData BinaryDataFromData_(const BlockData &data) const = 0;

  private:

    BlockIndex const index_;
    BlockTimeInterval const time_stamp_;
    BlockHash const previous_hash_;
    BlockNonce const nonce_;
    BlockData const data_;

    BlockHash hash_{};
  };

}  // namespace ssybc

#endif  // BLOCKCHAIN_BLOCK_BLOCK_HPP_

