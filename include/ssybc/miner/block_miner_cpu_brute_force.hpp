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

#ifndef SSYBC_INCLUDE_SSYBC_MINER_BLOCK_MINER_CPU_BRUTE_FORCE_HPP_
#define SSYBC_INCLUDE_SSYBC_MINER_BLOCK_MINER_CPU_BRUTE_FORCE_HPP_

#include "include/ssybc/miner/block_miner.hpp"

namespace ssybc {

  template<typename Validator>
  class BlockMinerCPUBruteForce: public virtual BlockMiner<Validator> {
  public:

// --------------------------------------------------- Public Method --------------------------------------------------

    MinedResult MineGenesisInfo(BinaryData const &hashable_binary) const override;
    MinedResult MineInfo(BlockHash const &previous_hash, BinaryData const &hashable_binary) const override;
  };


}  // namespace ssybc


#include "src/miner/block_miner_cpu_brute_force_impl.hpp"


#endif  // SSYBC_INCLUDE_SSYBC_MINER_BLOCK_MINER_CPU_BRUTE_FORCE_HPP_

