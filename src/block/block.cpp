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
#include "utility/utility.hpp"

#include <exception>
#include <cassert>

namespace ssybc {
  template<typename BlockData>
  std::string StringFromBlockData_(BlockData const data);
};

template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::Block(
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
{
  assert(sizeof(Byte) == 1);
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::Block(const Block & block) :
  Block(block.Index(), block.TimeStamp(), block.PreviousBlockHash(), block.Nonce(), block.Data())
{ EMPTY_BLOCK }


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::Block(Block && block) :
  Block(block.Index(), block.TimeStamp(), std::move(block.PreviousBlockHash()), block.Nonce(), std::move(block.Data()))
{ EMPTY_BLOCK }


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::~Block()
{
  delete index_;
  delete time_stamp_;
  delete previous_hash_;
  delete nonce_;
  delete data_;
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::BlockIndex ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::Index() const
{
  return index_;
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::BlockTimeInterval ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::TimeStamp() const
{
  return time_stamp_;
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::PreviousBlockHash() const
{
  return previous_hash_;
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::BlockNonce ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::Nonce() const
{
  return nonce_;
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
BlockData ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::Data() const
{
  return BlockData(data_);
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::Hash() const
{
  if (hash_ == HashType{}) {
    hash_ = HashCalculator().Hash(ToBinaryData());
  }
  return hash_;
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::operator std::string() const
{
  return ToString();
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
std::string ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::ToString() const
{
  std::string result{ "{\n\tindex: " };
  result += std::string(std::string{ index_ });
  result += ",\n\ttime_stamp: ";
  result += util::DateTimeStringFromTimeStamp(TimeStamp());
  result += ",\n\tnonce: ";
  result += std::string{ Nonce() };
  result += ",\n\tprevious_hash: ";
  result += std::string{ PreviousBlockHash() };
  result += ",\n\thash: ";
  result += std::string{ Hash() };
  result += ",\n\tdata: ";
  result += StringFromBlockData_(Data());
  retulr += "\n}";
  return result;
}


template<typename BlockData, typename BinaryDataConverter, typename HashCalculator>
ssybc::BinaryData ssybc::Block<BlockData, BinaryDataConverter, HashCalculator>::ToBinary() const
{
  return BinaryData();
}


template<typename BlockData>
std::string ssybc::StringFromBlockData_(BlockData const data)
{
  try {
    return std::string(data);
  }
  catch {
    return "unformated_data";
  }
}

