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


#ifndef SSYBC_SRC_BLOCKCHAIN_BLOCKCHAIN_IMPL_HPP_
#define SSYBC_SRC_BLOCKCHAIN_BLOCKCHAIN_IMPL_HPP_


#include "include/ssybc/blockchain/blockchain.hpp"
#include "include/ssybc/utility/utility.hpp"
#include "include/ssybc/binary_data_converter/binary_data_converter_default.hpp"

#include <exception>
#include <iterator>
#include <algorithm>


// --------------------------------------------- Constructor & Destructor ---------------------------------------------


template<typename BlockT, template<typename> class ValidatorTemplate>
ssybc::Blockchain<BlockT, ValidatorTemplate>::Blockchain(BlockType const & genesis_block)
{
  if (!ValidatorType().IsValidGenesisBlock(genesis_block)) {
    throw std::logic_error("Cannot construct Blockchain with invalid Genesis Block.");
  }
  PushBackBlock_(genesis_block);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
ssybc::Blockchain<BlockT, ValidatorTemplate>::Blockchain(BinaryData const &binary_data):
  Blockchain(BinaryData(binary_data.begin(), binary_data.end()))
{ EMPTY_BLOCK }


template<typename BlockT, template<typename> class ValidatorTemplate>
ssybc::Blockchain<BlockT, ValidatorTemplate>::Blockchain(BinaryData &&binary_data)
{
  auto converter = BinaryDataConverterDefault<SizeT>();
  std::vector<BlockType> blocks{};
  while (binary_data.size() > 0) {
    auto data_size_begin_iter = binary_data.begin();
    std::advance(data_size_begin_iter, BlockType::BlockHeaderType::SizeOfBinary());
    auto data_size_end_iter = data_size_begin_iter;
    std::advance(data_size_end_iter, sizeof(SizeT));
    BinaryData data_size_binary{ data_size_begin_iter, data_size_end_iter };
    auto const data_size = converter.DataFromBinaryData(data_size_binary);
    auto block_end_iter = data_size_end_iter;
    std::advance(block_end_iter, data_size);

    auto block_binary_copy = BinaryData{ binary_data.begin(), block_end_iter };
    blocks.push_back(BlockType(std::move(block_binary_copy)));
    binary_data.erase(binary_data.begin(), block_end_iter);
  }
  if (!ValidatorType().IsValidGenesisBlock(blocks.front())) {
    throw std::logic_error("Cannot construct Blockchain with invalid Genesis Block.");
  }
  PushBackBlock_(blocks.front());
  auto cur_iter = blocks.begin();
  std::advance(cur_iter, 1);
  while (cur_iter != blocks.end()) {
    bool const append_succeed{ Append(*cur_iter) };
    if (!append_succeed) {
      throw std::logic_error(
        "Cannot construct Blockchain from binary data."
      );
    }
    std::advance(cur_iter, 1);
  }
}


template<typename BlockT, template<typename> class ValidatorTemplate>
ssybc::Blockchain<BlockT, ValidatorTemplate>::~Blockchain()
{ EMPTY_BLOCK }


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename BlockT, template<typename> class ValidatorTemplate>
inline auto ssybc::Blockchain<BlockT, ValidatorTemplate>::Size() const -> SizeT
{
  return static_cast<SizeT>(blocks_.size());
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline bool ssybc::Blockchain<BlockT, ValidatorTemplate>::Append(BlockType const & block)
{
  if (ValidatorType().IsValidToAppend(TailBlock(), block)) {
    PushBackBlock_(block);
    return true;
  }
  return false;
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline auto ssybc::Blockchain<BlockT, ValidatorTemplate>::BlockchainHeadersOnly() const -> Blockchain
{
  Blockchain result{ BlockT{ GenesisBlock().Header() } };
  for (size_t i{ 1 }; i < blocks_.size(); ++i) {
    result.Append(BlockT(blocks_[i].Header()));
  }
  return result;
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline bool ssybc::Blockchain<BlockT, ValidatorTemplate>::Append(BlockDataType const & data)
{
  return Append(data, DefaultMiner_());
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline bool ssybc::Blockchain<BlockT, ValidatorTemplate>::Append(
  BlockDataType const & data,
  MinerType const &miner)
{
  auto const tail_block = TailBlock();
  auto const next_block_init = BlockInitializedWithData_(
    data,
    tail_block.Header().Version(),
    blocks_.size(),
    tail_block.Header().Hash());
  auto block = miner.Mine(tail_block, next_block_init);
  return Append(block);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline BlockT ssybc::Blockchain<BlockT, ValidatorTemplate>::GenesisBlock() const
{
  return BlockType(blocks_.front());
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline BlockT ssybc::Blockchain<BlockT, ValidatorTemplate>::TailBlock() const
{
  return BlockType(blocks_.back());
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline BlockT ssybc::Blockchain<BlockT, ValidatorTemplate>::operator[](long long const index) const
{
  long long real_index = index;
  if (index < 0) {
    real_index = blocks_.size() + index;
  }
  return BlockType(blocks_[static_cast<std::size_t>(real_index)]);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline BlockT ssybc::Blockchain<BlockT, ValidatorTemplate>::operator[](std::string const &hash_string)
{
  std::size_t index = hash_to_index_dict_[hash_string];
  return (*this)[index];
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline BlockT ssybc::Blockchain<BlockT, ValidatorTemplate>::operator[](BinaryData const &hash)
{
  auto hash_string = util::HexStringFromBytes(hash);
  return (*this)[hash_string];
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline bool ssybc::Blockchain<BlockT, ValidatorTemplate>::operator==(Blockchain const & blockchain) const
{
  if (Size() != blockchain.Size()) { return false; }
  for (std::size_t i{ 0 }; i < Size(); ++i) {
    if ((*this)[i] != blockchain[i]) {
      return false;
    }
  }
  return true;
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline bool ssybc::Blockchain<BlockT, ValidatorTemplate>::operator!=(Blockchain const & blockchain) const
{
  return !((*this) == blockchain);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline std::string ssybc::Blockchain<BlockT, ValidatorTemplate>::Description() const
{
  auto result = util::Join<BlockType>(blocks_, ",\n", [&](BlockType block) { return block.Description();  });
  return "[" + result + "]";
}


template<typename BlockT, template<typename> class ValidatorTemplate>
ssybc::Blockchain<BlockT, ValidatorTemplate>::operator std::string() const
{
  return Description();
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline auto ssybc::Blockchain<BlockT, ValidatorTemplate>::Binary() const -> BinaryData
{
  std::vector<BinaryData> result{};
  for (auto const &block : blocks_) {
    result.push_back(block.Binary());
  }
  return util::ConcatenateMoveDestructive(result);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline auto ssybc::Blockchain<BlockT, ValidatorTemplate>::BinaryHeadersOnly() const -> BinaryData
{
  return BlockchainHeadersOnly().Binary();
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline bool ssybc::Blockchain<BlockT, ValidatorTemplate>::SaveBinaryToFileAtPath(std::string const & file_path)
{
  return util::WriteBinaryDataToFileAtPath(Binary(), file_path);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline bool ssybc::Blockchain<
  BlockT,
  ValidatorTemplate>::SaveHeadersOnlyBinaryToFileAtPath(std::string const & file_path)
{
  return util::WriteBinaryDataToFileAtPath(BinaryHeadersOnly(), file_path);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline auto ssybc::Blockchain<
  BlockT,
  ValidatorTemplate>::LoadFromBinaryFileAtPath(std::string const & file_path) -> Blockchain
{
  return Blockchain{ util::ReadBinaryDataFromFileAtPath(file_path) };
}


// -------------------------------------------------- Private Member --------------------------------------------------


template<typename BlockT, template<typename> class ValidatorTemplate>
inline void ssybc::Blockchain<BlockT, ValidatorTemplate>::PushBackBlock_(BlockType const & block)
{
  blocks_.push_back(block);
  hash_to_index_dict_[block.Header().HashAsString()] = static_cast<std::size_t>(block.Header().Index());
}


template<typename BlockT, template<typename> class ValidatorTemplate>
BlockT ssybc::Blockchain<
  BlockT,
  ValidatorTemplate>::GenesisBlockMinedWithData(BlockDataType const & data)
{
  auto genesis_init = BlockInitializedWithData_(data, 0, 0, HeaderHashCalculatorType().GenesisBlockPreviousHash());
  return Blockchain::DefaultMiner_().MineGenesis(genesis_init);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
BlockT ssybc::Blockchain<
  BlockT,
  ValidatorTemplate>::GenesisBlockMinedWithData(BlockDataType const & data, MinerType const &miner)
{
  auto genesis_init = BlockInitializedWithData_(data, 0, 0, HeaderHashCalculatorType().GenesisBlockPreviousHash());
  return miner.MineGenesis(genesis_init);
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline auto ssybc::Blockchain<BlockT, ValidatorTemplate>::DefaultMiner_() -> BlockMinerCPUBruteForce<ValidatorType>
{
  return BlockMinerCPUBruteForce<ValidatorType>();
}


template<typename BlockT, template<typename> class ValidatorTemplate>
inline BlockT ssybc::Blockchain<
  BlockT,
  ValidatorTemplate>::BlockInitializedWithData_(
    BlockDataType const & data,
    BlockVersion const version,
    BlockIndex const index,
    BlockHash const &previous_hash)
{
  BlockType result {
    version,
    index,
    previous_hash,
    util::UTCTime(),
    kDefaultNonce,
    data
  };
  return result;
}


#endif  // SSYBC_SRC_BLOCKCHAIN_BLOCKCHAIN_IMPL_HPP_

