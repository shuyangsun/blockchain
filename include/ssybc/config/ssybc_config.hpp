
#ifndef SSYBC_INCLUDE_SSYBC_CONFIG_SSYBC_CONFIG_HPP_
#define SSYBC_INCLUDE_SSYBC_CONFIG_SSYBC_CONFIG_HPP_


#define SSYBC_VERSION_MAJOR 0
#define SSYBC_VERSION_MINOR 1
#define SSYBC_VERSION_BUILD 1

/* #undef ENABLE_CUDA */

#define SSYBC_HAS_C11_GMTIME_S
#define SSYBC_HAS_WIN32_GMTIME_S
/* #undef SSYBC_HAS_UNIX_GMTIME_R */

#ifdef ENABLE_CUDA

#define SSYBC_IS_CUDA_ENABLED



#endif  // ENABLE_CUDA

#endif  // SSYBC_INCLUDE_SSYBC_CONFIG_SSYBC_CONFIG_HPP_
