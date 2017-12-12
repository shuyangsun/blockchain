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


template<typename BlockType, template<typename> class Validator>
ssybc::Blockchain<BlockType, Validator>::Blockchain(BlockType const & genesis_block)
{
  if (!ValidatorType().IsValidGenesisBlock(genesis_block)) {
    throw std::logic_error("Cannot construct Blockchain with invalid Genesis Block.");
  }
  PushBackBlock_(genesis_block);
}


template<typename BlockType, template<typename> class Validator>
ssybc::Blockchain<BlockType, Validator>::Blockchain(BlockContentType const & content):
  Blockchain(content, DefaultMiner_())
{ EMPTY_BLOCK }


template<typename BlockType, template<typename> class Validator>
ssybc::Blockchain<BlockType, Validator>::Blockchain(BlockContentType const & content, MinerType const & miner):
  Blockchain(MinedGenesisWithContent_(content, miner))
{ EMPTY_BLOCK }


template<typename BlockType, template<typename> class Validator>
ssybc::Blockchain<BlockType, Validator>::Blockchain(BinaryData const &binary_data):
  Blockchain(std::move(BinaryData(binary_data.begin(), binary_data.end())))
{ EMPTY_BLOCK }


template<typename BlockType, template<typename> class Validator>
ssybc::Blockchain<BlockType, Validator>::Blockchain(BinaryData &&binary_data)
{
  auto converter = BinaryDataConverterDefault<SizeT>();
  std::vector<BlockType> blocks{};
  while (binary_data.size() > 0) {
    SizeT const size_of_block_binary{ converter.DataFromBinaryData(binary_data) };
    auto block_begin_iter = binary_data.begin();
    auto block_end_iter = binary_data.begin();
    std::advance(block_end_iter, static_cast<std::size_t>(size_of_block_binary));
    blocks.push_back(BlockType(binary_data));
    binary_data.erase(block_begin_iter, block_end_iter);
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


template<typename BlockType, template<typename> class Validator>
ssybc::Blockchain<BlockType, Validator>::~Blockchain()
{ EMPTY_BLOCK }


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename BlockType, template<typename> class Validator>
inline auto ssybc::Blockchain<BlockType, Validator>::Size() const -> SizeT
{
  return static_cast<SizeT>(blocks_.size());
}


template<typename BlockType, template<typename> class Validator>
inline bool ssybc::Blockchain<BlockType, Validator>::Append(BlockType const & block)
{
  if (ValidatorType().IsValidToAppend(TailBlock(), block)) {
    PushBackBlock_(block);
    return true;
  }
  return false;
}


template<typename BlockType, template<typename> class Validator>
inline bool ssybc::Blockchain<BlockType, Validator>::Append(BlockContentType const & content)
{
  return Append(content, DefaultMiner_());
}


template<typename BlockType, template<typename> class Validator>
inline bool ssybc::Blockchain<BlockType, Validator>::Append(
  BlockContentType const & content,
  MinerType const &miner)
{
  auto const tail_block = TailBlock();
  auto const next_block_init = BlockInitializedWithContent_(content, blocks_.size(), tail_block.Hash());
  auto const block = miner.Mine(tail_block, next_block_init);
  return Append(block);
}


template<typename BlockType, template<typename> class Validator>
inline BlockType ssybc::Blockchain<BlockType, Validator>::GenesisBlock() const
{
  return BlockType(blocks_.front());
}


template<typename BlockType, template<typename> class Validator>
inline BlockType ssybc::Blockchain<BlockType, Validator>::TailBlock() const
{
  return BlockType(blocks_.back());
}


template<typename BlockType, template<typename> class Validator>
inline BlockType ssybc::Blockchain<BlockType, Validator>::operator[](long long const index) const
{
  long long real_index = index;
  if (index < 0) {
    real_index = blocks_.size() + index;
  }
  return BlockType(blocks_[static_cast<std::size_t>(real_index)]);
}


template<typename BlockType, template<typename> class Validator>
inline BlockType ssybc::Blockchain<BlockType, Validator>::operator[](std::string const hash_string)
{
  std::size_t index = hash_to_index_dict_[hash_string];
  return (*this)[index];
}


template<typename BlockType, template<typename> class Validator>
inline bool ssybc::Blockchain<BlockType, Validator>::operator==(Blockchain const & blockchain) const
{
  if (Size() != blockchain.Size()) { return false; }
  for (std::size_t i{ 0 }; i < Size(); ++i) {
    if ((*this)[i] != blockchain[i]) {
      return false;
    }
  }
  return true;
}


template<typename BlockType, template<typename> class Validator>
inline bool ssybc::Blockchain<BlockType, Validator>::operator!=(Blockchain const & blockchain) const
{
  return !((*this) == blockchain);
}


template<typename BlockType, template<typename> class Validator>
inline std::string ssybc::Blockchain<BlockType, Validator>::Description() const
{
  return util::Join<BlockType>(blocks_, ",\n", [&](BlockType block) { return block.Description();  });
}


template<typename BlockType, template<typename> class Validator>
ssybc::Blockchain<BlockType, Validator>::operator std::string() const
{
  return Description();
}


template<typename BlockType, template<typename> class Validator>
inline auto ssybc::Blockchain<BlockType, Validator>::ToBinary() const -> BinaryData
{
  std::vector<BinaryData> result{};
  for (auto const &block : blocks_) {
    result.push_back(block.ToBinaryBlock());
  }
  return util::ConcatenateMoveDestructive(result);
}


// -------------------------------------------------- Private Member --------------------------------------------------


template<typename BlockType, template<typename> class Validator>
inline void ssybc::Blockchain<BlockType, Validator>::PushBackBlock_(BlockType const & block)
{
  blocks_.push_back(block);
  hash_to_index_dict_[block.HashAsString()] = static_cast<std::size_t>(block.Index());
}


template<typename BlockType, template<typename> class Validator>
BlockType ssybc::Blockchain<
  BlockType,
  Validator>::MinedGenesisWithContent_(BlockContentType const & content, MinerType const &miner) const
{
  auto genesis_init = BlockInitializedWithContent_(content, 0, HashCalculatorType().GenesisBlockPreviousHash());
  return miner.MineGenesis(genesis_init);
}


template<typename BlockType, template<typename> class Validator>
inline auto ssybc::Blockchain<BlockType, Validator>::DefaultMiner_() const -> BlockMinerCPUBruteForce<ValidatorType>
{
  return BlockMinerCPUBruteForce<ValidatorType>();
}


template<typename BlockType, template<typename> class Validator>
inline BlockType ssybc::Blockchain<
  BlockType,
  Validator>::BlockInitializedWithContent_(
    BlockContentType const & content,
    BlockIndex const index,
    BlockHash const &previous_hash) const
{
  BlockType result {
    index,
    util::UTCTime(),
    previous_hash,
    kDefaultNonce,
    content
  };
  return result;
}


#endif  // SSYBC_SRC_BLOCKCHAIN_BLOCKCHAIN_IMPL_HPP_

