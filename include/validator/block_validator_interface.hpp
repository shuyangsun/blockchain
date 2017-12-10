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

#ifndef BLOCKCHAIN_INCLUDE_VALIDATOR_BLOCK_VALIDATOR_INTERFACE_HPP_
#define BLOCKCHAIN_INCLUDE_VALIDATOR_BLOCK_VALIDATOR_INTERFACE_HPP_

#include "include/general.hpp"

namespace ssybc {

  template<typename BlockT>
  class BlockValidatorInterface {
  public:

// -------------------------------------------------- Public Interface -------------------------------------------------

    using BlockType = BlockT;

    virtual bool IsValidGenesisBlock(BlockT const &block) const = 0;
    virtual bool IsValidToAppend(BlockT const &previous_block, BlockT const &block) const = 0;

    virtual ~BlockValidatorInterface() { EMPTY_BLOCK }
  };

}  // namespace ssybc

#endif  // BLOCKCHAIN_INCLUDE_VALIDATOR_BLOCK_VALIDATOR_INTERFACE_HPP_

