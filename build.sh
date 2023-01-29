#!/bin/sh
EXECUTABLE=./HelloWorld
BUILD_DIR=./build/
mode=$1
if [ "$mode" = "" ]; then
  mode="Release"
fi
if [ "$mode" != "Debug" ] && [ "$mode" != "Release" ]; then
  printf "==> Invalid Mode: %s\nUsage: $0 [Debug|Release]" "$mode"
  exit 0
fi
echo -e "==> Using $mode Mode!\n"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi
cd "$BUILD_DIR" || exit 1
echo "==> Generating build files"
cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ../
echo -e "\n==> Building project"
ninja | ../lib/shiki/shiki
echo "==> Successfully built HelloWorld executable"
printf "\nDo you want to install this executable globally? [Y/n] "
read -r installExecutable
if [ "$installExecutable" = "" ]; then
  installExecutable="Y"
fi
if [ "$installExecutable" != "n" ] && [ "$installExecutable" = "Y" ]; then
  OUTPUT=$(id -u)
  if [ "$OUTPUT" != 0 ]; then
      echo "==> Please run as root"
      exit 1
  fi
  if test -f "$EXECUTABLE"; then
    echo "==> Installing HelloWorld globally..."
    cp ./HelloWorld /usr/bin/
    echo "==> Successfully installed"
  else
    echo "Please first run ./build.sh!"
  fi
  exit 0
else
  echo "==> Not installing this executable globally. Exiting..."
  exit 1
fi
