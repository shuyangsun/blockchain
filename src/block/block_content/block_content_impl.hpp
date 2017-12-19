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


#ifndef SSYBC_SRC_BLOCK_BLOCK_CONTENT_BLOCK_CONTENT_IMPL_HPP_
#define SSYBC_SRC_BLOCK_BLOCK_CONTENT_BLOCK_CONTENT_IMPL_HPP_


#include "include/ssybc/block/block_content/block_content.hpp"
#include "include/ssybc/utility/utility.hpp"

#include <exception>

// --------------------------------------------- Constructor & Destructor ---------------------------------------------


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::BlockContent(DataT const & data):
  data_ptr_{ std::make_unique<DataT const>(data) }
{
  if (SizeOfBinary() <= 0) {
    throw std::logic_error("Cannot construct BlockContent from data with size 0 as binary.");
  }
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::BlockContent(DataT &&data):
  data_ptr_{ std::make_unique<DataT const>(data) }
{
  if (SizeOfBinary() <= 0) {
    throw std::logic_error("Cannot construct BlockContent from data with size 0 as binary.");
  }
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::BlockContent(BinaryData const &binary_data):
  BlockContent(BinaryConverterType().DataFromBinaryData(binary_data))
{ EMPTY_BLOCK }


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::BlockContent(BinaryData &&binary_data) :
  BlockContent(BinaryConverterType().DataFromBinaryData(binary_data))
{ EMPTY_BLOCK }


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::BlockContent(BlockContent const & content):
  BlockContent(content.Data())
{ EMPTY_BLOCK }


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::BlockContent(BlockContent && content) :
  BlockContent(content.Data())
{ EMPTY_BLOCK }


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline DataT ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::Data() const
{
  return *data_ptr_;
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BinaryData ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::Binary() const
{
  auto result = BinaryConverterType().BinaryDataFromData(*data_ptr_);
  CacheSizeOfBinary_(result.size());
  return result;
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::SizeT ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::SizeOfBinary() const
{
  if (did_cache_size_of_binary_) {
    return size_of_binary_;
  }
  CacheSizeOfBinary_(Binary().size());
  return size_of_binary_;
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockHash ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::Hash() const
{
  return HashCalculatorT().Hash(Binary());
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline std::string ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::HashAsString() const
{
  return util::HexStringFromBytes(Hash(), " ");
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::operator std::string() const
{
  return Description();
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline std::string ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::Description(std::string const &lead_padding) const
{
  auto const size_str = util::ToString(SizeOfBinary());
  std::string data_str{};
  try {
    data_str = util::ToString(*data_ptr_);
  } catch (const std::exception& e) {
    data_str = util::HexStringFromBytes(Binary(), " ");
  }
  std::string result{lead_padding + "size: "};
  result += (size_str + ",\n");
  result += (lead_padding + "data: ");
  result += (data_str);
  return result;
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline std::string ssybc::BlockContent<DataT, BinaryConverterTemplateT, HashCalculatorT>::Description() const
{
  return Description("");
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline bool ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::operator==(BlockContent const & block) const
{
  return *data_ptr_ == *block.Data();
}


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline bool ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::operator!=(BlockContent const & block) const
{
  return *data_ptr_ != *block.Data();
}


// -------------------------------------------------- Private Method --------------------------------------------------


template<typename DataT, template<typename> class BinaryConverterTemplateT, typename HashCalculatorT>
inline void ssybc::BlockContent<
  DataT,
  BinaryConverterTemplateT,
  HashCalculatorT>::CacheSizeOfBinary_(SizeT const size) const
{
  if (did_cache_size_of_binary_) {
    return;
  }
  size_of_binary_ = size;
  did_cache_size_of_binary_ = true;
}


#endif  // SSYBC_SRC_BLOCK_BLOCK_CONTENT_BLOCK_CONTENT_IMPL_HPP_
