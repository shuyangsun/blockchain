# SSYBlockchain

## Introduction

SSYBlockchain is a generic purpose Blockchain that supports dynamic content data type, hashing function, block append validation, and block miner. Default implementation suits many common situations, but it is highly customizable. The framework heavily utilizes C++ template programming to ensure performance, security and make it less error-prone when developers want to extend its functionality.

Checkout [demo.cpp](https://github.com/shuyangsun/ssy_blockchain/blob/master/demo.cpp) for a simple demonstration for a string Blockchain.

## Basics of Block

A block is a unit on a Blockchain, it contains the following information: index, time stamp of when block is created (not when block is mined), hash of previous block, hash of next block, nonce, and its data content.

### Content Data Type and BinaryDataConverter

Each Blockchain type has to be constructed with a content data type and a BinaryDataConverter. Content data type is the type of data that's stored in the Block, it can be C++ built-in type or a customized object type. BinaryDataConverter tells the block how to export its data to a binary format, this is essential because fast and efficient binary information conversion is crucial to decentralizing the open ledger. The framework comes with support for many commonly used data types like `std::string`, `int`, `char` and other C++ primitive types, along with a default `BinaryDataConverter` implementation to support binary conversion of these types.

SSYBlockchain binary format uses little-endian, when implementing customized converter, make sure big-endian is also correctly handled.

The default hash function is [SHA256](https://en.wikipedia.org/wiki/SHA-2), but developers can implement their own Ha
