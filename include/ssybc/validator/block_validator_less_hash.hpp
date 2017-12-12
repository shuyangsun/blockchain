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

#ifndef SSYBC_INCLUDE_SSYBC_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_HPP_
#define SSYBC_INCLUDE_SSYBC_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_HPP_

#include "include/ssybc/validator/block_validator.hpp"

namespace ssybc {

  template<typename BlockT>
  class BlockValidatorLessHash: public virtual BlockValidator<BlockT> {
  public:

// --------------------------------------------------- Public Method --------------------------------------------------

    BlockValidatorLessHash();

    bool IsValidGenesisBlockHash(BlockHash const &hash) const override final;
    bool IsValidHashToAppend(BlockHash const &previous_hash, BlockHash const &hash) const override final;

  private:

// --------------------------------------------------- Private Member -------------------------------------------------
    
    BlockHash max_hash_{};
  };

}  // namespace ssybc


#include "src/validator/block_validator_less_hash_impl.hpp"


#endif  // SSYBC_INCLUDE_SSYBC_VALIDATOR_BLOCK_VALIDATOR_LESS_HASH_HPP_

