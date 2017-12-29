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


#include "puppy.hpp"

#include <iostream>
#include <type_traits>

void PrintBreedSelections_();

int main(int const argc, char const **argv) {

  ssybc::logging::SetLoggerVerbosityLevel(ssybc::logging::LoggerVerbosity::kDebug);
  auto const logger = ssybc::logging::notest;

  namespace cp = crypto_puppy;

  using PuppyChain = typename ssybc::Blockchain<ssybc::Block<
    cp::Puppy,
    cp::PuppyBinaryConverter
  >>;

  std::cout << "Welcome to CryptoPuppy!" << std::endl;
  std::cout << "Please type in your name to adopt a puppy: ";

  std::string owner_name{};
  std::getline(std::cin, owner_name);

  std::cout << std::endl;
  std::cout << "Now please select the breed of your puppy you'd like to adopt:" << std::endl;
  PrintBreedSelections_();
  std::cout << "Type in number of selected breed: ";

  crypto_puppy::BreedRawType breed_raw{};
  std::cin >> breed_raw;

  --breed_raw;
  auto breed = static_cast<crypto_puppy::PuppyBreed>(breed_raw);

  std::cout << "What would you like to name it? : ";

  std::string name{};
  std::cin.ignore();
  std::getline(std::cin, name);

  std::cout << std::endl << "Great job " << owner_name << "!" << std::endl;
  std::cout << "Please be patient while we're building a pet house for " << name << "..." << std::endl;
  std::cout << std::endl;

  PuppyChain puppy_chain{
    PuppyChain::GenesisBlockMinedWithData({ breed, name, owner_name })
  };

  std::cout << std::endl << "Congratulations! " << name << " is living in a pet house on blockchain now!" << std::endl;
  std::cout << puppy_chain.Description() << std::endl;

  std::cout << "Would you like to grow " << name << "? [y/n] : ";
  char answer{};
  std::cin >> answer;
  if (answer == 'y') {
    auto puppy_block = puppy_chain.TailBlock();
    if (!puppy_block.IsHeaderOnly()) {
      auto puppy = puppy_block.Content().Data();
      puppy.LevelUp();
      std::cout << "Feeding and playing with " << puppy.Name() << "..." << std::endl;
      puppy_chain.Append(puppy);
      std::cout << puppy.Name() << " has grown up! Here's " << puppy.Name() << "'s history:" << std::endl;
      std::cout << puppy_chain.Description() << std::endl;
    }
  }
  std::cout << std::endl;
  std::cout << "Would you like to save " << name << "'s history to a binary file (so it can be reloaded later)? ";
  std::cout << "[y/n] : ";

  std::cin.ignore();
  std::cin >> answer;
  std::cout << std::endl;

  if (answer == 'y') {
    std::cout << "Please type in the file path: ";
    std::cin.ignore();
    std::string file_path{};
    std::getline(std::cin, file_path);
    bool const succeed{ puppy_chain.SaveBinaryToFileAtPath(file_path) };
    if (succeed) {
      std::cout << name << " saved to file! Have a great day!" << std::endl;
    } else {
      std::cout << "Oops... looks like something went wrong while trying to save " << name << "to file." << std::endl;
    }
  } else {
    std::cout << "Goodbye!" << std::endl;
  }

  return 0;
}

void PrintBreedSelections_()
{
  crypto_puppy::BreedRawType breed_max{ crypto_puppy::PuppyBreed::kPuppyBreedCount };
  for (crypto_puppy::BreedRawType breed_raw{ 0 }; breed_raw < breed_max; ++breed_raw) {
    auto breed = static_cast<crypto_puppy::PuppyBreed>(breed_raw);
    std::cout << ssybc::util::ToString(breed_raw + 1) << ": ";
    std::cout << crypto_puppy::PuppyBreedDescription(breed) << std::endl;
  }
}

/**************************************************** Sample Output ***************************************************
 *
 *
 *********************************************************************************************************************/

