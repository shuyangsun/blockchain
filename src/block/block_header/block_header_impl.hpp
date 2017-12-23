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


#ifndef SSYBC_SRC_BLOCK_BLOCK_HEADER_BLOCK_HEADER_IMPL_HPP_
#define SSYBC_SRC_BLOCK_BLOCK_HEADER_BLOCK_HEADER_IMPL_HPP_


#include "include/ssybc/block/block_header/block_header.hpp"

#include "include/ssybc/utility/utility.hpp"
#include "include/ssybc/utility/operator.hpp"
#include "include/ssybc/binary_data_converter/binary_data_converter_default.hpp"


// --------------------------------------------- Constructor & Destructor ---------------------------------------------


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(
  BlockVersion const version,
  BlockIndex const index,
  BlockHash const & merkle_root,
  BlockHash const & previous_hash,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce):
  version_{ version },
  index_{ index },
  merkle_root_{ merkle_root.begin(), merkle_root.end() },
  previous_hash_{ previous_hash.begin(), previous_hash.end() },
  time_stamp_{ time_stamp },
  nonce_{ nonce },
  hash_{ HashCalculatorT().Hash(Binary()) }
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(
  BlockVersion const version,
  BlockIndex const index,
  BlockHash && merkle_root,
  BlockHash && previous_hash,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce) :
  version_{ version },
  index_{ index },
  merkle_root_{ merkle_root },
  previous_hash_{ previous_hash },
  time_stamp_{ time_stamp },
  nonce_{ nonce },
  hash_{ HashCalculatorT().Hash(Binary()) }
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BlockHeader const & header) :
  BlockHeader(
    header.Version(),
    header.Index(),
    header.MerkleRoot(),
    header.PreviousHash(),
    header.TimeStamp(),
    header.Nonce())
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BlockHeader && header) :
  BlockHeader(
    header.Version(),
    header.Index(),
    header.MerkleRoot(),
    header.PreviousHash(),
    header.TimeStamp(),
    header.Nonce())
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BinaryData const & binary_data):
  BlockHeader(
    VersionFromBinaryData_(binary_data),
    IndexFromBinaryData_(binary_data),
    MerkleRootFromBinaryData_(binary_data),
    PreviousHashFromBinaryData_(binary_data),
    TimeStampFromBinaryData_(binary_data),
    NonceFromBinaryData_(binary_data)
  )
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BinaryData && binary_data):
  BlockHeader(
    VersionFromBinaryData_(binary_data),
    IndexFromBinaryData_(binary_data),
    MerkleRootFromBinaryData_(binary_data),
    PreviousHashFromBinaryData_(binary_data),
    TimeStampFromBinaryData_(binary_data),
    NonceFromBinaryData_(binary_data)
  )
{ EMPTY_BLOCK }


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename HashCalculatorT>
inline ssybc::BlockVersion ssybc::BlockHeader<HashCalculatorT>::Version() const
{
  return version_;
}

template<typename HashCalculatorT>
inline ssybc::BlockIndex ssybc::BlockHeader<HashCalculatorT>::Index() const
{
  return index_;
}

template<typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::MerkleRoot() const
{
  return BinaryData{ merkle_root_.begin(), merkle_root_.end() };
}

template<typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::PreviousHash() const
{
  return BinaryData{ previous_hash_.begin(), previous_hash_.end() };;
}

template<typename HashCalculatorT>
inline ssybc::BlockTimeInterval ssybc::BlockHeader<HashCalculatorT>::TimeStamp() const
{
  return time_stamp_;
}

template<typename HashCalculatorT>
inline ssybc::BlockNonce ssybc::BlockHeader<HashCalculatorT>::Nonce() const
{
  return nonce_;
}

template<typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockHeader<HashCalculatorT>::Binary() const
{
  auto binaries = std::vector<BinaryData>{
    VersionAsBinary_(),
    IndexAsBinary_(),
    MerkleRootAsBinary_(),
    PreviousHashAsBinary_(),
    TimeStampAsBinary_(),
    NonceAsBinary_()
  };
  return util::ConcatenateMoveDestructive(binaries);
}

template<typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::Hash() const
{
  return BinaryData{ hash_.begin(), hash_.end() };
}


template<typename HashCalculatorT>
inline ssybc::SizeT ssybc::BlockHeader<HashCalculatorT>::SizeOfBinary()
{
  return
    sizeof(BlockVersion)
    + sizeof(BlockIndex)
    + HashCalculatorT().SizeOfHashInBytes() * 2
    + sizeof(BlockTimeInterval)
    + sizeof(BlockNonce);
}


template<typename HashCalculatorT>
inline std::string ssybc::BlockHeader<HashCalculatorT>::PreviousBlockHashAsString() const
{
  return util::HexStringFromBytes(PreviousHash());
}

template<typename HashCalculatorT>
inline std::string ssybc::BlockHeader<HashCalculatorT>::HashAsString() const
{
  return util::HexStringFromBytes(Hash());
}

template<typename HashCalculatorT>
inline auto ssybc::BlockHeader<HashCalculatorT>::HeaderWithDifferentMinedResult(
  MinedResult const mined_result) const -> BlockHeader
{
  return BlockHeader(Version(), Index(), PreviousHash(), MerkleRoot(), mined_result.time_stamp, mined_result.nonce);
}

template<typename HashCalculatorT>
inline std::string ssybc::BlockHeader<HashCalculatorT>::Description() const
{
  return Description("");
}

