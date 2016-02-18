FROM ubuntu

RUN apt-get update
RUN apt-get install -yq git
RUN apt-get install -yq curl
RUN apt-get install -yq cmake build-essential
RUN apt-get install -yq \
    flex \
    bison \
    libkrb5-dev \
    libsasl2-dev \
    libnuma-dev \
    pkg-config \
    libssl-dev \
    libcap-dev \
    ruby \
    gperf \
    autoconf-archive \
    libevent-dev \
    libgoogle-glog-dev \
    wget
WORKDIR /home
RUN git clone https://github.com/facebook/proxygen.git
WORKDIR /home/proxygen/proxygen
RUN ./deps.sh && ./reinstall.sh
RUN git clone https://github.com/kainlite/whatismyip whatismyip && cd whatismyip 
WORKDIR /home/proxygen/proxygen/whatismyip/build
RUN cmake .. && make