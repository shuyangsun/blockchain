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


#ifndef SSYBC_SRC_MINER_BLOCK_MINER_CPU_BRUTE_FORCE_IMPL_HPP_
#define SSYBC_SRC_MINER_BLOCK_MINER_CPU_BRUTE_FORCE_IMPL_HPP_

#include "include/ssybc/miner/block_miner_cpu_brute_force.hpp"
#include "include/ssybc/validator/block_validator.hpp"
#include "include/ssybc/utility/utility.hpp"

#include <exception>
#include <typeinfo>
#include <limits>


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename Validator>
inline auto ssybc::BlockMinerCPUBruteForce<Validator>::MineGenesisInfo(
  BinaryData const & hashable_binary) const -> MinedResult
{
  auto const validator = Validator();
  auto const hash_calculator = BlockMinerCPUBruteForce::HashCalculatorType();
  BlockTimeInterval result_ts{ util::TrailingTimeStampBeforeNonceFromBinaryData(hashable_binary) };
  if (validator.IsValidGenesisBlockHash(hash_calculator.Hash(hashable_binary))) {
    return { result_ts, util::TrailingNonceFromBinaryData(hashable_binary) };
  }
  BlockNonce result_nonce{};
  BlockNonce const nonce_max_limit{ std::numeric_limits<BlockNonce>::max() };
  auto binary_mutable_copy = BinaryData(hashable_binary.begin(), hashable_binary.end());
  while (!validator.IsValidGenesisBlockHash(hash_calculator.Hash(binary_mutable_copy))) {
    if (result_nonce >= nonce_max_limit) {
      result_nonce = 0;
      ++result_ts;
      util::UpdateBinaryDataWithTrailingTimeStampBeforeNonce(binary_mutable_copy, result_ts);
    } else {
      ++result_nonce;
    }
    util::UpdateBinaryDataWithTrailingNonce(binary_mutable_copy, result_nonce);
  }
  return { result_ts, result_nonce };
}


template<typename Validator>
inline auto ssybc::BlockMinerCPUBruteForce<Validator>::MineInfo(
  BlockHash const & previous_hash,
  BinaryData const & hashable_binary) const -> MinedResult
{
  auto const validator = Validator();
  auto const hash_calculator = BlockMinerCPUBruteForce::HashCalculatorType();
  BlockTimeInterval result_ts{ util::TrailingTimeStampBeforeNonceFromBinaryData(hashable_binary) };
  if (validator.IsValidHashToAppend(previous_hash, hash_calculator.Hash(hashable_binary))) {
    return { result_ts, util::TrailingNonceFromBinaryData(hashable_binary) };
  }
  BlockNonce result_nonce{};
  BlockNonce const nonce_max_limit{ std::numeric_limits<BlockNonce>::max() };
  auto binary_mutable_copy = BinaryData(hashable_binary.begin(), hashable_binary.end());
  while (!validator.IsValidHashToAppend(previous_hash, hash_calculator.Hash(binary_mutable_copy))) {
    if (result_nonce >= nonce_max_limit) {
      result_nonce = 0;
      ++result_ts;
      util::UpdateBinaryDataWithTrailingTimeStampBeforeNonce(binary_mutable_copy, result_ts);
    } else {
      ++result_nonce;
    }
    util::UpdateBinaryDataWithTrailingNonce(binary_mutable_copy, result_nonce);
  }
  return { result_ts, result_nonce };
}


#endif  // SSYBC_SRC_MINER_BLOCK_MINER_CPU_BRUTE_FORCE_IMPL_HPP_
