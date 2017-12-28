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
#include "include/ssybc/logging/logging.hpp"

#include <exception>
#include <typeinfo>
#include <limits>
#include <thread>
#include <mutex>
#include <condition_variable>


// ----------------------------------------------------- Helper -------------------------------------------------------

namespace ssybc {

  template<typename ValidatorT, typename HashCalculatorT>
  void MineGenesisInfoOnCPUThreadBruteForce_(
    BinaryData const & hashable_binary,
    BlockTimeInterval const time_stamp,
    BlockNonce const nonce_start,
    BlockNonce const nonce_end,
    ValidatorT const validator,
    HashCalculatorT const hash_calculator);

  template<typename ValidatorT, typename HashCalculatorT>
  void MineInfoOnCPUThreadBruteForce_(
    BinaryData const & previous_hash,
    BinaryData const & hashable_binary,
    BlockTimeInterval const time_stamp,
    BlockNonce const nonce_start,
    BlockNonce const nonce_end,
    ValidatorT const validator,
    HashCalculatorT const hash_calculator);

  static std::mutex block_mining_mtx_;
  static std::condition_variable block_mined_cv_;
  static bool is_block_mined_{ false };
  static MinedResult block_result_{};

  void LogThreadMiningNonceInRange_(BlockNonce const start, BlockNonce const stop);
  void LogThreadMiningNonceInRangeTerminatedWithoutValidResult_(BlockNonce const start, BlockNonce const stop);
  void LogThreadMiningNonceInRangeTerminatedWithValidResult_(
    BlockNonce const start,
    BlockNonce const stop,
    BlockNonce const result);
}


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename Validator>
inline auto ssybc::BlockMinerCPUBruteForce<Validator>::MineGenesisInfo(
  BinaryData const & hashable_binary) const -> MinedResult
{
  logging::info << "Mining Genesis block variables..." << std::endl;
  auto const validator = Validator();
  using HashCalculatorType = typename BlockMinerCPUBruteForce::HashCalculatorType;
  auto const hash_calculator = HashCalculatorType();
  BlockTimeInterval result_ts{ util::TrailingTimeStampBeforeNonceFromBinaryData(hashable_binary) };
  if (validator.IsValidGenesisBlockHash(hash_calculator.Hash(hashable_binary))) {
    logging::info << "Finished mining Genesis block variables." << std::endl;
    return { result_ts, util::TrailingNonceFromBinaryData(hashable_binary) };
  }

  auto const hardware_threads_count = std::thread::hardware_concurrency();
  auto thread_count = std::max<decltype(hardware_threads_count)>(1, hardware_threads_count);
  auto const max_nonce = std::numeric_limits<BlockNonce>::max();
  auto nonce_threads_gap = static_cast<BlockNonce>(max_nonce / thread_count);
  if (nonce_threads_gap * thread_count != max_nonce) {
    nonce_threads_gap = static_cast<BlockNonce>(max_nonce / (thread_count - 1));
  }
  logging::info << "Creating " + util::ToString(thread_count) + " threads for genesis block mining..." << std::endl;
  std::vector<std::thread> worker_threads{};
  for (decltype(thread_count) i{ 0 }; i < thread_count; ++i) {
    worker_threads.push_back(std::thread(
    MineGenesisInfoOnCPUThreadBruteForce_<Validator, HashCalculatorType>,
    hashable_binary,
    result_ts,
    static_cast<BlockNonce>(i * nonce_threads_gap),
    std::min(static_cast<BlockNonce>((i + 1) * nonce_threads_gap), max_nonce),
    validator,
    hash_calculator
    ));
  }

  std::unique_lock<std::mutex> lock(block_mining_mtx_);
  block_mined_cv_.wait(lock, [] { return is_block_mined_;  });
  for (auto &worker : worker_threads) {
    worker.join();
  }
  logging::info << "Joined " + util::ToString(thread_count) + " threads for genesis block mining." << std::endl;

  auto const result = MinedResult{ block_result_ };
  block_result_ = MinedResult();
  is_block_mined_ = false;
  logging::info << "Finished mining Genesis block variables." << std::endl;
  return result;
}


template<typename Validator>
inline auto ssybc::BlockMinerCPUBruteForce<Validator>::MineInfo(
  BlockHash const & previous_hash,
  BinaryData const & hashable_binary) const -> MinedResult
{
  logging::info << "Mining block variables..." << std::endl;
  auto const validator = Validator();
  using HashCalculatorType = typename BlockMinerCPUBruteForce::HashCalculatorType;
  auto const hash_calculator = HashCalculatorType();
  BlockTimeInterval result_ts{ util::TrailingTimeStampBeforeNonceFromBinaryData(hashable_binary) };
  if (validator.IsValidHashToAppend(previous_hash, hash_calculator.Hash(hashable_binary))) {
    logging::info << "Finished mining block variables." << std::endl;
    return { result_ts, util::TrailingNonceFromBinaryData(hashable_binary) };
  }

  auto const hardware_threads_count = std::thread::hardware_concurrency();
  auto thread_count = std::max<decltype(hardware_threads_count)>(1, hardware_threads_count);
  auto const max_nonce = std::numeric_limits<BlockNonce>::max();
  auto nonce_threads_gap = static_cast<BlockNonce>(max_nonce / thread_count);
  if (nonce_threads_gap * thread_count != max_nonce) {
    nonce_threads_gap = static_cast<BlockNonce>(max_nonce / (thread_count - 1));
  }
  std::vector<std::thread> worker_threads{};
  logging::info << "Creating " + util::ToString(thread_count) + " threads for block mining..." << std::endl;
  for (decltype(thread_count) i{ 0 }; i < thread_count; ++i) {
    worker_threads.push_back(std::thread(
      MineInfoOnCPUThreadBruteForce_<Validator, HashCalculatorType>,
      previous_hash,
      hashable_binary,
      result_ts,
      static_cast<BlockNonce>(i * nonce_threads_gap),
      std::min(static_cast<BlockNonce>((i + 1) * nonce_threads_gap), max_nonce),
      validator,
      hash_calculator
    ));
  }

  std::unique_lock<std::mutex> lock(block_mining_mtx_);
  block_mined_cv_.wait(lock, [] { return is_block_mined_;  });
  for (auto &worker : worker_threads) {
    worker.join();
  }
  logging::info << "Joined " + util::ToString(thread_count) + " threads for block mining." << std::endl;

  auto const result = MinedResult{ block_result_ };
  block_result_ = MinedResult();
  is_block_mined_ = false;
  logging::info << "Finished mining block variables." << std::endl;
  return result;
}


