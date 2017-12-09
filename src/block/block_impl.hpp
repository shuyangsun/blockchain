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


#ifndef BLOCKCHAIN_SRC_BLOCK_BLOCK_IMPL_HPP_
#define BLOCKCHAIN_SRC_BLOCK_BLOCK_IMPL_HPP_

#include "include/block/block.hpp"
#include "include/utility/utility.hpp"

#include <exception>
#include <cassert>
#include <algorithm>
#include <iterator>


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Block(
  BlockIndex block_index,
  BlockTimeInterval time_stamp,
  BlockHash previous_hash,
  BlockNonce nonce,
  BlockContent content) :
  index_{block_index},
  time_stamp_{time_stamp},
  previous_hash_{previous_hash},
  nonce_{nonce},
  content_{content},
  hash_{ HashCalculator().Hash(HashableBinaryData()) }
{
  assert(sizeof(Byte) == 1);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Block(const Block & block) :
  Block(block.Index(), block.TimeStamp(), block.PreviousBlockHash(), block.Nonce(), block.Content())
{ EMPTY_BLOCK }


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Block(Block && block) :
  Block(block.Index(), block.TimeStamp(), std::move(block.PreviousBlockHash()), block.Nonce(), std::move(block.Content()))
{ EMPTY_BLOCK }


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::~Block()
{ EMPTY_BLOCK }


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BlockIndex ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Index() const
{
  return index_;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BlockTimeInterval ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::TimeStamp() const
{
  return time_stamp_;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::PreviousBlockHash() const
{
  return previous_hash_;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BlockNonce ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Nonce() const
{
  return nonce_;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
size_t ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::SizeOfContentAsBinaryInBytes() const
{
  return ContentBinaryConverter().BinaryDataFromData(Content()).size();
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
BlockContent ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Content() const
{
  return BlockContent(content_);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Hash() const
{
  return hash_;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::operator std::string() const
{
  return ToString();
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
std::string ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::ToString() const
{
  std::string result{ "{\n\tindex: " };
  result += std::to_string(Index());
  result += ",\n\ttime_stamp: ";
  result += util::DateTimeStringFromTimeStamp(TimeStamp());
  result += ",\n\tnonce: ";
  result += std::to_string(Nonce());
  result += ",\n\tprevious_hash: ";
  result += PreviousBlockHash();
  result += ",\n\thash: ";
  result += Hash();
  result += ",\n\tcontent_size_in_bytes: ";
  result += std::to_string(SizeOfContentAsBinaryInBytes());
  result += ",\n\tcontent: ";

  std::string content_str{};
  auto content = Content();
  try {
    content_str = std::string{ content };
  }
  catch (const std::exception& e) {
    auto content_binary = ContentBinaryConverter().BinaryDataFromData(content);
    content_str = util::HexStringFromByte(content_binary);
  }

  result += content_str;
  result += "\n}";
  return result;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BinaryData ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::ToBinaryBlock() const
{
  auto index_binary = BinaryDataConverterDefault<BlockIndex>().BinaryDataFromData(Index());
  auto time_stamp_binary = BinaryDataConverterDefault<BlockTimeInterval>().BinaryDataFromData(TimeStamp());
  auto nonce_binary = BinaryDataConverterDefault<BlockNonce>().BinaryDataFromData(Nonce());
  auto prev_hash_binary = BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(PreviousBlockHash());
  auto hash_binary = BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(Hash());
  auto content_binary = ContentBinaryConverter().BinaryDataFromData(Content());
  auto content_size_binary = BinaryDataConverterDefault<size_t>().BinaryDataFromData(content_binary.size());
  
  std::vector<BinaryData> binarys{
    index_binary ,
    time_stamp_binary,
    nonce_binary,
    prev_hash_binary,
    hash_binary,
    content_size_binary,
    content_binary
  };

  BinaryData result{};
  for (auto &bin_data : binarys) {
    result.insert(
      result.end(),
      std::make_move_iterator(bin_data.begin()),
      std::make_move_iterator(bin_data.end())
    );
  }

  return result;
}

template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BinaryData ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::HashableBinaryData() const
{
  auto index_binary = BinaryDataConverterDefault<BlockIndex>().BinaryDataFromData(Index());
  auto time_stamp_binary = BinaryDataConverterDefault<BlockTimeInterval>().BinaryDataFromData(TimeStamp());
  auto nonce_binary = BinaryDataConverterDefault<BlockNonce>().BinaryDataFromData(Nonce());
  auto prev_hash_binary = BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(PreviousBlockHash());
  auto content_binary = ContentBinaryConverter().BinaryDataFromData(Content());

  std::vector<BinaryData> binarys{
    index_binary ,
    time_stamp_binary,
    nonce_binary,
    prev_hash_binary,
    content_binary
  };

  BinaryData result{};
  for (auto &bin_data : binarys) {
    result.insert(
      result.end(),
      std::make_move_iterator(bin_data.begin()),
      std::make_move_iterator(bin_data.end())
    );
  }

  return result;
}


#endif  // BLOCKCHAIN_SRC_BLOCK_BLOCK_IMPL_HPP_
