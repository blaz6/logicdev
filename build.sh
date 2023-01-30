#!/bin/sh
EXECUTABLE=./HelloWorld
BUILD_DIR=./buildDir/
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
    rm -rf $BUILD_DIR ./tmp ./src/discord ./lib/discord ./config
    exit 0
fi
if [ "$mode" != "Debug" ] && [ "$mode" != "Release" ]; then
  echo -e "${red}==> Invalid Mode:${reset} '$mode'\nAvailable options: Debug|Release"
  exit 0
fi

echo -e "${yellow}==> Using $mode Mode!${reset}\n"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi
if [ ! -d "./tmp" ] && [ ! -d "./lib/discord" ] && [ ! -d "./src/discord" ]; then
rm -rf tmp
rm -rf lib/discord
rm -rf src/discord
mkdir tmp
mkdir -p lib/discord
mkdir -p src/discord

cd tmp || exit 1
if [ "$mode" = "Release" ]; then
    wget "https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip" >/dev/null 2>&1
    unzip discord*.zip >/dev/null 2>&1
else
    wget "https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip"
    unzip discord*.zip
fi
cp lib/x86_64/* ../lib/discord/
cp cpp/* ../src/discord/
cd ../src/discord/ || exit 1

sed s/std::int/int/g -i *.*
sed s/std::uint/uint/g -i *.*

cd ../../
fi

cd "$BUILD_DIR" || exit 1
printf "${magenta}==> Generating build files${reset}%s"
if [ "$mode" = "Release" ]; then
    cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ../ >/dev/null 2>&1
else
    cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ../
fi
printf "\n${magenta}==> Building project%s"
if [ "$mode" = "Release" ]; then
    ninja | ../lib/shiki/shiki >/dev/null 2>&1
else
    ninja | ../lib/shiki/shiki
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