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

#ifndef SSYBC_INCLUDE_SSYBC_BLOCKCHAIN_BLOCKCHAIN_HPP_
#define SSYBC_INCLUDE_SSYBC_BLOCKCHAIN_BLOCKCHAIN_HPP_

#include "include/ssybc/general/general.hpp"
#include "include/ssybc/block/block.hpp"
#include "include/ssybc/validator/block_validator_less_hash.hpp"
#include "include/ssybc/miner/block_miner_cpu_brute_force.hpp"

#include <unordered_map>
#include <string>

namespace ssybc {

  template<typename BlockType, template<typename> class Validator = BlockValidatorLessHash>
  class Blockchain {
  public:


// -------------------------------------------------- Type Definition -------------------------------------------------

    using BlockContentType = typename BlockType::BlockContentType;
    using ContentBinaryConverterType = typename BlockType::ContentBinaryConverterType;
    using HashCalculatorType = typename BlockType::HashCalculatorType;
    using ValidatorType = Validator<BlockType>;
    using MinerType = BlockMiner<ValidatorType>;

// --------------------------------------------- Constructor & Destructor ---------------------------------------------

    Blockchain() = delete;
    Blockchain(BlockType const &genesis_block);
    Blockchain(BlockContentType const &content);
    Blockchain(BlockContentType const &content, MinerType const &miner);
    Blockchain(BinaryData const &binary_data);
    Blockchain(BinaryData &&binary_data);
    ~Blockchain();

// --------------------------------------------------- Public Method --------------------------------------------------

    SizeT Size() const;

    bool Append(BlockType const &block);
    bool Append(BlockContentType const &content);
    bool Append(BlockContentType const &content, MinerType const &miner);

    operator std::string() const;
    virtual std::string Description() const;

    BlockType operator[](long long const index) const;
    BlockType operator[](std::string const hash_string);
    bool operator==(Blockchain const &blockchain) const;
    bool operator!=(Blockchain const &blockchain) const;

    BlockType GenesisBlock() const;
    BlockType TailBlock() const;

    BinaryData ToBinary() const;

// -------------------------------------------------- Private Member --------------------------------------------------

  private:

    std::vector<BlockType> blocks_{};
    std::unordered_map<std::string, std::size_t> hash_to_index_dict_{};

    void PushBackBlock_(BlockType const &block);
    BlockType MinedGenesisWithContent_(BlockContentType const &content, MinerType const &miner) const;
    BlockMinerCPUBruteForce<ValidatorType> DefaultMiner_() const;
    BlockType BlockInitializedWithContent_(
      BlockContentType const &content,
      BlockIndex const index,
      BlockHash const &previous_hash) const;
  };


}  // namespace ssybc


#include "src/blockchain/blockchain_impl.hpp"


#endif  // SSYBC_INCLUDE_SSYBC_BLOCKCHAIN_BLOCKCHAIN_HPP_

