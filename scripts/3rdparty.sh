#!/bin/bash

set -exu

libdir="${2:-3rdparty}"

if [ "$1" = "x86_64" ]; then
    tar -xzf 3rdparty/boost-1.87.0-linux-x86_64.tar.gz --strip-components=1 -C $libdir
fi
