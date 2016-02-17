/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

namespace EchoService {

class EchoStats {
 public:
  virtual ~EchoStats() {
  }

  virtual void recordRequest() {
    ++reqCount_;
  }

  virtual uint64_t getRequestCount() {
    return reqCount_;
  }

  virtual void setClientIP(std::string address) {
    address_ = address;
  }

  virtual std::string getClientIP() {
    return address_;
  }

 private:
  uint64_t reqCount_{0};
  std::string address_;
};

}
