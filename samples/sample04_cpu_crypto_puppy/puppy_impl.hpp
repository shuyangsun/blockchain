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

#include <type_traits>
#include <vector>
#include <iterator>


namespace crypto_puppy {
  std::string OwnerInfo_(Puppy const &puppy);
}


inline crypto_puppy::Puppy::Puppy(PuppyBreed const breed, std::string const & owner_id):
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


ssybc::BinaryData crypto_puppy::PuppyBinaryConverter::BinaryDataFromData(Puppy const & puppy) const
{
  auto level = puppy.Level();
  auto breed = puppy.Breed();
  auto owner_id = puppy.OwnerID();

  using level_raw_type = typename std::underlying_type<decltype(level)>::type;
  using breed_raw_type = typename std::underlying_type<decltype(breed)>::type;

  auto level_raw = static_cast<level_raw_type>(level);
  auto breed_raw = static_cast<breed_raw_type>(breed);
  ssybc::SizeT owner_id_size = static_cast<ssybc::SizeT>(owner_id.size());

  auto level_binary = ssybc::BinaryDataConverterDefault<level_raw_type>().BinaryDataFromData(level_raw);
  auto breed_binary = ssybc::BinaryDataConverterDefault<breed_raw_type>().BinaryDataFromData(breed_raw);
  auto owner_id_size_binary = ssybc::BinaryDataConverterDefault<ssybc::SizeT>().BinaryDataFromData(owner_id_size);
  auto owner_id_binary = ssybc::BinaryDataConverterDefault<std::string>().BinaryDataFromData(owner_id);

  return ssybc::util::ConcatenateMoveDestructive(
    std::vector<ssybc::BinaryData> {level_binary, breed_binary, owner_id_size_binary, owner_id_binary}
  );
}


inline auto crypto_puppy::PuppyBinaryConverter::DataFromBinaryData(
  ssybc::BinaryData const & binary_data) const -> Puppy
{
  ssybc::BinaryData bin_copy{ binary_data.begin(), binary_data.end() };
  auto iter_begin = bin_copy.begin();
  auto iter_end = bin_copy.begin();

  using level_raw_type = typename std::underlying_type<PuppyLevel>::type;
  using breed_raw_type = typename std::underlying_type<PuppyBreed>::type;

  auto level_size = sizeof(level_raw_type);
  auto breed_size = sizeof(breed_raw_type);
  auto size_size = sizeof(ssybc::SizeT);

  std::advance(iter_end, level_size);
  auto level_raw = ssybc::BinaryDataConverterDefault<level_raw_type>().DataFromBinaryData(
    ssybc::BinaryData{iter_begin, iter_end}
  );
  iter_begin = iter_end;
  std::advance(iter_end, breed_size);
  auto breed_raw = ssybc::BinaryDataConverterDefault<breed_raw_type>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );
  iter_begin = iter_end;
  std::advance(iter_end, size_size);
  auto size_of_owner_id = ssybc::BinaryDataConverterDefault<ssybc::SizeT>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );
  auto owner_id_size = static_cast<std::size_t>(size_of_owner_id);
  iter_begin = iter_end;
  std::advance(iter_end, owner_id_size);
  std::string owner_id = ssybc::BinaryDataConverterDefault<std::string>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );

  auto breed = static_cast<PuppyBreed>(breed_raw);
  auto level = static_cast<PuppyLevel>(level_raw);
  
  Puppy result{ breed, owner_id };
  result.level_ = level;
  return result;
}


std::string crypto_puppy::PuppyBreedDescription(PuppyBreed const breed)
{
  switch (breed) {
  case PuppyBreed::kHusky:
    return "Husky";
  case PuppyBreed::kBulldog:
    return "Bulldog";
  default:
    return "Unknown breed";
  }
}


std::string crypto_puppy::PuppyLevelDescription(PuppyLevel const level)
{
  switch (level) {
  case PuppyLevel::kBaby:
    return "Baby";
  case PuppyLevel::kAdult:
    return "Adult";
  default:
    return "Unknown level";
  }
}


std::string crypto_puppy::OwnerInfo_(Puppy const &puppy)
{
  std::string result{ PuppyLevelDescription(puppy.Level()) };
  result += " ";
  result += PuppyBreedDescription(puppy.Breed());
  result += " owned by " + puppy.OwnerID() + "!";
  return result;
}

#endif  // SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_IMPL_HPP_
