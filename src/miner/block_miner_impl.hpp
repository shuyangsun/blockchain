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


#ifndef SSYBC_SRC_MINER_BLOCK_MINER_IMPL_HPP_
#define SSYBC_SRC_MINER_BLOCK_MINER_IMPL_HPP_

#include "include/ssybc/miner/block_miner.hpp"

#include <exception>
#include <typeinfo>


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename Validator>
inline auto ssybc::BlockMiner<Validator>::MineGenesis(BlockType const & block) const -> BlockType
{
  if (block.Header().Index() != 0) {
    std::string const message{ 
      "Cannot mine Genesis Block, index is "
      + std::to_string(block.Header().Index())
      + " instead of 0."
    };
    throw std::invalid_argument(message);
  }
  if (block.Header().PreviousHash() != HashCalculatorType().GenesisBlockPreviousHash()) {
    throw std::invalid_argument(
      "Cannot mine Genesis Block, previous hash does not match value provided by hash calculator."
    );
  }
  auto const hashable_binary = block.Header().Binary();
  auto const mined_result = MineGenesisInfo(hashable_binary);
  auto const old_header = block.Header();
  typename BlockType::BlockHeaderType result_header{
    old_header.Version(),
    old_header.Index(),
    old_header.MerkleRoot(),
    old_header.PreviousHash(),
    mined_result.time_stamp,
    mined_result.nonce};
  
  if (!Validator().IsValidGenesisBlock(BlockType(result_header))) {
    throw std::logic_error(
      "Cannot mine Genesis Block, mined result does not pass validator, "
      "check implementation of \"MineGenesisNonce\" method in \"" + std::string(typeid(*this).name()) + "\"."
    );
  }

  if (block.IsHeaderOnly()) {
    return BlockType{ result_header };
  }
  return BlockType{ result_header, block.Content() };
}


template<typename Validator>
inline auto ssybc::BlockMiner<Validator>::Mine(
  BlockType const & previous_block,
  BlockType const & block) const -> BlockType
{
  if (block.Header().PreviousHash() != previous_block.Header().Hash()) {
    throw std::invalid_argument(
      "Cannot mine Block " + std::to_string(block.Header().Index()) + ", it is not post-adjacent "
      "block with Block " + std::to_string(previous_block.Header().Index()) + "."
    );
  }
  auto const header_hash = block.Header().Binary();
  auto const mined_result = MineInfo(previous_block.Header().Hash(), header_hash);
  auto const old_header = block.Header();
  typename BlockType::BlockHeaderType result_header{
    old_header.Version(),
    old_header.Index(),
    old_header.MerkleRoot(),
    old_header.PreviousHash(),
    mined_result.time_stamp,
    mined_result.nonce };

  if (!Validator().IsValidToAppend(previous_block, BlockType{ result_header })) {
    throw std::logic_error(
      "Cannot mine Block, mined result does not pass validator, "
      "check implementation of \"MineNonce\" method in \"" + std::string(typeid(*this).name()) + "\"."
    );
  }

  if (block.IsHeaderOnly()) {
    return BlockType{ result_header };
  }
  return BlockType{ result_header, block.Content() };
}


#endif  // SSYBC_SRC_MINER_BLOCK_MINER_IMPL_HPP_
