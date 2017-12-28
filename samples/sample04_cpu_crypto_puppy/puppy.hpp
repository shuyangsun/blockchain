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

#ifndef SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_HPP_
#define SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_HPP_

#include "include/ssybc/ssybc.hpp"

#include <string>

namespace crypto_puppy {

  enum PuppyBreed : uint32_t {
    kHusky = 0,
    kBulldog,
    kPuppyBreedCount
  };

  enum PuppyLevel : uint32_t {
    kBaby = 0,
    kAdult,
    kPuppyLevelCount
  };

  class Puppy;

  class PuppyBinaryConverter: ssybc::BinaryDataConverterInterface<Puppy> {
  public:
    ssybc::BinaryData BinaryDataFromData(Puppy const &puppy) const override;
    Puppy DataFromBinaryData(ssybc::BinaryData const &binary_data) const override;
  };

  class Puppy {
  public:
    Puppy() = delete;

    Puppy(PuppyBreed const breed, std::string const &owner_id);

    Puppy(Puppy const &puppy);
    Puppy(Puppy &&puppy);

    ~Puppy() = default;

    std::string OwnerID() const;
    PuppyBreed Breed() const;
    PuppyLevel Level() const;

    void LevelUp();
    operator std::string() const;

    friend Puppy PuppyBinaryConverter::DataFromBinaryData(ssybc::BinaryData const &binary_data) const;

  private:
    std::string const owner_id_;
    PuppyBreed const breed_;
    PuppyLevel level_;
  };



  std::string PuppyBreedDescription(PuppyBreed const breed);
  std::string PuppyLevelDescription(PuppyLevel const level);

}  // crypto_puppy

#include "puppy_impl.hpp"

#endif  // SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_HPP_