// ----------------------------------------------------- Helper -------------------------------------------------------


template<typename ValidatorT, typename HashCalculatorT>
void ssybc::MineGenesisInfoOnCPUThreadBruteForce_(
  BinaryData const & hashable_binary,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce_start,
  BlockNonce const nonce_end,
  ValidatorT const validator,
  HashCalculatorT const hash_calculator)
{
  LogThreadMiningNonceInRange_(nonce_start, nonce_end);
  BlockNonce result_nonce{ nonce_start };
  BlockTimeInterval ts{ time_stamp };
  auto binary_mutable_copy = BinaryData(hashable_binary.begin(), hashable_binary.end());
  while (!is_block_mined_ && !validator.IsValidGenesisBlockHash(hash_calculator.Hash(binary_mutable_copy))) {
    if (result_nonce >= nonce_end) {
      ts = util::UTCTime();
      util::UpdateBinaryDataWithTrailingTimeStampBeforeNonce(binary_mutable_copy, ts);
      result_nonce = 0;
    } else {
      ++result_nonce;
    }
    
    util::UpdateBinaryDataWithTrailingNonce(binary_mutable_copy, result_nonce);
  }

  if (is_block_mined_) {
    LogThreadMiningNonceInRangeTerminatedWithoutValidResult_(nonce_start, nonce_end);
  } else {
    block_result_ = MinedResult{ ts, result_nonce };
    is_block_mined_ = true;
    LogThreadMiningNonceInRangeTerminatedWithValidResult_(nonce_start, nonce_end, result_nonce);
    block_mined_cv_.notify_all();
  }
}

template<typename ValidatorT, typename HashCalculatorT>
void ssybc::MineInfoOnCPUThreadBruteForce_(
  BinaryData const & previous_hash,
  BinaryData const & hashable_binary,
  BlockTimeInterval const time_stamp,
  BlockNonce const nonce_start,
  BlockNonce const nonce_end,
  ValidatorT const validator,
  HashCalculatorT const hash_calculator)
{
  LogThreadMiningNonceInRange_(nonce_start, nonce_end);
  BlockNonce result_nonce{ nonce_start };
  BlockTimeInterval ts{ time_stamp };
  auto binary_mutable_copy = BinaryData(hashable_binary.begin(), hashable_binary.end());
  while (!is_block_mined_ && !validator.IsValidHashToAppend(
      previous_hash,
      hash_calculator.Hash(binary_mutable_copy))) {
    if (result_nonce >= nonce_end) {
      ts = util::UTCTime();
      util::UpdateBinaryDataWithTrailingTimeStampBeforeNonce(binary_mutable_copy, ts);
      result_nonce = 0;
    }
    else {
      ++result_nonce;
    }

    util::UpdateBinaryDataWithTrailingNonce(binary_mutable_copy, result_nonce);
  }

  if (is_block_mined_) {
    LogThreadMiningNonceInRangeTerminatedWithoutValidResult_(nonce_start, nonce_end);
  } else {
    block_result_ = MinedResult{ ts, result_nonce };
    is_block_mined_ = true;
    LogThreadMiningNonceInRangeTerminatedWithValidResult_(nonce_start, nonce_end, result_nonce);
    block_mined_cv_.notify_all();
  }
}


inline void ssybc::LogThreadMiningNonceInRange_(BlockNonce const start, BlockNonce const stop)
{
  logging::threading << "Thread mining nonce in range ["
    + util::ToString(start)
    + ", "
    + util::ToString(stop)
    + ")..." << std::endl;
}


inline void ssybc::LogThreadMiningNonceInRangeTerminatedWithoutValidResult_(
  BlockNonce const start,
  BlockNonce const stop)
{
  logging::threading << "Thread mining nonce in range ["
    + util::ToString(start)
    + ", "
    + util::ToString(stop)
    + ") terminated without valid result." << std::endl;
}


inline void ssybc::LogThreadMiningNonceInRangeTerminatedWithValidResult_(
  BlockNonce const start,
  BlockNonce const stop,
  BlockNonce const result)
{
  logging::threading << "Thread mining nonce in range ["
    + util::ToString(start)
    + ", "
    + util::ToString(stop)
    + ") terminated with valid result: "
    + util::ToString(result)
    + "." << std::endl;
}


#endif  // SSYBC_SRC_MINER_BLOCK_MINER_CPU_BRUTE_FORCE_IMPL_HPP_
