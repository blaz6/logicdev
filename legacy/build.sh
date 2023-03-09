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

json=$(cat resources/constants.json)
get_color() {
  echo $json | jq -r ".formatting.$1"
}

build_binaries() {
  if [ "$1" == "LINUX" ]; then
    printf "$(get_color yellow)::$(get_color reset)$(get_color bold) Building linux binaries$(get_color reset)\n%s"
    printf "$(get_color magenta)  ->$(get_color reset)$(get_color bold) Generating build files$(get_color reset)\n%s"
    cmake -G "Ninja" -B${LINUX_BUILD_DIR} -DCMAKE_BUILD_TYPE=${mode} > /dev/null 2>&1
    cd ${LINUX_BUILD_DIR}
    printf "$(get_color magenta)  ->$(get_color reset)$(get_color bold) Building project$(get_color reset)\n%s"
    ninja > /dev/null 2>&1
    cd ../../
  elif [ "$1" == "WINDOWS" ]; then
    printf "$(get_color yellow)::$(get_color reset)$(get_color bold) Building windows binaries$(get_color reset)\n%s"
    printf "$(get_color magenta)  ->$(get_color reset)$(get_color bold) Generating build files$(get_color reset)\n%s"
    #msvc-x64-cmake -G "Ninja" -B${WINDOWS_BUILD_DIR} -DCMAKE_BUILD_TYPE="$mode" #-DCMAKE_TOOLCHAIN_FILE=../../toolchains/WindowsToolchain/Windows.MSVC.toolchain.cmake
    cmake -B${WINDOWS_BUILD_DIR} -DCMAKE_BUILD_TYPE=${mode} -DCMAKE_TOOLCHAIN_FILE=../../toolchains/mingw-w64-x86_64.cmake > /dev/null 2>&1
    cd ${WINDOWS_BUILD_DIR}
    printf "$(get_color magenta)  ->$(get_color reset)$(get_color bold) Building project$(get_color reset)\n%s"
    make > /dev/null 2>&1
    cd ../../
  else
    printf "$(get_color red):: An error occurred"
  fi
}

printf "${yellow}::$(get_color reset)$(get_color bold) Using %s Mode!${reset}\n" "$mode"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p "${LINUX_BUILD_DIR}"
  mkdir -p "${WINDOWS_BUILD_DIR}"
  mkdir -p "${BINARIES_DIR}"
fi

# BUILDING LINUX BINARIES
build_binaries LINUX

# BUILDING WINDOWS BINARIES
build_binaries WINDOWS

printf "${yellow}::$(get_color reset)$(get_color bold) Distributing binaries in ./target/release${reset}\n%s"
cd ${LINUX_BUILD_DIR}
cp logicdev ../release
cd ../../
cd ${WINDOWS_BUILD_DIR}
cp logicdev.exe ../release.exe > /dev/null 2>&1

printf "${green}::$(get_color reset)$(get_color bold) Done${reset}" ""
kill -2 $$