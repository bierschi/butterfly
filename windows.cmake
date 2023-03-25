set(CMAKE_SYSTEM_NAME Windows)

# 64-Bit Toolchain
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
# 32-Bit Toochain
#set(TOOLCHAIN_PREFIX i686-w64-mingw32)

# Cross compilers to use for C and C++
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# Target environment on the build host system
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX} /usr/lib/gcc/${TOOLCHAIN_PREFIX}/7.3-posix)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
