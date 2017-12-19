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


#ifndef SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_HPP_
#define SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_HPP_

#include "include/ssybc/general/general.hpp"
#include "include/ssybc/block/block_header/block_header.hpp"
#include "include/ssybc/block/block_content/block_content.hpp"
#include "include/ssybc/hash_calculator/hash_calculator_double_sha256.hpp"
#include "include/ssybc/binary_data_converter/binary_data_converter_default.hpp"

#include <memory>

namespace ssybc {

  template<
    typename DataT,
    template<typename> class ContentBinaryConverterTemplate = BinaryDataConverterDefault,
    typename HeaderHashCalculatorT = DoubleSHA256Calculator,
    typename ContentHashCalculatorT = HeaderHashCalculatorT>
  class Block {

  public:

// -------------------------------------------------- Type Definition -------------------------------------------------

    using DataType = DataT;
    using ContentBinaryConverterType = ContentBinaryConverterTemplate<DataT>;
    using BlockHeaderType = BlockHeader<HeaderHashCalculatorT>;
    using BlockContentType = BlockContent<DataT, ContentBinaryConverterTemplate, ContentHashCalculatorT>;
    using HeaderHashCalculatorType = HeaderHashCalculatorT;
    using ContentHashCalculatorType = ContentHashCalculatorT;

// --------------------------------------------- Constructor & Destructor ---------------------------------------------

    Block() = delete;

    Block(BlockHeaderType const &header);
    Block(BlockHeaderType &&header);

    Block(BlockHeaderType const &header, BlockContentType const &content);
    Block(BlockHeaderType &&header, BlockContentType &&content);

    Block(
      BlockVersion const block_version,
      BlockIndex const block_index,
      BlockHash const &previous_hash,
      BlockTimeInterval const time_stamp,
      BlockNonce const nonce,
      DataT const &data
    );

    Block(
      BlockVersion const block_version,
      BlockIndex const block_index,
      BlockHash &&previous_hash,
      BlockTimeInterval const time_stamp,
      BlockNonce const nonce,
      DataT &&data
    );

    Block(
      BlockVersion const block_version,
      BlockIndex const block_index,
      BlockHash const &merkle_root,
      BlockHash const &previous_hash,
      BlockTimeInterval const time_stamp,
      BlockNonce const nonce
    );

    Block(
      BlockVersion const block_version,
      BlockIndex const block_index,
      BlockHash &&merkle_root,
      BlockHash &&previous_hash,
      BlockTimeInterval const time_stamp,
      BlockNonce const nonce
    );

    Block(Block const &block);
    Block(Block &&block);

    Block(BinaryData const &binary_data);
    Block(BinaryData &&binary_data);
    
    ~Block() = default;

// --------------------------------------------------- Public Method --------------------------------------------------

    bool IsHeaderOnly() const;
    BlockHeaderType Header() const;
    BlockContentType Content() const;

    BinaryData Binary() const;
    
    operator std::string() const;
    virtual std::string Description() const;

    Block& operator=(Block &&) = delete;
    Block& operator=(Block const &) = delete;

    bool operator==(Block const & block) const;
    bool operator!=(Block const & block) const;

  private:

// -------------------------------------------------- Private Field ---------------------------------------------------

    BlockHeaderType const header_;
    std::unique_ptr<BlockContentType const> const content_ptr_;

// -------------------------------------------------- Private Method --------------------------------------------------

    BlockHeaderType HeaderFromBinaryData_(BinaryData &&binary_data) const;
    std::unique_ptr<BlockContentType const> ContentPtrFromBinaryData_(BinaryData &&binary_data) const;
    void ThrowContentHashDoesNotMatchMerkleRootException_() const;
  };

}  // namespace ssybc


#include "src/block/block_impl.hpp"


#endif  // SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_HPP_

