# SSYBlockchain

SSYBlockchain is a generic purpose blockchain library, checkout [samples](https://github.com/shuyangsun/ssy_blockchain/tree/master/samples) for some sample projects, especially [CryptoPuppy](https://github.com/shuyangsun/ssy_blockchain/blob/master/samples/sample04_cpu_crypto_puppy/cpu_crypto_puppy.cpp).


## Installation

SSYBlockchain is built and tested on the following 64-bit laptop/desktop operating systems:

* MacOS 10.13 (High Sierra)
* Ubuntu 16.04 LTS
* Windows 10 (with Visual Studio 2017)

To get started, clone the source repository into a local path of your choice.

SSYBlockchain is distributed with [CMake](https://cmake.org/), to generate build system for your platform with CMake, download the latest version [here](https://cmake.org/download/).

### MacOS

1. Open CMake application, you will be given options to select source and destination location. Simply set source location to source file location, and binary destination to a folder of your choice.
2. Click "Configure". By default MacOS generates Unix Makefiles for build system, but you can select other build systems if you'd like.
3. After project configuration is done, you can configure project options. Check "BUILD_SAMPLES" to build executable sample projects, by default this option is "ON".
4. Click "Generate" to generate your build system.
5. After project generation is done, simply go to the binary folder, and build the project (i.e., run `make all` for Unix Makefiles).

If you chose to build sample projects,they will be inside the "samples" folder.

### Windows

Windows follows the same procedure as MacOS, except the default system generated is a Visual Studio solution. Make sure you have Visual Studio installed to open the solution.

An alternative option is opening source file folder from Visual Studio directly. Microsoft started supporting CMake natively since Visual Studio 2017, checkout a simple tutorial on Microsoft's [blog](https://blogs.msdn.microsoft.com/vcblog/2016/10/05/cmake-support-in-visual-studio/).

### Linux

There is no CMake GUI interface available on Linux platforms, the only option is to run CMake on command line. For CMake installation on Linux, checkout CMake's official [tutorial](https://cmake.org/install/).

Below is the procedure to generate build system on command line:

1. Create a folder at a location of your choice, this will be the binary destination folder.
2. Run `cd path_to_destination`.
3. Run `cmake -BUILD_SAMPLES=[ON/OFF] path_to_source`. This will generate Makefiles at destination folder.
4. Run `make all` to build the project.

>  `pthread` must be installed for project to compile, it is used for CPU mining.

## Introduction to SSYBlockchain

SSYBlockchain supports different kinds of content data type, hashing function, block append validation, and block miner. Default implementation suits many common situations (built in string and binary data content type support), and it is highly customizable. The framework utilizes C++ template programming heavily to ensure performance and make it less error-prone when developers extend its functionality.

### Basics of Block

A `Block` is a unit in a `Blockchain`, it contains the following information: index, time stamp, hash of previous block, merkle root, hash of current block, nonce, and its data content.

#### Content data type and BinaryDataConverter

Each `Block` type has to be constructed with a content data type and a `BinaryDataConverter`. Content data type is the type of data that's stored in the block, it can be C++ built-in type or a customized object type. `BinaryDataConverter` tells the block how to export its data to a binary format, this is essential because fast and efficient binary information conversion is crucial to decentralizing the open ledger.

The framework comes with support for many commonly used data types like `std::string`, `int`, `char` and other C++ primitive types, along with a default `BinaryDataConverter` implementation to support binary conversion of these types.

> SSYBlockchain binary format uses little-endian, when implementing customized converter, make sure big-endian is also correctly handled.

#### Hashing

Hashing is the fundamental of blockchain security, each `Block` must has a `HashCalculator`, which is responsible for generating hash value for the block. Notice `HashCalculator` is only responsible for generating hash, it is not responsible for the validation of hash.

The default hash function is Double-[SHA256](https://en.wikipedia.org/wiki/SHA-2), but developers can implement their own hash function by inheriting from a abstract class.

### Validator

A `BlockValidator` is responsible for validating if a genesis block has the correct hash, and if a block can be appended to a blockchain. This is where developers can set their own difficulty and block appending rules.

The default implementation of `BlockValidator` has a difficulty level 2 on a genesis block, and appending block's hash value has to be less than previous block's hash value.

### Miner

A `BlockMiner` is a class that mines the block, it is independent of the `Blockchain`, and vise-versa. A `Blockchain` can function independently on a `Miner`, but implementation of `Miner` reuses many building blocks of `BlockChain`, especially the validator and hash function calculator.

The default implementation uses CPU brute-force.

### Blockchain

`Blockchain` represents a blockchain, it must be initialized with a genesis `Block`. Developers can append a `Block` or content of new block onto a `Blockchain`, in the case of content, a default miner is used for mining the block, which can seriously decrease performance.

