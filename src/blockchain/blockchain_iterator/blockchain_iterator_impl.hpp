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


#ifndef SSYBC_SRC_BLOCKCHAIN_BLOCKCHAIN_BLOCKCHAIN_ITERATOR_BLOCKCHAIN_ITERATOR_IMPL_HPP_
#define SSYBC_SRC_BLOCKCHAIN_BLOCKCHAIN_BLOCKCHAIN_ITERATOR_BLOCKCHAIN_ITERATOR_IMPL_HPP_

#include "include/ssybc/general/general.hpp"
#include "include/ssybc/blockchain/blockchain_iterator/blockchain_iterator.hpp"


// --------------------------------------------- Constructor & Destructor ---------------------------------------------


template<typename BlockchainT>
inline ssybc::BlockchainIterator<BlockchainT>::BlockchainIterator(BlockchainT const & blockchain):
  BlockchainIterator(blockchain, 0)
{ EMPTY_BLOCK }


template<typename BlockchainT>
inline ssybc::BlockchainIterator<BlockchainT>::BlockchainIterator(
  BlockchainT const & blockchain,
  std::size_t const index):
  blockchain_{ blockchain },
  index_{ index }
{ EMPTY_BLOCK }


template<typename BlockchainT>
inline ssybc::BlockchainIterator<BlockchainT>::BlockchainIterator(BlockchainIterator const & iter):
  BlockchainIterator(iter.blockchain_, iter.index_)
{ EMPTY_BLOCK }


template<typename BlockchainT>
inline ssybc::BlockchainIterator<BlockchainT>::BlockchainIterator(BlockchainIterator && iter):
  BlockchainIterator(iter.blockchain_, iter.index_)
{ EMPTY_BLOCK }


// --------------------------------------------------- Public Method --------------------------------------------------


template<typename BlockchainT>
inline auto ssybc::BlockchainIterator<BlockchainT>::operator=(
  BlockchainIterator const & iterator) -> BlockchainIterator&
{
  blockchain_ = iterator.blockchain_;
  index_ = iterator.index_;
  return *this;
}


template<typename BlockchainT>
inline bool ssybc::BlockchainIterator<BlockchainT>::operator==(BlockchainIterator const & iterator)
{
  return !((*this) == iterator);
}


template<typename BlockchainT>
inline bool ssybc::BlockchainIterator<BlockchainT>::operator!=(BlockchainIterator const & iterator)
{
  return index_ != iterator.index_;
}


template<typename BlockchainT>
inline typename BlockchainT::BlockType ssybc::BlockchainIterator<BlockchainT>::operator*()
{
  return blockchain_[index_];
}


template<typename BlockchainT>
inline auto ssybc::BlockchainIterator<BlockchainT>::operator++() -> BlockchainIterator&
{
  ++index_;
  return *this;
}


template<typename BlockchainT>
inline auto ssybc::BlockchainIterator<BlockchainT>::operator++(int) -> BlockchainIterator&
{
  BlockchainIterator result{ *this };
  ++(*this);
  return result;
}


#endif  // SSYBC_SRC_BLOCKCHAIN_BLOCKCHAIN_BLOCKCHAIN_ITERATOR_BLOCKCHAIN_ITERATOR_IMPL_HPP_

