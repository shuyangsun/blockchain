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

#include "include/blockchain/blockchain.hpp"
#include "include/utility/utility.hpp"


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
  std::cout
    << "Block indices: "
    << genesis_block.Index() << " "
    << second_block.Index() << " "
    << last_block.Index() << std::endl;
  
  auto last_block_by_negative_idx = str_blockchain[-1];
  auto last_block_by_hash = str_blockchain[last_block.HashAsString()];

  std::cout << "Found last block by negative index: " << (last_block_by_negative_idx == last_block) << std::endl;
  std::cout << "Found last block by hash lookup: " << (last_block_by_hash == last_block) << std::endl;

  // Convert Blockchain to binary data, can be save to file later.
  auto str_chain_as_binary = str_blockchain.ToBinary();

  // Visualize binary data.
  std::cout << "Binary block chain as hex:" << std::endl;
  std::cout << ssybc::util::HexStringFromBytes(str_chain_as_binary, " ") << std::endl;

  // Reconstruct Blockchain from binary data.
  StringBlockChain resconstructed_strchain{ str_chain_as_binary };
  std::cout
    << "Reconstructed blockchain from is identical with original: "
    << (str_blockchain == resconstructed_strchain) << std::endl;

  return 0;
}

