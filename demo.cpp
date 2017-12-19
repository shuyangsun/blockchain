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
  
  std::cout << "Started mining blocks..." << std::endl;

  // Initializing the Genesis Block with a string.
  StringBlockChain str_blockchain{ "This is a Genesis Block on SSY Blockchain!" };
  std::cout << "Genesis block mined!" << std::endl;

  // Appending content onto the chain.
  str_blockchain.Append("The second block needs a little bit time to mine.");
  std::cout << "Second block mined!" << std::endl;

  str_blockchain.Append("Third block is slower.");
  std::cout << "Third block mined!" << std::endl;

  std::cout << "Block mining finished." << std::endl;
  std::cout << std::endl;

  // Print Blockchain to human readable text.
  std::cout << str_blockchain.Description() << std::endl;

  // Looking up blocks by index and hash.
  auto genesis_block = str_blockchain.GenesisBlock();
  auto second_block = str_blockchain[1];
  auto last_block = str_blockchain.TailBlock();

  std::cout << std::endl;
  std::cout
    << "Block indices: "
    << genesis_block.Header().Index() << " "
    << second_block.Header().Index() << " "
    << last_block.Header().Index() << std::endl;
  
  auto last_block_by_negative_idx = str_blockchain[-1];
  auto last_block_by_hash = str_blockchain[last_block.Header().HashAsString()];

  std::cout << std::endl;
  std::cout << "Found last block by negative index: " << (last_block_by_negative_idx == last_block) << std::endl;
  std::cout << "Found last block by hash lookup: " << (last_block_by_hash == last_block) << std::endl;
  std::cout << std::endl;

  // Convert Blockchain to binary data, can be save to file later.
  auto str_chain_as_binary = str_blockchain.Binary();

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
 * 
 * Started mining blocks...
 * Genesis block mined!
 * Second block mined!
 * Third block mined!
 * Block mining finished.
 * 
 * [{
 *   header: {
 *     version: 0,
 *     index: 0,
 *     time_stamp: 2017-12-19T06:43:26UTC,
 *     nonce: 33345,
 *     merkel_root: 0414a621607c50202d805f2baef57d2c6344bc1560a783270e0e2db108e34c96,
 *     previous_hash: 0000000000000000000000000000000000000000000000000000000000000000,
 *     hash:          000065d2ce1b0ec1a45f61e49fba4fbe6d77d20a13851ccbd2be534154c0f6dc
 *   },
 *   content: {
 *     size: 42,
 *     data: This is a Genesis Block on SSY Blockchain!
 *   }
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 1,
 *     time_stamp: 2017-12-19T06:43:27UTC,
 *     nonce: 202554,
 *     merkel_root: 961530065a089857eb23a18837a5881e89356e7fd61695502126ffc041ac55ce,
 *     previous_hash: 000065d2ce1b0ec1a45f61e49fba4fbe6d77d20a13851ccbd2be534154c0f6dc,
 *     hash:          00004851e5139dac3438e81c0176031394e6e0dacf4c21963e2429455bb9f3ca
 *   },
 *   content: {
 *     size: 49,
 *     data: The second block needs a little bit time to mine.
 *   }
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 2,
 *     time_stamp: 2017-12-19T06:43:36UTC,
 *     nonce: 14197,
 *     merkel_root: 18a0309f564a3e67805e839f48f84af392cbb7947aa831676b6d7b4df5e7a273,
 *     previous_hash: 00004851e5139dac3438e81c0176031394e6e0dacf4c21963e2429455bb9f3ca,
 *     hash:          0000219e0bea7ed6a0a22352155cd1249172f69dc8e409a775acef6bdbd38cb8
 *   },
 *   content: {
 *     size: 22,
 *     data: Third block is slower.
 *   }
 * }]
 * 
 * Block indices: 0 1 2
 * 
 * Found last block by negative index: 1
 * Found last block by hash lookup: 1
 * 
 * 
 * Binary blockchain as hex:
 * 00 00 00 00 00 00 00 00 00 00 00 00 04 14 a6 21 60 7c 50 20 2d 80 5f 2b ae f5 7d 2c 63 44 bc 15 60 a7 83 27 0e 0e 2d
 * b1 08 e3 4c 96 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0e b5
 * 38 5a 00 00 00 00 41 82 00 00 00 00 00 00 2a 00 00 00 00 00 00 00 54 68 69 73 20 69 73 20 61 20 47 65 6e 65 73 69 73
 * 20 42 6c 6f 63 6b 20 6f 6e 20 53 53 59 20 42 6c 6f 63 6b 63 68 61 69 6e 21 00 00 00 00 01 00 00 00 00 00 00 00 96 15
 * 30 06 5a 08 98 57 eb 23 a1 88 37 a5 88 1e 89 35 6e 7f d6 16 95 50 21 26 ff c0 41 ac 55 ce 00 00 65 d2 ce 1b 0e c1 a4
 * 5f 61 e4 9f ba 4f be 6d 77 d2 0a 13 85 1c cb d2 be 53 41 54 c0 f6 dc 0f b5 38 5a 00 00 00 00 3a 17 03 00 00 00 00 00
 * 31 00 00 00 00 00 00 00 54 68 65 20 73 65 63 6f 6e 64 20 62 6c 6f 63 6b 20 6e 65 65 64 73 20 61 20 6c 69 74 74 6c 65
 * 20 62 69 74 20 74 69 6d 65 20 74 6f 20 6d 69 6e 65 2e 00 00 00 00 02 00 00 00 00 00 00 00 18 a0 30 9f 56 4a 3e 67 80
 * 5e 83 9f 48 f8 4a f3 92 cb b7 94 7a a8 31 67 6b 6d 7b 4d f5 e7 a2 73 00 00 48 51 e5 13 9d ac 34 38 e8 1c 01 76 03 13
 * 94 e6 e0 da cf 4c 21 96 3e 24 29 45 5b b9 f3 ca 18 b5 38 5a 00 00 00 00 75 37 00 00 00 00 00 00 16 00 00 00 00 00 00
 * 00 54 68 69 72 64 20 62 6c 6f 63 6b 20 69 73 20 73 6c 6f 77 65 72 2e
 * 
 * Reconstructed blockchain from binary data is identical with original: 1
 *
 **********************************************************************************************************************/

