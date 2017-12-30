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

#ifndef SSYBC_INCLUDE_SSYBC_BLOCKCHAIN_BLOCKCHAIN_ITERATOR_BLOCKCHAIN_ITERATOR_HPP_
#define SSYBC_INCLUDE_SSYBC_BLOCKCHAIN_BLOCKCHAIN_ITERATOR_BLOCKCHAIN_ITERATOR_HPP_

#include "include/ssybc/blockchain/blockchain.hpp"

#include <iterator>

namespace ssybc {

  template<typename BlockchainT>
  class BlockchainIterator : public std::iterator<std::forward_iterator_tag, BlockchainT> {

  public:

// -------------------------------------------------- Type Definition -------------------------------------------------

    using BlockchainType = BlockchainT;

// --------------------------------------------- Constructor & Destructor ---------------------------------------------

    BlockchainIterator() = default;

    BlockchainIterator(BlockchainT const &blockchain);
    BlockchainIterator(BlockchainT const &blockchain, std::size_t const index);

    BlockchainIterator(BlockchainIterator const &iter);
    BlockchainIterator(BlockchainIterator &&iter);

    ~BlockchainIterator() = default;

// --------------------------------------------------- Public Method --------------------------------------------------

    BlockchainIterator &operator=(BlockchainIterator const &iterator);
    bool operator==(BlockchainIterator const &iterator);
    bool operator!=(BlockchainIterator const &iterator);

    typename BlockchainT::BlockType operator*();

    BlockchainIterator &operator++();
    BlockchainIterator &operator++(int);

// -------------------------------------------------- Private Member --------------------------------------------------
  private:
    BlockchainT const &blockchain_;
    std::size_t index_{};
  };

}  // namespace ssybc


#include "src/blockchain/blockchain_iterator/blockchain_iterator_impl.hpp"


#endif  // SSYBC_INCLUDE_SSYBC_BLOCKCHAIN_BLOCKCHAIN_ITERATOR_BLOCKCHAIN_ITERATOR_HPP_

