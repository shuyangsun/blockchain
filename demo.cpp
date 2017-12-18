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


#include<iostream>

#include "include/ssybc/ssybc.hpp"


int main(int const argc, char const **argv) {
  // Define a type alias for a blockchain with content type on each block as string.
  using StringBlockChain = typename ssybc::Blockchain<ssybc::Block<std::string>>;
  
  // Initializing the Genesis Block with a string.
  StringBlockChain str_blockchain{ "This is a Genesis Block on SSY Blockchain!" };

  // Appending content onto the chain.
  str_blockchain.Append("The second block needs a little bit time to mine.");
  str_blockchain.Append("Third block is slower.");

  // Print Blockchain to human readable text.
  std::cout << str_blockchain.Description() << std::endl;

  // Looking up blocks by index and hash.
  auto genesis_block = str_blockchain.GenesisBlock();
  auto second_block = str_blockchain[1];
  auto last_block = str_blockchain.TailBlock();

  std::cout << std::endl;
  std::cout
    << "Block indices: "
    << genesis_block.Index() << " "
    << second_block.Index() << " "
    << last_block.Index() << std::endl;
  
  auto last_block_by_negative_idx = str_blockchain[-1];
  auto last_block_by_hash = str_blockchain[last_block.HashAsString()];

  std::cout << std::endl;
  std::cout << "Found last block by negative index: " << (last_block_by_negative_idx == last_block) << std::endl;
  std::cout << "Found last block by hash lookup: " << (last_block_by_hash == last_block) << std::endl;
  std::cout << std::endl;

  // Convert Blockchain to binary data, can be save to file later.
  auto str_chain_as_binary = str_blockchain.ToBinary();

  // Visualize binary data.
  std::cout << std::endl;
  std::cout << "Binary blockchain as hex:" << std::endl;
  std::cout << ssybc::util::HexStringFromBytes(str_chain_as_binary, " ") << std::endl;

  // Reconstruct Blockchain from binary data.
  StringBlockChain resconstructed_strchain{ str_chain_as_binary };
  std::cout << std::endl;
  std::cout
    << "Reconstructed blockchain from binary data is identical with original: "
    << (str_blockchain == resconstructed_strchain) << std::endl;
  return 0;
}

/**************************************************** Sample Output ****************************************************
 * {
 *   index: 0,
 *   time_stamp: 2017-12-11T18:23:52UTC,
 *   nonce: 55363,
 *   pre_hash: 0000000000000000000000000000000000000000000000000000000000000000,
 *   cur_hash: 0000ed47f0747de374922683e83b8e259a80f8e89c31c96025aabde0c69d67ef,
 *   content_size_in_bytes: 42,
 *   content: This is a Genesis Block on SSY Blockchain!
 * },
 * {
 *   index: 1,
 *   time_stamp: 2017-12-11T18:23:53UTC,
 *   nonce: 31830,
 *   pre_hash: 0000ed47f0747de374922683e83b8e259a80f8e89c31c96025aabde0c69d67ef,
 *   cur_hash: 0000b32832a0e14debac17037abf5103e49c1f7cfd330e74a14518b438e8508e,
 *   content_size_in_bytes: 49,
 *   content: The second block needs a little bit time to mine.
 * },
 * {
 *   index: 2,
 *   time_stamp: 2017-12-11T18:23:54UTC,
 *   nonce: 115547,
 *   pre_hash: 0000b32832a0e14debac17037abf5103e49c1f7cfd330e74a14518b438e8508e,
 *   cur_hash: 000044d101e5b6de8e819980fb4bd5e86755a263a65e4515c073be7e76977400,
 *   content_size_in_bytes: 22,
 *   content: Third block is slower.
 * }
 * 
 * Block indices: 0 1 2
 * 
 * Found last block by negative index: 1
 * Found last block by hash lookup: 1
 * 
 * 
 * Binary blockchain as hex:
 * 8a 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 38 cd 2e 5a 00 00 00 00 43 d8 00 00 00 00 00 00 00 00 00 00 00 00 00
 * 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ed 47 f0 74 7d e3 74 92 26 83 e8 3b
 * 8e 25 9a 80 f8 e8 9c 31 c9 60 25 aa bd e0 c6 9d 67 ef 54 68 69 73 20 69 73 20 61 20 47 65 6e 65 73 69 73 20 42 6c 6f
 * 63 6b 20 6f 6e 20 53 53 59 20 42 6c 6f 63 6b 63 68 61 69 6e 21 91 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 39 cd
 * 2e 5a 00 00 00 00 56 7c 00 00 00 00 00 00 00 00 ed 47 f0 74 7d e3 74 92 26 83 e8 3b 8e 25 9a 80 f8 e8 9c 31 c9 60 25
 * aa bd e0 c6 9d 67 ef 00 00 b3 28 32 a0 e1 4d eb ac 17 03 7a bf 51 03 e4 9c 1f 7c fd 33 0e 74 a1 45 18 b4 38 e8 50 8e
 * 54 68 65 20 73 65 63 6f 6e 64 20 62 6c 6f 63 6b 20 6e 65 65 64 73 20 61 20 6c 69 74 74 6c 65 20 62 69 74 20 74 69 6d
 * 65 20 74 6f 20 6d 69 6e 65 2e 76 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 3a cd 2e 5a 00 00 00 00 5b c3 01 00 00
 * 00 00 00 00 00 b3 28 32 a0 e1 4d eb ac 17 03 7a bf 51 03 e4 9c 1f 7c fd 33 0e 74 a1 45 18 b4 38 e8 50 8e 00 00 44 d1
 * 01 e5 b6 de 8e 81 99 80 fb 4b d5 e8 67 55 a2 63 a6 5e 45 15 c0 73 be 7e 76 97 74 00 54 68 69 72 64 20 62 6c 6f 63 6b
 * 20 69 73 20 73 6c 6f 77 65 72 2e
 * 
 * Reconstructed blockchain from binary data is identical with original: 1
 * 
 **********************************************************************************************************************/

