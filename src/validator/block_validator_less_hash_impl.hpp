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


#ifndef BLOCKCHAIN_INCLUDE_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_IMPL_HPP_
#define BLOCKCHAIN_INCLUDE_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_IMPL_HPP_

#include "include/validator/block_validator_less_hash.hpp"
#include "include/utility/operator.hpp"
#include <limits>


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename BlockT>
bool ssybc::BlockValidatorLessHash<BlockT>::IsValidGenesisBlock(BlockT const &block) const
{
  auto const byte_max{ std::numeric_limits<Byte>::max() };
  auto max_hash = BlockHash(BlockType::HashCalculatorType().SizeOfHashInBytes());
  unsigned short const genesis_difficulty_level{2};
  for (std::size_t i{ 0 }; i < max_hash.size(); ++i) {
    max_hash[i] = (i < genesis_difficulty_level) ? 0 : byte_max;
  }
  return block.Hash() <= max_hash;
}


template<typename BlockT>
inline bool ssybc::BlockValidatorLessHash<BlockT>::IsValidToAppend(BlockT const & previous_block, BlockT const & block) const
{
  return block.Hash() < previous_block.Hash();
}


#endif  // BLOCKCHAIN_INCLUDE_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_IMPL_HPP_
