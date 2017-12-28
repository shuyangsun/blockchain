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

#include<iostream>


int main(int const argc, char const **argv) {

  // Set logging verbosity level and initialize a general purpose logger.
  // To log multi-thread CPU mining information, set verbosity level to LoggerVerbosity::kThreading.
  ssybc::logging::SetLoggerVerbosityLevel(ssybc::logging::LoggerVerbosity::kDebug);
  auto const logger = ssybc::logging::notest;

  logger << "SSYBlockchain Version " << ssybc::util::VersionString() << std::endl;
  logger << std::endl;

  // Define a type alias for a blockchain with content type on each block as string.
  using StringBlockChain = typename ssybc::Blockchain<ssybc::Block<std::string>>;
  
  // StringBlockChain by default uses the default binary data converter; double-sha256 hash calculator for both header
  // and data; validator starts with diffculty level 2 for genesis block and appending hash must be less than previous
  // hash; miner uses multi-thread brute force algorithm on CPU.
  // Data type, binary converter, hash calculator, vadlidator and miner are all customizable. User-defined custom data
  // types are also supported, as long as customized binary data converter provides a valid binary conversion.

  // Initializing the Genesis Block with a string.
  StringBlockChain str_blockchain{
    StringBlockChain::GenesisBlockMinedWithData("This is a Genesis Block on SSY Blockchain!")
  };

  // Appending content onto the chain.
  str_blockchain.Append("Mining the second block on multi-thread CPU code is not that slow.");
  str_blockchain.Append("Third block may take a little longer.");

  logger << std::endl;
  logger << str_blockchain.Description() << std::endl;

  // Looking up blocks by index and hash.
  auto genesis_block = str_blockchain.GenesisBlock();
  auto second_block = str_blockchain[1];
  auto last_block = str_blockchain.TailBlock();

  logger << std::endl;
  logger
    << "Block indices: "
    << genesis_block.Header().Index() << " "
    << second_block.Header().Index() << " "
    << last_block.Header().Index() << std::endl;
  
  auto last_block_by_negative_idx = str_blockchain[-1];
  auto last_block_by_hash = str_blockchain[last_block.Header().Hash()];
  auto last_block_by_hash_str = str_blockchain[last_block.Header().HashAsString()];

  logger << std::endl;
  logger << "Found last block by negative index: " << (last_block_by_negative_idx == last_block) << std::endl;
  logger << "Found last block by hash lookup: " << (last_block_by_hash == last_block) << std::endl;
  logger << "Found last block by hash string lookup: " << (last_block_by_hash_str == last_block) << std::endl;
  logger << std::endl;

  // Export Blockchain to binary data, can be save to file later.
  auto str_chain_as_binary = str_blockchain.Binary();

  // Visualize binary data.
  logger << std::endl;
  logger << "Binary blockchain as hex:" << std::endl;
  logger << ssybc::util::HexStringFromBytes(str_chain_as_binary, " ") << std::endl;

  // Reconstruct Blockchain from binary data.
  StringBlockChain resconstructed_strchain{ str_chain_as_binary };
  logger << std::endl;
  logger
    << "Reconstructed blockchain from binary data is identical with original: "
    << (str_blockchain == resconstructed_strchain) << std::endl;

  // Export Blockchain headers to binary data.
  auto const strchain_header_binary = str_blockchain.BinaryHeadersOnly();

  logger << std::endl;
  logger << "Binary blockchain headers as hex:" << std::endl;
  logger << ssybc::util::HexStringFromBytes(strchain_header_binary, " ") << std::endl;

  // Reconstruct Blockchain headers from binary data.
  StringBlockChain resconstructed_strchain_header{ strchain_header_binary };
  logger << std::endl;
  logger << "Reconstructed headers from binary data:" << std::endl;
  logger << resconstructed_strchain_header.Description() << std::endl;

  logger << std::endl;
  logger
    << "Reconstructed blockchain headers from binary data is identical with original: "
    << (str_blockchain == resconstructed_strchain_header) << std::endl;

  // Save to binary file.
  std::string const file_path{ "temp.ssybc" };
  bool const save_succeeded{ str_blockchain.SaveHeadersOnlyBinaryToFileAtPath(file_path) };
  logger << std::endl;
  logger << "Save binary header to file succeeded: " << save_succeeded << std::endl;

  // Load from binary file.
  auto loaded_blockchain = StringBlockChain::LoadFromBinaryFileAtPath(file_path);
  logger << "Loaded Blockchain is identical with original: " << (loaded_blockchain == str_blockchain);
  logger << std::endl;

  return 0;
}

