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


#ifndef BLOCKCHAIN_SRC_MINER_BLOCK_MINER_IMPL_HPP_
#define BLOCKCHAIN_SRC_MINER_BLOCK_MINER_IMPL_HPP_

#include "include/miner/block_miner.hpp"

#include <exception>
#include <typeinfo>


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename Validator>
inline auto ssybc::BlockMiner<Validator>::MineGenesis(BlockType const & block) const -> BlockType
{
  if (block.Index() != 0) {
    std::string const message{ 
      "Cannot mine Genesis Block, index is "
      + std::to_string(block.Index())
      + " instead of 0."
    };
    throw std::invalid_argument(message);
  }
  if (block.PreviousBlockHash() != HashCalculatorType().GenesisBlockPreviousHash()) {
    throw std::invalid_argument(
      "Cannot mine Genesis Block, previous hash does not match value provided by hash calculator."
    );
  }
  auto const hashable_binary = block.HashableBinaryData();
  auto const result_nonce = MineGenesisNonce(hashable_binary);
  auto result = block.BlockWithDifferentNonce(result_nonce);
  if (!Validator().IsValidGenesisBlock(result)) {
    throw std::logic_error(
      "Cannot mine Genesis Block, mined result does not pass validator, "
      "check implementation of \"MineGenesisNonce\" method in \"" + std::string(typeid(*this).name()) + "\"."
    );
  }
  return result;
}


template<typename Validator>
inline auto ssybc::BlockMiner<Validator>::Mine(
  BlockType const & previous_block,
  BlockType const & block) const -> BlockType
{
  if (block.PreviousBlockHash() != previous_block.Hash()) {
    throw std::invalid_argument(
      "Cannot mine Block " + std::to_string(block.Index()) + ", it is not post-adjacent "
      "block with Block " + std::to_string(previous_block.Index()) + "."
    );
  }
  auto const hashable_binary = block.HashableBinaryData();
  auto const result_nonce = MineNonce(previous_block.Hash(), hashable_binary);
  auto const result = block.BlockWithDifferentNonce(result_nonce);
  if (!Validator().IsValidToAppend(previous_block, result)) {
    throw std::logic_error(
      "Cannot mine Genesis Block, mined result does not pass validator, "
      "check implementation of \"MineGenesisNonce\" method in \"" + std::string(typeid(*this).name()) + "\"."
    );
  }
  return result;
}


#endif  // BLOCKCHAIN_SRC_MINER_BLOCK_MINER_IMPL_HPP_
