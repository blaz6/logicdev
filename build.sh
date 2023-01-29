#!/bin/sh

mode=$1
if [ "$mode" != "Debug" ] && [ "$mode" != "Release" ]; then
  printf "==> Invalid Mode: %s\nUsage: $0 [Debug|Release]" "$mode"
  exit 0
fi

echo "==> Generating build files"
cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ./
echo "==> Building project"
ninja
echo "==> Successfully built HelloWorld executable"
exit 1
