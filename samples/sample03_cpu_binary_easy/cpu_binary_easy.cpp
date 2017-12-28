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
  // To log multi-thread CPU mining information, set verbosity level to LoggerVerbosity::kThreading.
  ssybc::logging::SetLoggerVerbosityLevel(ssybc::logging::LoggerVerbosity::kDebug);
  auto const logger = ssybc::logging::notest;

  logger << "SSYBlockchain Version " << ssybc::util::VersionString() << std::endl;
  logger << std::endl;

  // Define a type alias for a blockchain with content type on each block as BinaryData.
  using BinaryBlockChain = typename ssybc::Blockchain<ssybc::Block<ssybc::BinaryData>>;

  // Read this source file itself as binary data.
  auto binary_data = ssybc::util::ReadBinaryDataFromFileAtPath(__FILE__);

  // Initializing the Genesis Block with binary data.
  BinaryBlockChain binary_blockchain{
    BinaryBlockChain::GenesisBlockMinedWithData(binary_data)
  };

  // Appending content onto the chain.
  binary_blockchain.Append(ssybc::BinaryData{ 'U', 'V', 'W' });
  binary_blockchain.Append(ssybc::BinaryData{ 'X', 'Y', 'Z' });

  logger << std::endl;
  logger << binary_blockchain.Description() << std::endl;

  return 0;
}

/**************************************************** Sample Output ***************************************************
 *
 * SSYBlockchain Version 0.2.1
 * 
 * Mining Genesis block...
 * Finished mining Genesis block.
 * Mining block # 1...
 * Finished mining block # 1.
 * Mining block # 2...
 * Finished mining block # 2.
 * 
 * [{
 *   header: {
 *     version: 0,
 *     index: 0,
 *     time_stamp: 2017-12-28T22:00:24UTC,
 *     nonce: 8384883669867984338,
 *     merkel_root:   e14018d97b248cec662aa1eeaf912adbe53c8bf7e686df52e3f5fce3e612c112,
 *     previous_hash: 0000000000000000000000000000000000000000000000000000000000000000,
 *     hash:          0000089660c70830acfe09c5c90d991581ed7b4121465ae75ac2b8ff7d57c827
 *   },
 *   content: {
 *     size: 2917,
 *     data:
 *   2f 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a
 *   2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a
 *   2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a
 *   2a 2a 2a 2a 2a 0d 0a 20 2a 0d 0a 20 2a 20 43 6f 70 79 72 69 67 68 74 20 28 63 29 20 32 30 31 37 2d 32 30 31 38 20
 *   .............
 *   }
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 1,
 *     time_stamp: 2017-12-28T22:00:24UTC,
 *     nonce: 11738837137815296258,
 *     merkel_root:   d2ef8cf239366feac78e89f210cc4ab28ddb9c4df8738d1bd3dc745dcb9a07cd,
 *     previous_hash: 0000089660c70830acfe09c5c90d991581ed7b4121465ae75ac2b8ff7d57c827,
 *     hash:          000008515b7fae463383fb5a8c01cf9749f348863565973768ee071edbccb10b
 *   },
 *   content: {
 *     size: 3,
 *     data: 55 56 57
 *   }
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 2,
 *     time_stamp: 2017-12-28T22:00:25UTC,
 *     nonce: 11738837137815300864,
 *     merkel_root:   c49d0a2c78cfa181a275ec91e47109af129bec483285aa6e814c42e166b4919e,
 *     previous_hash: 000008515b7fae463383fb5a8c01cf9749f348863565973768ee071edbccb10b,
 *     hash:          000002cdc698062c3b9e2401a4795855515a6a83eff5f30b224c3332ab1167a5
 *   },
 *   content: {
 *     size: 3,
 *     data: 58 59 5a
 *   }
 * }]
 *
 *********************************************************************************************************************/