/**************************************************** Sample Output ***************************************************
 * 
 * SSYBlockchain Version 0.1.1
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
 *     time_stamp: 2017-12-26T00:58:50UTC,
 *     nonce: 13835058055282166369,
 *     merkel_root:   0414a621607c50202d805f2baef57d2c6344bc1560a783270e0e2db108e34c96,
 *     previous_hash: 0000000000000000000000000000000000000000000000000000000000000000,
 *     hash:          0000cc356c65e09d5798252924ea037bf4e3f424cd1b5a177ba79c65c296dc98
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
 *     time_stamp: 2017-12-26T00:58:50UTC,
 *     nonce: 16909515400900427020,
 *     merkel_root:   b75f4e8de66db47260df43bc75a5a9ebd9757a041c065524a9a45546cfe48157,
 *     previous_hash: 0000cc356c65e09d5798252924ea037bf4e3f424cd1b5a177ba79c65c296dc98,
 *     hash:          000039f2c9cb2cd297ea77eeaec362b432b7ff70c2571232f06cd3d99267448d
 *   },
 *   content: {
 *     size: 66,
 *     data: Mining the second block on multi-thread CPU code is not that slow.
 *   }
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 2,
 *     time_stamp: 2017-12-26T00:58:50UTC,
 *     nonce: 12297829382473048422,
 *     merkel_root:   de9ed254453c75049533485c54a076033e0a566e0b43c72227408b9e76ee0a61,
 *     previous_hash: 000039f2c9cb2cd297ea77eeaec362b432b7ff70c2571232f06cd3d99267448d,
 *     hash:          000030130c5040240cf567d57db516e8866bb0a6704cc2e905a011219617a975
 *   },
 *   content: {
 *     size: 37,
 *     data: Third block may take a little longer.
 *   }
 * }]
 * 
 * Block indices: 0 1 2
 * 
 * Found last block by negative index: 1
 * Found last block by hash lookup: 1
 * Found last block by hash string lookup: 1
 * 
 * 
 * Binary blockchain as hex:
 * 00 00 00 00 00 00 00 00 00 00 00 00 04 14 a6 21 60 7c 50 20 2d 80 5f 2b ae f5 7d 2c 63 44 bc 15 60 a7 83 27 0e 0e 2d
 * b1 08 e3 4c 96 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ca 9e
 * 41 5a 00 00 00 00 61 0a 00 00 00 00 00 c0 2a 00 00 00 00 00 00 00 54 68 69 73 20 69 73 20 61 20 47 65 6e 65 73 69 73
 * 20 42 6c 6f 63 6b 20 6f 6e 20 53 53 59 20 42 6c 6f 63 6b 63 68 61 69 6e 21 00 00 00 00 01 00 00 00 00 00 00 00 b7 5f
 * 4e 8d e6 6d b4 72 60 df 43 bc 75 a5 a9 eb d9 75 7a 04 1c 06 55 24 a9 a4 55 46 cf e4 81 57 00 00 cc 35 6c 65 e0 9d 57
 * 98 25 29 24 ea 03 7b f4 e3 f4 24 cd 1b 5a 17 7b a7 9c 65 c2 96 dc 98 ca 9e 41 5a 00 00 00 00 0c bd aa aa aa aa aa ea
 * 42 00 00 00 00 00 00 00 4d 69 6e 69 6e 67 20 74 68 65 20 73 65 63 6f 6e 64 20 62 6c 6f 63 6b 20 6f 6e 20 6d 75 6c 74
 * 69 2d 74 68 72 65 61 64 20 43 50 55 20 63 6f 64 65 20 69 73 20 6e 6f 74 20 74 68 61 74 20 73 6c 6f 77 2e 00 00 00 00
 * 02 00 00 00 00 00 00 00 de 9e d2 54 45 3c 75 04 95 33 48 5c 54 a0 76 03 3e 0a 56 6e 0b 43 c7 22 27 40 8b 9e 76 ee 0a
 * 61 00 00 39 f2 c9 cb 2c d2 97 ea 77 ee ae c3 62 b4 32 b7 ff 70 c2 57 12 32 f0 6c d3 d9 92 67 44 8d ca 9e 41 5a 00 00
 * 00 00 66 e1 aa aa aa aa aa aa 25 00 00 00 00 00 00 00 54 68 69 72 64 20 62 6c 6f 63 6b 20 6d 61 79 20 74 61 6b 65 20
 * 61 20 6c 69 74 74 6c 65 20 6c 6f 6e 67 65 72 2e
 * 
 * Reconstructed blockchain from binary data is identical with original: 1
 * 
 * Binary blockchain headers as hex:
 * 00 00 00 00 00 00 00 00 00 00 00 00 04 14 a6 21 60 7c 50 20 2d 80 5f 2b ae f5 7d 2c 63 44 bc 15 60 a7 83 27 0e 0e 2d
 * b1 08 e3 4c 96 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ca 9e
 * 41 5a 00 00 00 00 61 0a 00 00 00 00 00 c0 00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 b7 5f 4e 8d e6
 * 6d b4 72 60 df 43 bc 75 a5 a9 eb d9 75 7a 04 1c 06 55 24 a9 a4 55 46 cf e4 81 57 00 00 cc 35 6c 65 e0 9d 57 98 25 29
 * 24 ea 03 7b f4 e3 f4 24 cd 1b 5a 17 7b a7 9c 65 c2 96 dc 98 ca 9e 41 5a 00 00 00 00 0c bd aa aa aa aa aa ea 00 00 00
 * 00 00 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 de 9e d2 54 45 3c 75 04 95 33 48 5c 54 a0 76 03 3e 0a 56 6e 0b 43
 * c7 22 27 40 8b 9e 76 ee 0a 61 00 00 39 f2 c9 cb 2c d2 97 ea 77 ee ae c3 62 b4 32 b7 ff 70 c2 57 12 32 f0 6c d3 d9 92
 * 67 44 8d ca 9e 41 5a 00 00 00 00 66 e1 aa aa aa aa aa aa 00 00 00 00 00 00 00 00
 * 
 * Reconstructed headers from binary data:
 * [{
 *   header: {
 *     version: 0,
 *     index: 0,
 *     time_stamp: 2017-12-26T00:58:50UTC,
 *     nonce: 13835058055282166369,
 *     merkel_root:   0414a621607c50202d805f2baef57d2c6344bc1560a783270e0e2db108e34c96,
 *     previous_hash: 0000000000000000000000000000000000000000000000000000000000000000,
 *     hash:          0000cc356c65e09d5798252924ea037bf4e3f424cd1b5a177ba79c65c296dc98
 *   },
 *   content: __CONTENT_NOT_PROVIDED__
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 1,
 *     time_stamp: 2017-12-26T00:58:50UTC,
 *     nonce: 16909515400900427020,
 *     merkel_root:   b75f4e8de66db47260df43bc75a5a9ebd9757a041c065524a9a45546cfe48157,
 *     previous_hash: 0000cc356c65e09d5798252924ea037bf4e3f424cd1b5a177ba79c65c296dc98,
 *     hash:          000039f2c9cb2cd297ea77eeaec362b432b7ff70c2571232f06cd3d99267448d
 *   },
 *   content: __CONTENT_NOT_PROVIDED__
 * },
 * {
 *   header: {
 *     version: 0,
 *     index: 2,
 *     time_stamp: 2017-12-26T00:58:50UTC,
 *     nonce: 12297829382473048422,
 *     merkel_root:   de9ed254453c75049533485c54a076033e0a566e0b43c72227408b9e76ee0a61,
 *     previous_hash: 000039f2c9cb2cd297ea77eeaec362b432b7ff70c2571232f06cd3d99267448d,
 *     hash:          000030130c5040240cf567d57db516e8866bb0a6704cc2e905a011219617a975
 *   },
 *   content: __CONTENT_NOT_PROVIDED__
 * }]
 * 
 * Reconstructed blockchain headers from binary data is identical with original: 1
 * 
 * Save binary header to file succeeded: 1
 * Loaded Blockchain is identical with original: 1
 *
 *********************************************************************************************************************/

