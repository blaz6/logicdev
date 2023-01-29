#!/bin/sh
EXECUTABLE=./HelloWorld
mode=$1
if [ "$mode" = "" ]; then
  mode="Release"
fi
if [ "$mode" != "Debug" ] && [ "$mode" != "Release" ]; then
  printf "==> Invalid Mode: %s\nUsage: $0 [Debug|Release]" "$mode"
  exit 0
fi
printf "==> Using %s Mode!\n" "$mode"
echo "==> Generating build files"
cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ./
echo "==> Building project"
ninja | ./lib/shiki/shiki
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
