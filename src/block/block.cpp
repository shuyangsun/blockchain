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


#include "include/block/block.hpp"
#include "include/utility/utility.hpp"

#include <exception>
#include <cassert>
#include <algorithm>


namespace ssybc {
  template<typename BlockContent>
  std::string StringFromBlockContent_(BlockContent const data);
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::Block(
  BlockIndex block_index,
  BlockTimeInterval time_stamp,
  BlockHash previous_hash,
  BlockNonce nonce,
  BlockContent content) :
  index_{block_index},
  time_stamp_{time_stamp},
  previous_hash_{previous_hash},
  nonce_{nonce},
  content_{content}
{
  assert(sizeof(Byte) == 1);
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::Block(const Block & block) :
  Block(block.Index(), block.TimeStamp(), block.PreviousBlockHash(), block.Nonce(), block.Content())
{ EMPTY_BLOCK }


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::Block(Block && block) :
  Block(block.Index(), block.TimeStamp(), std::move(block.PreviousBlockHash()), block.Nonce(), std::move(block.Content()))
{ EMPTY_BLOCK }


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::~Block()
{
  delete index_;
  delete time_stamp_;
  delete previous_hash_;
  delete nonce_;
  delete content_;
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::BlockIndex ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::Index() const
{
  return index_;
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::BlockTimeInterval ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::TimeStamp() const
{
  return time_stamp_;
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::PreviousBlockHash() const
{
  return previous_hash_;
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::BlockNonce ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::Nonce() const
{
  return nonce_;
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
size_t ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::SizeOfContentAsBinaryInBytes() const
{
  return ContentAsBinary_().size();
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
BlockContent ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::Content() const
{
  return BlockContent(content_);
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::BlockHash ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::Hash() const
{
  if (hash_ == HashType{}) {
    hash_ = HashCalculator().Hash(ToBinaryBlock());
  }
  return hash_;
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::operator std::string() const
{
  return ToString();
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
std::string ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::ToString() const
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
  result += ",\n\tcontent_size_in_bytes: ";
  result += std::string{ SizeOfContentAsBinaryInBytes() };
  result += ",\n\tcontent: ";
  result += StringFromBlockContent_(Content());
  retulr += "\n}";
  return result;
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::BinaryData ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::ContentAsBinary_() const
{
  return BinaryDataConverter_().BinaryDataFromData(content_);
}


template<typename BlockContent, template<typename> class BinaryDataConverterTemplate, typename HashCalculator>
ssybc::BinaryData ssybc::Block<BlockContent, BinaryDataConverterTemplate, HashCalculator>::ToBinaryBlock() const
{
  // TODO
  return BinaryData();
}


template<typename BlockContent>
std::string ssybc::StringFromBlockContent_(BlockContent const data)
{
  try {
    return std::string(data);
  }
  catch {
    return util::HexStringFromByte(ContentAsBinary_());
  }
}

