#!/bin/sh

mode=$1
if [ "$mode" != "Debug" ] && [ "$mode" != "Release" ]; then
  exit 0
fi

cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$mode" ./
