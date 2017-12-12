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


#ifndef SSYBC_SRC_BLOCK_BLOCK_IMPL_HPP_
#define SSYBC_SRC_BLOCK_BLOCK_IMPL_HPP_

#include "include/ssybc/block/block.hpp"
#include "include/ssybc/utility/utility.hpp"
#include "include/ssybc/utility/operator.hpp"

#include <exception>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <string>


// --------------------------------------------- Constructor & Destructor ---------------------------------------------


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Block(
  BlockIndex const block_index,
  BlockTimeInterval const time_stamp,
  BlockHash const &previous_hash,
  BlockNonce const nonce,
  BlockContent const &content) :
  index_{block_index},
  time_stamp_{time_stamp},
  previous_hash_{previous_hash},
  nonce_{nonce},
  content_{content},
  hash_{HashCalculator().Hash(HashableBinaryData())}
{
  assert(sizeof(Byte) == 1);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Block(const Block & block) :
  Block(
    block.Index(),
    block.TimeStamp(),
    block.PreviousBlockHash(),
    block.Nonce(),
    block.Content())
{ EMPTY_BLOCK }


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Block(Block && block) :
  Block(
    block.Index(),
    block.TimeStamp(),
    std::move(block.PreviousBlockHash()),
    block.Nonce(),
    std::move(block.Content()))
{ EMPTY_BLOCK }


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Block(BinaryData const &binary_data) :
  Block(
    IndexFromBinaryBlockData_(binary_data),
    TimeStampFromBinaryBlockData_(binary_data),
    PreviousHashFromBinaryBlockData_(binary_data),
    NonceFromBinaryBlockData_(binary_data),
    ContentFromBinaryBlockData_(binary_data)
  )
{
  auto const stored_hash_in_binary = HashFromBinaryBlockData_(binary_data);
  auto const real_hash = Hash();
  if (stored_hash_in_binary != real_hash) {
    throw std::logic_error(
      "Cannot initialize block from binary data: "
      "stored hash \"" + util::HexStringFromBytes(stored_hash_in_binary) + "\" is not the same as real hash "
      "\"" + util::HexStringFromBytes(real_hash) + "\"."
    );
  }
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::~Block()
{ EMPTY_BLOCK }


// --------------------------------------------------- Public Method --------------------------------------------------


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
ssybc::BlockHash ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Hash() const
{
  return hash_;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
std::string ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::PreviousBlockHashAsString() const
{
  return util::HexStringFromBytes(PreviousBlockHash());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
std::string ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::HashAsString() const
{
  return util::HexStringFromBytes(Hash());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BlockNonce ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Nonce() const
{
  return nonce_;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
auto ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::SizeOfBinaryContent() const -> SizeT
{
  return ContentAsBinary_().size();
}

template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
auto ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::SizeOfBinaryBlock() const -> SizeT
{
  SizeT const result =
    sizeof(SizeT)
    + IndexAsBinary_().size()
    + TimeStampAsBinary_().size()
    + NonceAsBinary_().size()
    + HashCalculator().SizeOfHashInBytes() * 2
    + SizeOfBinaryContent();
  return result;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
BlockContent ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Content() const
{
  return BlockContent(content_);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::operator std::string() const
{
  return Description();
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
std::string ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::Description() const
{
  std::string result{ "{\n\tindex: " };
  result += std::to_string(Index());
  result += ",\n\ttime_stamp: ";
  result += util::DateTimeStringFromTimeStamp(TimeStamp());
  result += ",\n\tnonce: ";
  result += std::to_string(Nonce());
  result += ",\n\tpre_hash: ";
  result += PreviousBlockHashAsString();
  result += ",\n\tcur_hash: ";
  result += HashAsString();
  result += ",\n\tcontent_size_in_bytes: ";
  result += std::to_string(SizeOfBinaryContent());
  result += ",\n\tcontent: ";

  std::string content_str{};
  auto content = Content();

  try {
    content_str = util::Description(content);
  }
  catch (const std::exception& e) {
    auto content_binary = ContentAsBinary_();
    content_str = util::HexStringFromBytes(content_binary, " ");
  }

  result += content_str;
  result += "\n}";
  return result;
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BinaryData ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator>::ToBinaryBlock() const
{
  return util::ConcatenateMoveDestructive(BlockBinaryArr_());
}

template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::HashableBinaryData() const
{
  return util::ConcatenateMoveDestructive(HashableBinaryArr_());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
ssybc::Block<BlockContent, ContentBinaryConverterTemplate, HashCalculator> ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::BlockWithDifferentNonce(BlockNonce const nonce) const
{
  return Block(Index(), TimeStamp(), PreviousBlockHash(), nonce, Content());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline bool ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::operator==(Block const & block) const
{
  return
    Index() == block.Index() &&
    TimeStamp() == block.TimeStamp() &&
    PreviousBlockHash() == block.PreviousBlockHash() &&
    Hash() == block.Hash() &&
    Nonce() == block.Nonce();
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline bool ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::operator!=(Block const & block) const
{
  return !((*this) == block);
}


// -------------------------------------------------- Private Method --------------------------------------------------


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::IndexAsBinary_() const
{
  return BinaryDataConverterDefault<BlockIndex>().BinaryDataFromData(Index());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::TimeStampAsBinary_() const
{
  return BinaryDataConverterDefault<BlockTimeInterval>().BinaryDataFromData(TimeStamp());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::PreviousHashAsBinary_() const
{
  return BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(PreviousBlockHash());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::NonceAsBinary_() const
{
  return BinaryDataConverterDefault<BlockNonce>().BinaryDataFromData(Nonce());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::ContentAsBinary_() const
{
  return ContentBinaryConverterType().BinaryDataFromData(Content());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::SizeOfBlockAsBinary_() const
{
  return BinaryDataConverterDefault<SizeT>().BinaryDataFromData(SizeOfBinaryBlock());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline ssybc::BinaryData ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::HashAsBinary_() const
{
  return BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(Hash());
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::BlockBinaryArr_() const -> std::vector<BinaryData>
{
  return {
    SizeOfBlockAsBinary_(),
    IndexAsBinary_(),
    TimeStampAsBinary_(),
    NonceAsBinary_(),
    PreviousHashAsBinary_(),
    HashAsBinary_(),
    ContentAsBinary_()
  };
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::HashableBinaryArr_() const -> std::vector<BinaryData>
{
  return {
    IndexAsBinary_(),
    TimeStampAsBinary_(),
    PreviousHashAsBinary_(),
    ContentAsBinary_(),
    NonceAsBinary_()
  };
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::SizeOfBinaryBlockFromBinaryBlockData_(BinaryData const &data) const -> SizeT
{
  auto begin_iter = data.begin();
  auto end_iter = data.begin();
  std::advance(end_iter, sizeof(SizeT));
  BinaryData const data_tmp{begin_iter, end_iter};
  return BinaryDataConverterDefault<SizeT>().DataFromBinaryData(data_tmp);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::IndexFromBinaryBlockData_(BinaryData const &data) const -> BlockIndex
{
  auto begin_iter = data.begin();
  std::advance(begin_iter, sizeof(SizeT));
  auto end_iter = begin_iter;
  std::advance(end_iter, sizeof(BlockIndex));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockIndex>().DataFromBinaryData(data_tmp);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::TimeStampFromBinaryBlockData_(BinaryData const &data) const -> BlockTimeInterval
{
  auto begin_iter = data.begin();
  std::advance(begin_iter, sizeof(SizeT) + sizeof(BlockIndex));
  auto end_iter = begin_iter;
  std::advance(end_iter, sizeof(BlockTimeInterval));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockTimeInterval>().DataFromBinaryData(data_tmp);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::NonceFromBinaryBlockData_(BinaryData const &data) const -> BlockNonce
{
  auto begin_iter = data.begin();
  std::advance(begin_iter, sizeof(SizeT) + sizeof(BlockIndex) + sizeof(BlockTimeInterval));
  auto end_iter = begin_iter;
  std::advance(end_iter, sizeof(BlockNonce));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockNonce>().DataFromBinaryData(data_tmp);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::PreviousHashFromBinaryBlockData_(BinaryData const &data) const -> BlockHash
{
  auto begin_iter = data.begin();
  std::advance(begin_iter, sizeof(SizeT) + sizeof(BlockIndex) + sizeof(BlockTimeInterval) + sizeof(BlockNonce));
  auto end_iter = begin_iter;
  std::advance(end_iter, HashCalculator().SizeOfHashInBytes());
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockHash>().DataFromBinaryData(data_tmp);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::HashFromBinaryBlockData_(BinaryData const &data) const -> BlockHash
{
  auto begin_iter = data.begin();
  std::advance(begin_iter,
    sizeof(SizeT)
    + sizeof(BlockIndex)
    + sizeof(BlockTimeInterval)
    + sizeof(BlockNonce)
    + HashCalculator().SizeOfHashInBytes());
  auto end_iter = begin_iter;
  std::advance(end_iter, HashCalculator().SizeOfHashInBytes());
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockHash>().DataFromBinaryData(data_tmp);
}


template<typename BlockContent, template<typename> class ContentBinaryConverterTemplate, typename HashCalculator>
inline auto ssybc::Block<
  BlockContent,
  ContentBinaryConverterTemplate,
  HashCalculator>::ContentFromBinaryBlockData_(BinaryData const &data) const -> BlockContent
{
  auto begin_iter = data.begin();
  SizeT const block_size_without_content{
    sizeof(SizeT)
    + sizeof(BlockIndex)
    + sizeof(BlockTimeInterval)
    + sizeof(BlockNonce)
    + HashCalculator().SizeOfHashInBytes() * 2
  };
  SizeT const content_size{SizeOfBinaryBlockFromBinaryBlockData_(data) - block_size_without_content};
  std::advance(begin_iter, block_size_without_content);
  auto end_iter = begin_iter;
  std::advance(end_iter, content_size);
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockContent>().DataFromBinaryData(data_tmp);
}


#endif  // BLOCKCHAIN_SRC_BLOCK_BLOCK_IMPL_HPP_