template<typename HashCalculatorT>
inline std::string ssybc::BlockHeader<HashCalculatorT>::Description(std::string const & lead_padding) const
{
  std::string result{ lead_padding + "version: " };
  result += (util::ToString(Version()) + ",\n");
  result += (lead_padding + "index: ");
  result += (util::ToString(Index()) + ",\n");
  result += (lead_padding + "time_stamp: ");
  result += (util::DateTimeStringFromTimeStamp(TimeStamp()) + ",\n");
  result += (lead_padding + "nonce: ");
  result += (util::ToString(Nonce()) + ",\n");
  result += (lead_padding + "merkel_root:   ");
  result += ( util::HexStringFromBytes(MerkleRoot()) + ",\n");
  result += (lead_padding + "previous_hash: ");
  result += (util::HexStringFromBytes(PreviousHash()) + ",\n");
  result += (lead_padding + "hash:          ");
  result += util::HexStringFromBytes(Hash());
  return result;
}

template<typename HashCalculatorT>
inline bool ssybc::BlockHeader<HashCalculatorT>::operator==(BlockHeader const & header) const
{
  return !((*this) != header);
}

template<typename HashCalculatorT>
inline bool ssybc::BlockHeader<HashCalculatorT>::operator!=(BlockHeader const & header) const
{
  return
    Version() != header.Version()
    || Index() != header.Index()
    || PreviousHash() != header.PreviousHash()
    || MerkleRoot() != header.MerkleRoot()
    || TimeStamp() != header.TimeStamp()
    || Nonce() != header.Nonce();
}


// -------------------------------------------------- Private Method --------------------------------------------------


template<typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockHeader<HashCalculatorT>::VersionAsBinary_() const
{
  return BinaryDataConverterDefault<BlockVersion>().BinaryDataFromData(Version());
}

template<typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockHeader<HashCalculatorT>::IndexAsBinary_() const
{
  return BinaryDataConverterDefault<BlockIndex>().BinaryDataFromData(Index());
}

template<typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockHeader<HashCalculatorT>::MerkleRootAsBinary_() const
{
  return BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(MerkleRoot());
}

template<typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockHeader<HashCalculatorT>::PreviousHashAsBinary_() const
{
  return BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(PreviousHash());
}

template<typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockHeader<HashCalculatorT>::TimeStampAsBinary_() const
{
  return BinaryDataConverterDefault<BlockTimeInterval>().BinaryDataFromData(TimeStamp());
}

template<typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockHeader<HashCalculatorT>::NonceAsBinary_() const
{
  return BinaryDataConverterDefault<BlockNonce>().BinaryDataFromData(Nonce());
}

template<typename HashCalculatorT>
inline ssybc::BlockVersion ssybc::BlockHeader<HashCalculatorT>::VersionFromBinaryData_(BinaryData const & data) const
{
  auto begin_iter = data.begin();
  auto end_iter = begin_iter;
  std::advance(end_iter, sizeof(BlockVersion));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockVersion>().DataFromBinaryData(data_tmp);
}

template<typename HashCalculatorT>
inline ssybc::BlockIndex ssybc::BlockHeader<HashCalculatorT>::IndexFromBinaryData_(BinaryData const & data) const
{
  auto begin_iter = data.begin();
  std::advance(begin_iter, sizeof(BlockVersion));
  auto end_iter = begin_iter;
  std::advance(end_iter, sizeof(BlockIndex));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockIndex>().DataFromBinaryData(data_tmp);
}

template<typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::MerkleRootFromBinaryData_(BinaryData const & data) const
{
  auto begin_iter = data.begin();
  std::advance(begin_iter, sizeof(BlockVersion) + sizeof(BlockIndex));
  auto end_iter = begin_iter;
  std::advance(end_iter, static_cast<std::size_t>(HashCalculatorT().SizeOfHashInBytes()));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockHash>().DataFromBinaryData(data_tmp);
}

template<typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::PreviousHashFromBinaryData_(BinaryData const & data) const
{
  auto begin_iter = data.begin();
  auto const size_of_hash = static_cast<std::size_t>(HashCalculatorT().SizeOfHashInBytes());
  std::advance(begin_iter, sizeof(BlockVersion) + sizeof(BlockIndex) + size_of_hash);
  auto end_iter = begin_iter;
  std::advance(end_iter, size_of_hash);
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockHash>().DataFromBinaryData(data_tmp);
}

template<typename HashCalculatorT>
inline ssybc::BlockTimeInterval ssybc::BlockHeader<HashCalculatorT>::TimeStampFromBinaryData_(
  BinaryData const & data) const
{
  auto begin_iter = data.begin();
  auto const size_of_hash = static_cast<std::size_t>(HashCalculatorT().SizeOfHashInBytes());
  std::advance(begin_iter, sizeof(BlockVersion) + sizeof(BlockIndex) + size_of_hash * 2);
  auto end_iter = begin_iter;
  std::advance(end_iter, sizeof(BlockTimeInterval));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockTimeInterval>().DataFromBinaryData(data_tmp);
}

template<typename HashCalculatorT>
inline ssybc::BlockNonce ssybc::BlockHeader<HashCalculatorT>::NonceFromBinaryData_(BinaryData const & data) const
{
  auto begin_iter = data.begin();
  auto const size_of_hash = static_cast<std::size_t>(HashCalculatorT().SizeOfHashInBytes());
  std::advance(begin_iter, sizeof(BlockVersion) + sizeof(BlockIndex) + size_of_hash * 2 + sizeof(BlockTimeInterval));
  auto end_iter = begin_iter;
  std::advance(end_iter, sizeof(BlockNonce));
  BinaryData const data_tmp{ begin_iter, end_iter };
  return BinaryDataConverterDefault<BlockNonce>().DataFromBinaryData(data_tmp);
}


#endif  // SSYBC_SRC_BLOCK_BLOCK_HEADER_BLOCK_HEADER_IMPL_HPP_
