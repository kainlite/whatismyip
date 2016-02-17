# WhatIsMyIp.cpp

[![Build Status](https://travis-ci.org/kainlite/whatismyip.svg?branch=master)](https://travis-ci.org/kainlite/whatismyip)

### First of all make sure you have all these packages:
unzip git curl cmake flex bison gperf wget pkg-config 

### And libs:
libkrb5 libsasl2 libnuma libssl libcap autoconf libevent glog

### Then install Proxygen (a word of advice, just use deps.sh):
https://github.com/facebook/proxygen

### Then build this project:
```
mkdir build; cd build
cmake ..
make
make test
```
