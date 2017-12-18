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


#ifndef SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_HEADER_BLOCK_HEADER_HPP_
#define SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_HEADER_BLOCK_HEADER_HPP_

#include "include/ssybc/general/general.hpp"
#include "include/ssybc/miner/block_miner.hpp"

#include <string>

namespace ssybc {

  template<typename HashCalculatorT>
  class BlockHeader {

  public:

// --------------------------------------------- Constructor & Destructor ---------------------------------------------

    BlockHeader() = delete;

    BlockHeader(
      BlockVersion const version,
      BlockIndex const index,
      BlockHash const &merkle_root,
      BlockHash const &previous_hash,
      BlockTimeInterval const time_stamp,
      BlockNonce const nonce
    );

    BlockHeader(
      BlockVersion const version,
      BlockIndex const index,
      BlockHash &&merkle_root,
      BlockHash &&previous_hash,
      BlockTimeInterval const time_stamp,
      BlockNonce const nonce
    );

    BlockHeader(BinaryData const &binary_data);
    BlockHeader(BinaryData &&binary_data);

    BlockHeader(BlockHeader const &header);
    BlockHeader(BlockHeader &&header);

    ~BlockHeader() = default;

// --------------------------------------------------- Public Method --------------------------------------------------

    BlockVersion Version() const;
    BlockIndex Index() const;
    BlockHash MerkleRoot() const;
    BlockHash PreviousHash() const;
    BlockTimeInterval TimeStamp() const;
    BlockNonce Nonce() const;

    BinaryData Binary() const;
    BlockHash Hash() const;

    static SizeT SizeOfBinary();
    std::string PreviousBlockHashAsString() const;
    std::string HashAsString() const;

    BlockHeader HeaderWithDifferentMinedResult(MinedResult const mined_result) const;

    operator std::string() const;
    std::string Description() const;
    virtual std::string Description(std::string const &lead_padding) const;

    BlockHeader& operator=(BlockHeader &&) = delete;
    BlockHeader& operator=(BlockHeader const &) = delete;

    bool operator==(BlockHeader const & header) const;
    bool operator!=(BlockHeader const & header) const;

  private:

// -------------------------------------------------- Private Field ---------------------------------------------------

    BlockVersion const version_;
    BlockIndex const index_;
    BlockHash const previous_hash_;
    BlockHash const merkle_root_;
    BlockTimeInterval const time_stamp_;
    BlockNonce const nonce_;
    BlockHash const hash_;

// -------------------------------------------------- Private Method --------------------------------------------------

    BinaryData VersionAsBinary_() const;
    BinaryData IndexAsBinary_() const;
    BinaryData MerkleRootAsBinary_() const;
    BinaryData PreviousHashAsBinary_() const;
    BinaryData TimeStampAsBinary_() const;
    BinaryData NonceAsBinary_() const;

    BlockVersion VersionFromBinaryData_(BinaryData const &data) const;
    BlockIndex IndexFromBinaryData_(BinaryData const &data) const;
    BlockHash MerkleRootFromBinaryData_(BinaryData const &data) const;
    BlockHash PreviousHashFromBinaryData_(BinaryData const &data) const;
    BlockTimeInterval TimeStampFromBinaryData_(BinaryData const &data) const;
    BlockNonce NonceFromBinaryData_(BinaryData const &data) const;
    
  };

}  // namespace ssybc


#include "src/block/block_header/block_header_impl.hpp"


#endif  // SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_HEADER_BLOCK_HEADER_HPP_

