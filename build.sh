#!/bin/sh
EXECUTABLE=./logicdev
BUILD_DIR=./target
mode=$1

red='\033[0;31m'
green='\033[0;32m'
yellow='\033[0;33m'
blue='\033[0;34m'
magenta='\033[0;35m'
reset='\033[0m'

if [ "$mode" = "" ]; then
  mode="Release"
fi
if [ "$mode" = "clean" ]; then
    rm -rf $BUILD_DIR
    exit 0
fi
if [ "$mode" != "Debug" ] && [ "$mode" != "Release" ]; then
  echo -e "${red}==> Invalid Mode:${reset} '$mode'\nAvailable options: Debug|Release"
  exit 0
fi

printf "${yellow}==> Using %s Mode!${reset}\n" "$mode"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi
grep -rl "windows.h" . | xargs sed -i "s/windows.h/windows.h/g"

cd "$BUILD_DIR" || exit 1
printf "${magenta}==> Generating build files${reset}%s"
if [ "$mode" = "Release" ]; then
  if [ "$2" = "win" ]; then
      cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=../../../toolchains/mingw-w64-x86_64.cmake -DCMAKE_BUILD_TYPE="$mode" ../ >/dev/null 2>&1
  else
    cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ../ >/dev/null 2>&1
  fi
else
  if [ "$2" = "win" ]; then
      cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=../../../toolchains/mingw-w64-x86_64.cmake -DCMAKE_BUILD_TYPE="$mode" ../
  else
    cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ../
  fi
fi
printf "\n${magenta}==> Building project%s"
if [ "$mode" = "Release" ]; then
    ninja >/dev/null 2>&1
else
    ninja
fi
printf "\n${green}==> Successfully built %s executable${reset}" "$EXECUTABLE"
if [ -f ../config/config ]; then
  if grep -q "Y" ../config/config; then
    if test -f "$EXECUTABLE"; then
      printf "\n\n${magenta}==> Installing %s globally...${reset}" "$EXECUTABLE"
      sudo cp ./$EXECUTABLE /usr/bin/
      printf "\n${green}==> Successfully %sinstalled${reset}" ""
    else
      echo "Please first run ./build.sh!"
    fi
  fi
  kill -2 $$
fi
printf "\n\n${blue}Do you want to install this executable%s globally? [Y/n]${reset} " ""
read -r installExecutable
if [ "$installExecutable" = "" ]; then
  installExecutable="Y"
fi
if [ "$installExecutable" != "n" ] && [ "$installExecutable" = "Y" ]; then
  if test -f "$EXECUTABLE"; then
    printf "${magenta}==> Installing %s globally...${reset}" "$EXECUTABLE"
      sudo cp ./$EXECUTABLE /usr/bin/
      printf "\n${green}==> Successfully installed %s" ""
  else
    echo "Please first run ./build.sh!"
  fi
else
  echo "==> Not installing this executable globally. Exiting..."
fi
cd ../
if [ -f ./config/config ]; then
  kill -2 $$
fi
printf "\n\n${blue}Do you want to save%s this setting? [Y/n]${reset} " ""
read -r saveSettings
if [ "$saveSettings" = "" ]; then
  saveSettings="Y"
fi
if [ "$saveSettings" != "n" ] && [ "$saveSettings" = "Y" ]; then
  printf "${magenta}==> %sSaving settings...${reset}"
  rm -rf config
  mkdir config
  touch config/config
  echo "$saveSettings" > ./config/config
  printf "\n${green}==> Saved settings in ./config/config${reset}%s" ""
fi
kill -2 $$
