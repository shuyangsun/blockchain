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


#ifndef SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_CONTENT_BLOCK_CONTENT_HPP_
#define SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_CONTENT_BLOCK_CONTENT_HPP_

#include "include/ssybc/general/general.hpp"

#include <string>
#include <memory>

namespace ssybc {

  template<typename DataT,
    template<typename> class BinaryConverterTemplateT,
    typename HashCalculatorT>
  class BlockContent {

  public:

    using BinaryConverterT = typename BinaryConverterTemplateT<DataT>;

// --------------------------------------------- Constructor & Destructor ---------------------------------------------

    BlockContent() = delete;

    BlockContent(DataT const &data);
    BlockContent(DataT &&data);

    BlockContent(BinaryData const &binary_data);
    BlockContent(BinaryData &&binary_data);

    BlockContent(BlockContent const &content);
    BlockContent(BlockContent &&content);

    ~BlockContent() = default;

// --------------------------------------------------- Public Method --------------------------------------------------
    
    DataT Data() const;
    BinaryData Binary() const;
    SizeT SizeOfBinary() const;

    BlockHash Hash() const;
    std::string HashAsString() const;

    operator std::string() const;
    std::string Description() const;
    virtual std::string Description(std::string const &lead_padding) const;

    BlockContent& operator=(BlockContent &&) = delete;
    BlockContent& operator=(BlockContent const &) = delete;

    bool operator==(BlockContent const & block) const;
    bool operator!=(BlockContent const & block) const;

  private:

// -------------------------------------------------- Private Field ---------------------------------------------------

    std::unique_ptr<DataT const> const data_ptr_;
    mutable bool did_cache_size_of_binary_{false};
    mutable SizeT size_of_binary_{};

// -------------------------------------------------- Private Method --------------------------------------------------
   
    void CacheSizeOfBinary_(SizeT const size) const;
  };

}  // namespace ssybc


#include "src/block/block_content/block_content_impl.hpp"


#endif  // SSYBC_INCLUDE_SSYBC_BLOCK_BLOCK_CONTENT_BLOCK_CONTENT_HPP_

