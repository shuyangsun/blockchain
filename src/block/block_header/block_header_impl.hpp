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
  BlockHash const & previous_hash,
  BlockHash const & merkle_root,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce):
  version_{ version },
  index_{ index },
  previous_hash_{ previous_hash },
  merkle_root_{ merkle_root },
  time_stamp_{ time_stamp },
  nonce_{ nonce },
  hash_{ HashCalculatorT().Hash(Binary()) }
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(
  BlockVersion const version,
  BlockIndex const index,
  BlockHash && previous_hash,
  BlockHash && merkle_root,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce) :
  version_{ version },
  index_{ index },
  previous_hash_{ previous_hash },
  merkle_root_{ merkle_root },
  time_stamp_{ time_stamp },
  nonce_{ nonce },
  hash_{ HashCalculatorT().Hash(Binary()) }
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BlockHeader const & header) :
  BlockHeader(
    header.Version(),
    header.Index(),
    header.PreviousHash(),
    header.MerkleRoot(),
    header.TimeStamp(),
    header.Nonce())
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BlockHeader && header) :
  BlockHeader(
    header.Version(),
    header.Index(),
    header.PreviousHash(),
    header.MerkleRoot(),
    header.TimeStamp(),
    header.Nonce())
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BinaryData const & binary_data):
  // TODO
  BlockHeader()
{ EMPTY_BLOCK }


template<typename HashCalculatorT>
inline ssybc::BlockHeader<HashCalculatorT>::BlockHeader(BinaryData && binary_data):
  // TODO
  BlockHeader()
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
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::PreviousHash() const
{
  return BinaryData{ previous_hash_.begin(), previous_hash_.end() };;
}

template<typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::MerkleRoot() const
{
  return BinaryData{ merkle_root_.begin(), merkle_root_.end() };
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
  return util::ConcatenateMoveDestructive({
    BinaryDataConverterDefault<BlockVersion>().BinaryDataFromData(Version()),
    BinaryDataConverterDefault<BlockIndex>().BinaryDataFromData(Index()),
    BinaryDataConverterDefault<BlockVersion>().BinaryDataFromData(Version()),
    BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(PreviousHash()),
    BinaryDataConverterDefault<BlockHash>().BinaryDataFromData(MerkleRoot()),
    BinaryDataConverterDefault<BlockTimeInterval>().BinaryDataFromData(TimeStamp()),
    BinaryDataConverterDefault<BlockNonce>().BinaryDataFromData(Nonce())
  });
}

template<typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockHeader<HashCalculatorT>::Hash() const
{
  return BinaryData{ hash_.begin(), hash_.end() };
}

template<typename HashCalculatorT>
inline ssybc::SizeT ssybc::BlockHeader<HashCalculatorT>::SizeOfBinary() const
{
  return
    sizeof(decltype(version_))
    + sizeof(decltype(index_))
    + HashCalculatorT().SizeOfHashInBytes() * 2
    + sizeof(decltype(time_stamp_))
    + sizeof(decltype(nonce_));
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
inline std::string ssybc::BlockHeader<HashCalculatorT>::Description() const
{
  return Description("");
}

template<typename HashCalculatorT>
inline std::string ssybc::BlockHeader<HashCalculatorT>::Description(std::string const & lead_padding) const
{
  std::string result{ lead_padding + "version: " };
  result += (lead_padding + util::ToString(Version()) + ",\n");
  result += (lead_padding + "index: ");
  result += (lead_padding + util::ToString(Index()) + ",\n");
  result += (lead_padding + "time_stamp: ");
  result += (lead_padding + util::ToString(TimeStamp()) + ",\n");
  result += (lead_padding + "nonce: ");
  result += (lead_padding + util::ToString(Nonce()) + ",\n");
  result += (lead_padding + "merkel_root: ");
  result += (lead_padding + util::HexStringFromBytes(MerkleRoot()) + ",\n");
  result += (lead_padding + "previous_hash: ");
  result += (lead_padding + util::HexStringFromBytes(PreviousHash()) + ",\n");
  result += (lead_padding + "hash: ");
  result += (lead_padding + util::HexStringFromBytes(Hash()) + "\n");
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



#endif  // SSYBC_SRC_BLOCK_BLOCK_HEADER_BLOCK_HEADER_IMPL_HPP_
