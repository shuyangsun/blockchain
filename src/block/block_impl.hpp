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
#include <utility>


// --------------------------------------------- Constructor & Destructor ---------------------------------------------


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(BlockHeaderType const & header):
  header_{ header },
  content_ptr_{ nullptr }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
  inline ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(BlockHeaderType && header) :
  header_{ header },
  content_ptr_{ nullptr }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
  inline ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(BlockHeaderType const & header, BlockContentType const &content) :
  header_{ header },
  content_ptr_{ std::make_unique<BlockContentType const>(BlockContentType(content)) }
{
  if (header.MerkleRoot() != content.Hash()) {
    ThrowContentHashDoesNotMatchMerkleRootException_();
  }
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(BlockHeaderType && header, BlockContentType &&content) :
  header_{ header },
  content_ptr_{ std::make_unique<BlockContentType const>(BlockContentType(content)) }
{
  if (header.MerkleRoot() != content.Hash()) {
    ThrowContentHashDoesNotMatchMerkleRootException_();
  }
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline ssybc::Block<DataT, ContentBinaryConverterTemplate, HeaderHashCalculatorT, ContentHashCalculatorT>::Block(
  BlockVersion const block_version,
  BlockIndex const block_index,
  BlockHash const & previous_hash,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce,
  DataT const &data):
  content_ptr_{ std::make_unique<BlockContentType const>(BlockContentType(data)) },
  header_{ block_version, block_index, BlockContentType(data).Hash(), previous_hash, time_stamp, nonce }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline ssybc::Block<DataT, ContentBinaryConverterTemplate, HeaderHashCalculatorT, ContentHashCalculatorT>::Block(
  BlockVersion const block_version,
  BlockIndex const block_index,
  BlockHash && previous_hash,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce,
  DataT &&data) :
  content_ptr_{ std::make_unique<BlockContentType const>(BlockContentType(data)) },
  header_{ block_version, block_index, BlockContentType(data).Hash(), previous_hash, time_stamp, nonce }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(
    BlockVersion const block_version,
    BlockIndex const block_index,
    BlockHash const & merkle_root,
    BlockHash const & previous_hash,
    BlockTimeInterval const time_stamp,
    BlockNonce const nonce
  ):
  header_{ block_version, block_index, merkle_root, previous_hash, time_stamp, nonce },
  content_ptr_{ nullptr }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(
    BlockVersion const block_version,
    BlockIndex const block_index,
    BlockHash && merkle_root,
    BlockHash && previous_hash,
    BlockTimeInterval const time_stamp,
    BlockNonce const nonce
  ) :
  header_{ block_version, block_index, merkle_root, previous_hash, time_stamp, nonce },
  content_ptr_{ nullptr }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(Block const & block) :
  header_{ block.Header() },
  content_ptr{ block.IsHeaderOnly()
  ? nullptr : std::make_unique<BlockContentType const>(BlockContentType(block.Content())) }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(Block &&block) :
  header_{ block.Header() },
  content_ptr{ block.IsHeaderOnly()
  ? nullptr : std::make_unique<BlockContentType const>(BlockContentType(block.Content())) }
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(BinaryData const &binary_data):
  Block(BinaryData{binary_data.begin(), binary_data.end()})
{ EMPTY_BLOCK }


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Block(BinaryData &&binary_data):
  header_{ HeaderFromBinaryData_(std::forward<BinaryData>(binary_data)) },
  content_ptr_{ ContentPtrFromBinaryData_(std::forward<BinaryData>(binary_data)) }
{
  if (!IsHeaderOnly() && content_ptr_->Hash() != header_.MerkleRoot()) {
    ThrowContentHashDoesNotMatchMerkleRootException_();
  }
}


// --------------------------------------------------- Public Method --------------------------------------------------


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline bool ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::IsHeaderOnly() const
{
  return content_ptr_ == nullptr;
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline auto ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Header() const -> BlockHeaderType
{
  return header_;
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline auto ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Content() const -> BlockContentType
{
  if (IsHeaderOnly()) {
    throw std::logic_error(
      "Block " + util::ToString(Header().Index()) + "is only contains header information, cannot access its content."
    );
  }
  return *content_ptr_;
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline auto ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Binary() const -> BinaryData
{
  SizeT size_of_content = 0;
  if (!IsHeaderOnly()) {
    size_of_content = content_ptr_->SizeOfBinary();
  }
  auto size_of_content_binary = BinaryDataConverterDefault<SizeT>().BinaryDataFromData(size_of_content);
  std::vector<BinaryData> result_binaries{ Header().Binary() };
  result_binaries.push_back(size_of_content_binary);
  if (!IsHeaderOnly()) {
    result_binaries.push_back(content_ptr_->Binary());
  }
  return util::ConcatenateMoveDestructive(result_binaries);
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::operator std::string() const
{
  return Description();
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
std::string ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::Description() const
{
  std::string result{ "{\n  header: {\n" };
  result += Header().Description("    ");
  result += "\n  },\n  content: ";
  if (IsHeaderOnly()) {
    result += "__CONTENT_NOT_PROVIDED__\n}";
    return result;
  }
  result += "{\n";
  result += content_ptr_->Description("    ");
  result += "\n  }\n}";
  return result;
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline bool ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::operator==(Block const & block) const
{
  return !((*this) != block);
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline bool ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::operator!=(Block const & block) const
{
  return header_ != block.header_;
}


// -------------------------------------------------- Private Method --------------------------------------------------


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline auto ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::HeaderFromBinaryData_(
    BinaryData &&binary_data) const -> BlockHeaderType
{
  auto begin_iter = binary_data.begin();
  auto end_iter = binary_data.begin();
  std::advance(end_iter, static_cast<std::size_t>(BlockHeaderType::SizeOfBinary()));
  auto header_binary_copy = BinaryData{ begin_iter, end_iter };
  auto header = BlockHeaderType(std::move(header_binary_copy));
  binary_data.erase(begin_iter, end_iter);
  return header;
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline auto ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::ContentPtrFromBinaryData_(
    BinaryData &&binary_data) const -> std::unique_ptr<BlockContentType const>
{
  auto begin_iter = binary_data.begin();
  auto end_iter = binary_data.begin();
  std::advance(end_iter, sizeof(SizeT));
  auto size_binary_copy = BinaryData{ begin_iter, end_iter };
  auto const size_of_content_data = BinaryDataConverterDefault<SizeT>().DataFromBinaryData(size_binary_copy);
  binary_data.erase(begin_iter, end_iter);

  if (size_of_content_data <= 0) {
    return nullptr;
  }

  begin_iter = binary_data.begin();
  end_iter = begin_iter;
  std::advance(end_iter, static_cast<std::size_t>(size_of_content_data));
  auto content_ptr = std::make_unique<BlockContentType const>(BlockContentType{ binary_data });
  binary_data.erase(begin_iter, end_iter);
  return content_ptr;
}


template<
  typename DataT,
  template<typename> class ContentBinaryConverterTemplate,
  typename HeaderHashCalculatorT,
  typename ContentHashCalculatorT
>
inline void ssybc::Block<
  DataT,
  ContentBinaryConverterTemplate,
  HeaderHashCalculatorT,
  ContentHashCalculatorT>::ThrowContentHashDoesNotMatchMerkleRootException_() const
{
  throw std::logic_error(
    "Cannot construct block with content and header, content hash does not match merkle root."
  );
}

#endif  // BLOCKCHAIN_SRC_BLOCK_BLOCK_IMPL_HPP_
