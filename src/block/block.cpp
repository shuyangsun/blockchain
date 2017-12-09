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


#include "block/block.hpp"


template<typename BlockData, typename HashCalculator>
ssybc::Block<BlockData, HashCalculator>::Block(
  BlockIndex block_index,
  BlockTimeInterval time_stamp,
  BlockHash previous_hash,
  BlockNonce nonce,
  BlockData data) :
  index_{block_index},
  time_stamp_{time_stamp},
  previous_hash_{previous_hash},
  nonce_{nonce},
  data_{data}
{ EMPTY_BLOCK }


template<typename BlockData, typename HashCalculator>
ssybc::Block<BlockData, HashCalculator>::Block(const Block & block) :
  index_{ block.Index() },
  time_stamp_{ block.TimeStamp() },
  previous_hash_{ block.PreviousBlockHash() },
  nonce_{ block.Nonce() },
  data_{ block.Data() }
{ EMPTY_BLOCK }


template<typename BlockData, typename HashCalculator>
ssybc::Block<BlockData, HashCalculator>::Block(Block && block) :
  index_{ block.Index() },
  time_stamp_{ block.TimeStamp() },
  previous_hash_{ std::move(block.PreviousBlockHash()) },
  nonce_{ block.Nonce() },
  data_{ std::move(block.Data()) }
{ EMPTY_BLOCK }


template<typename BlockData, typename HashCalculator>
ssybc::Block<BlockData, HashCalculator>::~Block()
{
  delete index_;
  delete time_stamp_;
  delete previous_hash_;
  delete nonce_;
  delete data_;
}

template<typename BlockData, typename HashCalculator>
ssybc::BlockIndex ssybc::Block<BlockData, HashCalculator>::Index() const
{
  return index_;
}

template<typename BlockData, typename HashCalculator>
ssybc::BlockTimeInterval ssybc::Block<BlockData, HashCalculator>::TimeStamp() const
{
  return time_stamp_;
}

template<typename BlockData, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockData, HashCalculator>::PreviousBlockHash() const
{
  return previous_hash_;
}

template<typename BlockData, typename HashCalculator>
ssybc::BlockNonce ssybc::Block<BlockData, HashCalculator>::Nonce() const
{
  return nonce_;
}

template<typename BlockData, typename HashCalculator>
BlockData ssybc::Block<BlockData, HashCalculator>::Data() const
{
  return data_;
}

template<typename BlockData, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockData, HashCalculator>::Hash() const
{
  if (hash_ == HashType{}) {
    hash_ = HashCalculator().Hash(ToBinaryData());
  }
  return hash_;
}

template<typename BlockData, typename HashCalculator>
std::string ssybc::Block<BlockData, HashCalculator>::ToString() const
{
  return std::string();
}

template<typename BlockData, typename HashCalculator>
ssybc::BinaryData ssybc::Block<BlockData, HashCalculator>::ToBinaryData() const
{
  return BinaryData();
}



