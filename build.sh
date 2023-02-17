#!/bin/sh
BUILD_DIR=target
LINUX_BUILD_DIR=${BUILD_DIR}/linux
WINDOWS_BUILD_DIR=${BUILD_DIR}/win
BINARIES_DIR=${BUILD_DIR}/release
mode=Debug

red='\033[1;31m'
green='\033[1;32m'
yellow='\033[1;33m'
blue='\033[1;34m'
magenta='\033[1;35m'
reset='\033[0m'
bold='\033[1m'

printf "${yellow}::${reset}${bold} Using %s Mode!${reset}\n" "$mode"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p "${LINUX_BUILD_DIR}"
  mkdir -p "${WINDOWS_BUILD_DIR}"
  mkdir -p "${BINARIES_DIR}"
fi

printf "${yellow}::${reset}${bold} Building linux binaries${reset}\n%s"
printf "${magenta}  ->${reset}${bold} Generating build files${reset}\n%s"
cmake -G "Ninja" -B${LINUX_BUILD_DIR} -DCMAKE_BUILD_TYPE=${mode}
cd ${LINUX_BUILD_DIR}
printf "\n${magenta}  ->${reset}${bold} Building project${reset}\n%s"
ninja
cd ../../

printf "${yellow}::${reset}${bold} Building windows binaries${reset}\n%s"
printf "${magenta}  ->${reset}${bold} Generating build files${reset}\n%s"
#msvc-x64-cmake -G "Ninja" -B${WINDOWS_BUILD_DIR} -DCMAKE_BUILD_TYPE="$mode" #-DCMAKE_TOOLCHAIN_FILE=../../toolchains/WindowsToolchain/Windows.MSVC.toolchain.cmake
cmake -B${WINDOWS_BUILD_DIR} -DCMAKE_BUILD_TYPE=${mode} -DCMAKE_TOOLCHAIN_FILE=../../toolchains/mingw-w64-x86_64.cmake
cd ${WINDOWS_BUILD_DIR}
printf "\n${magenta}  ->${reset}${bold} Building project${reset}\n%s"
make
cd ../../

printf "${yellow}::${reset}${bold} Distributing binaries in ./target/release${reset}\n%s"
cd ${LINUX_BUILD_DIR}
cp logicdev ../release
cd ../../
cd ${WINDOWS_BUILD_DIR}
cp logicdev.exe ../release

printf "${green}::${reset}${bold} Done${reset}" ""
kill -2 $$