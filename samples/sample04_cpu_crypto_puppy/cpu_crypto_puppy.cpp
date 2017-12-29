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

/**********************************************************************************************************************
 *
 * ASCII artworks from http://www.chris.com/ascii/index.php?art=animals/dogs
 *
 *********************************************************************************************************************/

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
 * Welcome to CryptoPuppy!
 * Please type in your name to adopt a puppy: Shuyang
 * 
 * Now please select the breed of your puppy you'd like to adopt:
 * 1: Husky
 * 2: Bulldog
 * Type in number of selected breed: 1
 * What would you like to name it? : Blosky
 * 
 * Great job Shuyang!
 * Please be patient while we're building a pet house for Blosky...
 * 
 * Mining Genesis block...
 * Finished mining Genesis block.
 * 
 * Congratulations! Blosky is living in a pet house on blockchain now!
 * [{
 *   header: {
 *     version: 0,
 *     index: 0,
 *     time_stamp: 2017-12-29T09:47:39UTC,
 *     nonce: 16769767339735958599,
 *     merkel_root:   50f0d38f1c22e73f0d10cb5f10e8de9ceefaf9961a6a5ed53ca82bf2d2a6de03,
 *     previous_hash: 0000000000000000000000000000000000000000000000000000000000000000,
 *     hash:          00004b3f9f2f964b2dd6e39e98483062fde26596a10da194762c161c8f5f0ae7
 *   },
 *   content: {
 *     size: 37,
 *     data: Shuyang's Blosky (Baby Husky)!
 *                              ;
 *                             |'
 *          _                  ; : ;
 *         / `-.              /: : |
 *        |  ,-.`-.          ,': : |
 *          :  `. `.       ,'-. : |
 *          ;    ;  `-.__,'    `-.|
 *           ;   ;  :::  ,::'`:.  `.
 *            `-. :  `    :.    `.
 *                   ,   ;   ,:    (
 *                :., :.    ,'o)): ` `-.
 *            ,/,' ;' ,::"'`.`---'   `.  `-._
 *          ,/  :  ; '"      `;'          ,--`.
 *         ;/   :; ;             ,:'     (   ,:)
 *           ,.,:.    ; ,:.,  ,-._ `.     \""'/
 *           '::'     `:'`  ,'(  `._____.-'"'
 *              ;,   ;  `.  `. `._`-.  \
 *              ;:.  ;:       `-._`-.  `.
 *               '`:. :        |' `. `  )
 *       -hrr-      ` ;:       |    `--__,'
 *                    '`      ,'
 *                         ,-'
 * 
 *   }
 * }]
 * Would you like to grow Blosky? [y/n] : y
 * Feeding and playing with Blosky...
 * Mining block # 1...
 * Finished mining block # 1.
 * Blosky has grown up! Here's Blosky's history:
 * [{
 *   header: {
 *     version: 0,
 *     index: 0,
 *     time_stamp: 2017-12-29T09:47:39UTC,
 *     nonce: 16769767339735958599,
 *     merkel_root:   50f0d38f1c22e73f0d10cb5f10e8de9ceefaf9961a6a5ed53ca82bf2d2a6de03,
 *     previous_hash: 0000000000000000000000000000000000000000000000000000000000000000,
 *     hash:          00004b3f9f2f964b2dd6e39e98483062fde26596a10da194762c161c8f5f0ae7
 *   },
 *   content: {
 *     size: 37,
 *     data: Shuyang's Blosky (Baby Husky)!
 *                              ;
 *                             |'
 *          _                  ; : ;
 *         / `-.              /: : |
 *        |  ,-.`-.          ,': : |
 *          :  `. `.       ,'-. : |
 *          ;    ;  `-.__,'    `-.|
 *           ;   ;  :::  ,::'`:.  `.
 *            `-. :  `    :.    `.
 *                   ,   ;   ,:    (
 *                :., :.    ,'o)): ` `-.
 *            ,/,' ;' ,::"'`.`---'   `.  `-._
 *          ,/  :  ; '"      `;'          ,--`.
 *         ;/   :; ;             ,:'     (   ,:)
 *           ,.,:.    ; ,:.,  ,-._ `.     \""'/
 *           '::'     `:'`  ,'(  `._____.-'"'
 *              ;,   ;  `.  `. `._`-.  \
 *              ;:.  ;:       `-._`-.  `.
 *               '`:. :        |' `. `  )
 *       -hrr-      ` ;:       |    `--__,'
 *                    '`      ,'
 *                         ,-'
 * 
 *   }
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 1,
 *     time_stamp: 2017-12-29T09:47:43UTC,
 *     nonce: 5030930201920802644,
 *     merkel_root:   23b1c0505cfa172721400053ac4cf8bc37b5e0734fb7b7ba09774712068800f2,
 *     previous_hash: 00004b3f9f2f964b2dd6e39e98483062fde26596a10da194762c161c8f5f0ae7,
 *     hash:          000044794e3c9f6fa77248fb1fee3bcb053a7966c0e5538b2cb86f57bbaa5064
 *   },
 *   content: {
 *     size: 37,
 *     data: Shuyang's Blosky (Adult Husky)!
 *                      ,
 *                 ,.  |
 *                |:  ; :
 *                :' ;| ::
 *                  : | `::
 *                 _)  |   `:`.
 *               ,' , `.    ;: ;
 *             ,' ;:  ;"'  ,:: |_
 *            /,   ` .    ;::: |:`-.__
 *         _,' _o  ,::.`:' ;  ;   . '
 *     _,-'           `:.          ;,
 *  ,-'                     ,:         `-;,
 *  ,                       ;:           ;--._
 *   `.______,-,----._     ,' ;:        ,/ ,  ,`
 *          / /,-';'       ; `:      ,'/,::.:::
 *        ,',;-'-'_,--;    ;   :.   ,',',;::::::
 *       ( /___,-'     `.     ;::,,'o/  ,:::::::
 *        `'             )    ;:,'o /  ;" - -::
 *                       __ _,'o ,'         ,::
 *                          ) `--'       ,..::::
 *       -hrr-              ; `.        ,:::::::
 *                           ;  ``::.    :::::::
 * 
 * 
 *   }
 * }]
 * 
 * Would you like to save Blosky's history to a binary file (so it can be reloaded later)? [y/n] : y
 * 
 * Please type in the file path: ~/Desktop/blosky_chain.ssybc
 * Blosky saved to file! Have a great day!
 *
 *********************************************************************************************************************/

