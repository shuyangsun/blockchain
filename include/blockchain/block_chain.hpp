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

#ifndef BLOCKCHAIN_INCLUDE_BLOCKCHAIN_BLOCKCHAIN_HPP_
#define BLOCKCHAIN_INCLUDE_BLOCKCHAIN_BLOCKCHAIN_HPP_

#include "include/general.hpp"
#include "include/miner/block_miner.hpp"

#include <unordered_map>
#include <string>

namespace ssybc {

  template<typename Block, typename Validator>
  class BlockChain {
  public:


// -------------------------------------------------- Type Definition -------------------------------------------------

    using BlockType = typename Block;
    using BlockContentType = typename Block::BlockContent;
    using ContentBinaryConverterType = typename Block::ContentBinaryConverterType;
    using HashCalculatorType = typename Block::HashCalculator;
    using ValidatorType = typename Validator;

// --------------------------------------------- Constructor & Destructor ---------------------------------------------


    BlockChain() = delete;
    BlockChain(Block const &genesis_block);
    ~BlockChain();

// --------------------------------------------------- Public Method --------------------------------------------------

    bool Append(Block const &block);
    bool AppendContent(BlockContentType const &content);
    bool AppendContent(BlockContentType const &content, BlockMiner const &miner);

    operator std::string() const;
    virtual std::string Description() const;

// -------------------------------------------------- Private Member --------------------------------------------------

  private:

    std::vector<Block const> blocks_{};
    std::unordered_map<BlockHash, size_t> hash_to_index_dict_{};

  };


}  // namespace ssybc


#endif  // BLOCKCHAIN_INCLUDE_BLOCKCHAIN_BLOCKCHAIN_HPP_

