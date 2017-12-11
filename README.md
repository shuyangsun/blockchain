# SSYBlockchain

## Introduction

SSYBlockchain is a generic purpose blockchain that supports dynamic content data type, hashing function, block append validation, and block miner. Default implementation suits many common situations, but it is highly customizable. The framework heavily utilizes C++ template programming to ensure performance, security and make it less error-prone when developers want to extend its functionality.

Checkout [demo.cpp](https://github.com/shuyangsun/ssy_blockchain/blob/master/demo.cpp) for a simple demonstration for a string blockchain.

## Basics of Block

A `Block` is a unit in a `Blockchain`, it contains the following information: index, time stamp of when block is created (not when block is mined), hash of previous block, hash of next block, nonce, and its data content.

### Content data type and BinaryDataConverter

Each `Block` type has to be constructed with a content data type and a `BinaryDataConverter`. Content data type is the type of data that's stored in the block, it can be C++ built-in type or a customized object type. `BinaryDataConverter` tells the block how to export its data to a binary format, this is essential because fast and efficient binary information conversion is crucial to decentralizing the open ledger.

The framework comes with support for many commonly used data types like `std::string`, `int`, `char` and other C++ primitive types, along with a default `BinaryDataConverter` implementation to support binary conversion of these types.

> SSYBlockchain binary format uses little-endian, when implementing customized converter, make sure big-endian is also correctly handled.

### Hashing

Hashing is the fundamental of blockchain security, each `Block` must has a `HashCalculator`, which is responsible for generating hash value for the block. Notice `HashCalculator` is only responsible for generating hash, it is not responsible for the validation of hash.

The default hash function is [SHA256](https://en.wikipedia.org/wiki/SHA-2), but developers can implement their own hash function by inheriting from a abstract class.

## Validator

A `BlockValidator` is responsible for validating if a genesis block has the correct hash, and if a block can be appended to a blockchain. This is where developers can set their own difficulty and block appending rules.

The default implementation of `BlockValidator` has a difficulty level 2 on a genesis block, and appending block's hash value has to be less than previous block's hash value.

## Miner

A `BlockMiner` is a class that mines the block, it is independent of the `Blockchain`, and vise-versa. A `Blockchain` can function independently on a `Miner`, but implementation of `Miner` reuses many building blocks of `BlockChain`, especially the validator and hash function calculator.

The default implementation uses CPU brute-force.

## Blockchain

`Blockchain` represents a blockchain, it must be initialized with a genesis `Block`. Developers can append a `Block` or content of new block onto a `Blockchain`, in the case of content, a default miner is used for mining the block, which can seriously decrease performance.

