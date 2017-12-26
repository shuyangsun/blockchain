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


#ifndef SSYBC_SRC_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_IMPL_HPP_
#define SSYBC_SRC_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_IMPL_HPP_

#include "include/ssybc/validator/block_validator_less_hash.hpp"
#include "include/ssybc/utility/operator.hpp"
#include <limits>


template<typename BlockT, ssybc::HashDifficulty Difficulty>
inline ssybc::BlockValidatorLessHash<BlockT, Difficulty>::BlockValidatorLessHash():
  BlockValidator<BlockT, Difficulty>()
{
  auto const byte_max{ std::numeric_limits<Byte>::max() };
  auto max_hash = BlockHash(typename BlockT::HeaderHashCalculatorType().SizeOfHashInBytes());
  for (std::size_t i{ Difficulty }; i < max_hash.size(); ++i) {
    max_hash[i] = byte_max;
  }
  max_hash_ = max_hash;
}


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename BlockT, ssybc::HashDifficulty Difficulty>
inline bool ssybc::BlockValidatorLessHash<BlockT, Difficulty>::IsValidGenesisBlockHash(BlockHash const & hash) const
{
  return hash <= max_hash_;
}


template<typename BlockT, ssybc::HashDifficulty Difficulty>
inline bool ssybc::BlockValidatorLessHash<BlockT, Difficulty>::IsValidHashToAppend(
  BlockHash const & previous_hash,
  BlockHash const & hash) const
{
  return hash < previous_hash;
}


#endif  // SSYBC_SRC_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_IMPL_HPP_
