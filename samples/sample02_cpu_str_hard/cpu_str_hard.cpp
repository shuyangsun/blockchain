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


#include "include/ssybc/ssybc.hpp"

#include <iostream>


int main(int const argc, char const **argv) {

  // Set logging verbosity level and initialize a general purpose logger.
  ssybc::logging::SetLoggerVerbosityLevel(ssybc::logging::LoggerVerbosity::kThreading);
  auto const logger = ssybc::logging::notest;

  logger << "SSYBlockchain Version " << ssybc::util::VersionString() << std::endl;
  logger << std::endl;

  ssybc::logging::warning << "WARNING: long mining time." << std::endl << std::endl;

  // Define a type alias for a blockchain with content type std::string, set initial difficulty level to 4.
  using StringBlockChain = typename ssybc::Blockchain<ssybc::Block<std::string>, 4>;

  StringBlockChain str_blockchain{
    StringBlockChain::GenesisBlockMinedWithData("This is a Genesis Block on SSY Blockchain!")
  };
  logger << str_blockchain.TailBlock().Description() << std::endl;

  for (std::size_t i{0}; i < 5; ++i) {
    std::string const content{ "This is the content on block # " + ssybc::util::ToString(i + 1) + "."};
    logger << str_blockchain.TailBlock().Description() << std::endl;
  }

  return 0;
}

/**************************************************** Sample Output ***************************************************
 * SSYBlockchain Version 0.2.1
 * 
 * WARNING: long mining time.
 * 
 * Mining Genesis block...
 * Mining Genesis block variables...
 * Creating 12 threads for genesis block mining...
 * Thread mining nonce in range [0, 1676976733973595601)...
 * Thread mining nonce in range [1676976733973595601, 3353953467947191202)...
 * Thread mining nonce in range [3353953467947191202, 5030930201920786803)...
 * Thread mining nonce in range [5030930201920786803, 6707906935894382404)...
 * Thread mining nonce in range [8384883669867978005, 10061860403841573606)...
 * Thread mining nonce in range [10061860403841573606, 11738837137815169207)...
 * Thread mining nonce in range [11738837137815169207, 13415813871788764808)...
 * Thread mining nonce in range [13415813871788764808, 15092790605762360409)...
 * Thread mining nonce in range [15092790605762360409, 16769767339735956010)...
 * Thread mining nonce in range [16769767339735956010, 18446744073709551611)...
 * Thread mining nonce in range [18446744073709551611, 1676976733973595596)...
 * Thread mining nonce in range [6707906935894382404, 8384883669867978005)...
 *
 * ...
 *
 *********************************************************************************************************************/

