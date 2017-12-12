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


#include "include/ssybc/utility/operator.hpp"

#include <utility>


// --------------------------------------------------- Helper Method --------------------------------------------------


namespace ssybc {

  std::pair<BlockHash, BlockHash> PairHashStripped_(BlockHash const & lhs, BlockHash const & rhs);
  std::pair<BlockHash::const_iterator, BlockHash::const_iterator> PairHashIterator_(
    BlockHash const & lhs,
    BlockHash const & rhs
  );

}


// -------------------------------------------------- Public Function -------------------------------------------------


bool ssybc::util::operator!=(BlockHash const & lhs, BlockHash const & rhs)
{
  auto const stripped = PairHashStripped_(lhs, rhs);
  if (stripped.first.size() != stripped.second.size()) {
    return true;
  }
  auto pair_iter = PairHashIterator_(stripped.first, stripped.second);
  for (; pair_iter.first != stripped.first.end(); ++pair_iter.first, ++pair_iter.second) {
    if (*(pair_iter.first) != *(pair_iter.second)) {
      return true;
    }
  }
  return false;
}


bool ssybc::util::operator==(BlockHash const & lhs, BlockHash const & rhs)
{
  return !(lhs != rhs);
}


bool ssybc::util::operator<=(BlockHash const & lhs, BlockHash const & rhs)
{
  auto const stripped = PairHashStripped_(lhs, rhs);
  if (stripped.first.size() < stripped.second.size()) {
    return true;
  }
  if (stripped.first.size() > stripped.second.size()) {
    return false;
  }
  auto pair_iter = PairHashIterator_(stripped.first, stripped.second);
  for (; pair_iter.first != stripped.first.end(); ++pair_iter.first, ++pair_iter.second) {
    if (*(pair_iter.first) > *(pair_iter.second)) {
      return false;
    }
    if (*(pair_iter.first) < *(pair_iter.second)) {
      return true;
    }
  }
  return true;
}


bool ssybc::util::operator>=(BlockHash const & lhs, BlockHash const & rhs)
{
  auto const stripped = PairHashStripped_(lhs, rhs);
  if (stripped.first.size() > stripped.second.size()) {
    return true;
  }
  if (stripped.first.size() < stripped.second.size()) {
    return false;
  }
  auto pair_iter = PairHashIterator_(stripped.first, stripped.second);
  for (; pair_iter.first != stripped.first.end(); ++pair_iter.first, ++pair_iter.second) {
    if (*(pair_iter.first) < *(pair_iter.second)) {
      return false;
    }
    if (*(pair_iter.first) > *(pair_iter.second)) {
      return true;
    }
  }
  return true;
}

bool ssybc::util::operator<(BlockHash const & lhs, BlockHash const & rhs)
{
  auto const stripped = PairHashStripped_(lhs, rhs);
  if (stripped.first.size() < stripped.second.size()) {
    return true;
  }
  if (stripped.first.size() > stripped.second.size()) {
    return false;
  }
  auto pair_iter = PairHashIterator_(stripped.first, stripped.second);
  for (; pair_iter.first != stripped.first.end(); ++pair_iter.first, ++pair_iter.second) {
    if (*(pair_iter.first) > *(pair_iter.second)) {
      return false;
    }
    if (*(pair_iter.first) < *(pair_iter.second)) {
      return true;
    }
  }
  return false;
}

bool ssybc::util::operator>(BlockHash const & lhs, BlockHash const & rhs)
{
  auto const stripped = PairHashStripped_(lhs, rhs);
  if (stripped.first.size() < stripped.second.size()) {
    return true;
  }
  if (stripped.first.size() > stripped.second.size()) {
    return false;
  }
  auto pair_iter = PairHashIterator_(stripped.first, stripped.second);
  for (; pair_iter.first != stripped.first.end(); ++pair_iter.first, ++pair_iter.second) {
    if (*(pair_iter.first) < *(pair_iter.second)) {
      return false;
    }
    if (*(pair_iter.first) > *(pair_iter.second)) {
      return true;
    }
  }
  return false;
}


// --------------------------------------------------- Helper Method --------------------------------------------------


inline auto ssybc::PairHashStripped_(BlockHash const & lhs, BlockHash const & rhs) -> std::pair<BlockHash, BlockHash>
{
  auto lhs_stripped = util::HashStrippedLeadingZeros(lhs);
  auto rhs_stripped = util::HashStrippedLeadingZeros(rhs);
  return std::make_pair(lhs_stripped, rhs_stripped);
}


inline auto ssybc::PairHashIterator_(
  BlockHash const & lhs,
  BlockHash const & rhs
) -> std::pair<BlockHash::const_iterator, BlockHash::const_iterator>
{
  return std::make_pair(lhs.begin(), rhs.begin());
}
