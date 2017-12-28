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

#ifndef SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_IMPL_HPP_
#define SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_IMPL_HPP_

#include "puppy.hpp"


namespace crypto_puppy {
  std::string OwnerInfo_(Puppy const &puppy);
}


inline crypto_puppy::Puppy::Puppy(std::string const & owner_id, PuppyBreed const breed):
  owner_id_{ owner_id },
  breed_{ breed },
  level_{ PuppyLevel::kBaby }
{ EMPTY_BLOCK }


inline crypto_puppy::Puppy::Puppy(Puppy const & puppy):
  owner_id_ { puppy.OwnerID() },
  breed_{ puppy.Breed() },
  level_{ puppy.Level() }
{ EMPTY_BLOCK }


inline crypto_puppy::Puppy::Puppy(Puppy && puppy) :
  owner_id_{ puppy.OwnerID() },
  breed_{ puppy.Breed() },
  level_{ puppy.Level() }
{ EMPTY_BLOCK }


inline std::string crypto_puppy::Puppy::OwnerID() const
{
  return owner_id_;
}


inline auto crypto_puppy::Puppy::Breed() const -> PuppyBreed
{
  return breed_;
}


inline auto crypto_puppy::Puppy::Level() const -> PuppyLevel
{
  return level_;
}


inline void crypto_puppy::Puppy::LevelUp()
{
  auto level_val = static_cast<std::underlying_type<PuppyLevel>::type>(level_);
  ++level_val;
  level_ = static_cast<PuppyLevel>(level_val);
}


inline crypto_puppy::Puppy::operator std::string() const
{
  std::string result{ OwnerInfo_(*this) };
  return result;
}

std::string crypto_puppy::OwnerInfo_(Puppy const &puppy)
{
  std::string result{""};
  switch (puppy.Level()) {
  case PuppyLevel::kBaby:
    result += "A baby";
    break;
  case PuppyLevel::kAdult:
    result += "An adult";
    break;
  default:
    result += "An unknown level";
    break;
  }
  result += " ";
  switch (puppy.Breed()) {
  case PuppyBreed::kHusky:
    result += "Husky";
    break;
  case PuppyBreed::kBulldog:
    result += "Bulldog";
    break;
  default:
    result += "unknown breed";
    break;
  }
  result += " owned by " + puppy.OwnerID() + "!";
  return result;
}

#endif  // SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_IMPL_HPP_
